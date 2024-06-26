/*
 * LWSDK Header File
 *
 * LWOBJIMP.H -- LightWave Object Importers
 *
 * When LightWave encounters a foreign object file which it cannot parse,
 * it will call an "ObjectLoader" class server to import it.  All the
 * loaders defined for the host will be activated in sequence, and the
 * first one to recognize the file will load it.
 *
 *Copyright © 2024 LightWave Digital, Ltd. and its licensors. All rights reserved.
 *
 *This file contains confidential and proprietary information of LightWave Digital, Ltd.,
 *and is subject to the terms of the LightWave End User License Agreement (EULA).
 */
#ifndef LWSDK_OBJIMP_H
#define LWSDK_OBJIMP_H

#include <lwtypes.h>
#include <lwmonitor.h>
#include <lwmeshes.h>

#define LWOBJECTIMPORT_CLASS    "ObjectLoader"
#define LWOBJECTIMPORT_VERSION  5

/*
 * The activation function of the server is passed an LWObjectImport
 * structure as its local data which includes the filename of the object
 * to load.  The loader attempts to parse the input file and calls the
 * embedded callbacks to insert the data into LightWave.  It indicates
 * its success or failure by setting the 'result' field, and the optional
 * failedBuf.
 *
 * result   set by the server to one of the LWOBJIM values below.
 *
 * filename the filename of the object to load.
 *
 * monitor  progress monitor that can be used to track the import
 *      process.
 *
 * failedBuf    string buffer for the server to store a human-readable
 *      error message if the result code is LWOBJIM_FAILED.
 *
 * data     private data pointer to be passed to all the embedded
 *      function callbacks.
 *
 * done     called when object import is complete.
 *
 * layer    start a new layer in the import data.  The layer is
 *      defined by an index number and a name string.
 *
 * pivot    set the pivot point for the current layer.
 *
 * parent   set the index of the parent layer for the current layer.
 *
 * lFlags   set the flag bits for the current layer.  The low-order bit
 *      is set if this is a hidden layer.
 *
 * point    add a new point to the current layer.  The point is given
 *      by an XYZ position and the function returns a void pointer
 *      as point identifier.
 *
 * vmap     select a VMAP for assigning data to points, creating a new
 *      VMAP if it does not yet exist.  The VMAP is defined by a
 *      type, dimension and name.
 *
 * vmapVal  set a vector for a point into the currently selected VMAP.
 *      The vector should have the same dimension as the VMAP.
 *
 * vmapPDV  set a vector for a point with reference to a specific polygon.
 *      This is the "polygon discontinuous value" for the point.
 *
 * polygon  add a new polygon to the current layer.  The polygon is
 *      defined by a type code, type-specific flags and a list of
 *      point identifiers.
 *
 * polTag   associate a tag string to the given polygon.  The tag
 *      string has a type, the most common being 'SURF'.
 *
 * surface  add a new surface to this object.  The surface is defined by
 *      the base name, the reference name, and a block of raw surface
 *      data.
 */
typedef struct st_LWObjectImport {
    int         result;
    LWCStringUTF8 filename;
    LWMonitor   *monitor;
    LWMutableCStringUTF8 failedBuf;
    int         failedLen;
    void        *data;

    void        (*done)    (void *);
    void        (*layer)   (void *, int lNum, LWCStringUTF8 name);
    void        (*pivot)   (void *, const LWFVector pivot);
    void        (*parent)  (void *, int lNum);
    void        (*lFlags)  (void *, int flags);
    LWPntID     (*point)   (void *, const LWFVector xyz);
    void        (*vmap)    (void *, LWID type, int dim, LWCStringUTF8 name);
    void        (*vmapVal) (void *, LWPntID point, const float *val);
    LWPolID     (*polygon) (void *, LWID type, int flags, int numPts, const LWPntID *);
    void        (*polTag)  (void *, LWPolID polygon, LWID type, LWCStringUTF8 tag);
    void        (*surface) (void *, LWCStringUTF8 basename, LWCStringUTF8 refname, int chunk_size, void *surf_chunk, unsigned int version);
    void        (*vmapPDV) (void *, LWPntID point, LWPolID polygon, const float *val);
    void        (*vmapsubp)(void *, unsigned int subpint);
    void        (*vmapskco)(void *, unsigned int sketchcolor);
    void*       (*curVmap) (void *);
    LWImageID   (*loadBitmap) (LWCStringUTF8 path);
    int         (*switchLayer)(void *, int lNum);
} LWObjectImport;


/*
 * The server must set the 'result' field to one of these following values
 * before it returns.
 *
 * OK       indicates successful parsing of the object file.
 *
 * BADFILE  indicates that the loader could not open the file.
 *
 * NOREC    indicates that the loader could open the file but could
 *      not recognize the format.
 *
 * ABORTED  indicates the that the user manually aborted the load.
 *
 * Any other failure is indicated by the generic FAILED value.  In this case,
 * the loader may also place a human-readable error message into the buffer
 * pointed to by `failedBuf,' provided that `failedLen' is non-zero.
 */
#define LWOBJIM_OK   0
#define LWOBJIM_NOREC    1
#define LWOBJIM_BADFILE  2
#define LWOBJIM_ABORTED  3
#define LWOBJIM_FAILED   99


#endif
