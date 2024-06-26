/*
 * LWSDK Header File
 *
 * LWPREVIEW.H -- LightWave Preview Services
 *
 *Copyright © 2024 LightWave Digital, Ltd. and its licensors. All rights reserved.
 *
 *This file contains confidential and proprietary information of LightWave Digital, Ltd.,
 *and is subject to the terms of the LightWave End User License Agreement (EULA).
 */
#ifndef     LWPREVIEW_H
#define     LWPREVIEW_H

#include <lwtypes.h>
#include <lwimage.h>
#include <lwtxtr.h>

typedef struct  st_PvSample {
    int             x,y;
    double          rgbaz[5];
    LWMicropol      mp;
} PvSample;

typedef int         clickFunc(int   count,void  *userData,PvSample  *pixel);
typedef void        optionsFunc(int option,void *userData);
typedef void        closeFunc(void  *userData);

typedef int         initFunc(void   *renderData,int     manual);
typedef void        cleanupFunc(void    *renderData);
typedef int         evaluateFunc(void   *renderData,int w,int   h,PvSample  *pixel);
typedef void        presetFunc(void *userData,LWImageID img);

typedef struct  st_PvContext    *PvContextID;

#define LWPREVIEWFUNCS_GLOBAL   "Preview Functions 2"

typedef struct  st_LWPreviewFuncs {
    PvContextID     (*subscribe)(LWCStringUTF8 title, void *userData, closeFunc *);
    void            (*unsubscribe)(PvContextID);

    void            (*open)(PvContextID);
    void            (*close)(void);
    int             (*isOpen)(void);
    void            (*setContext)(PvContextID);

    void            (*setClick)(PvContextID,clickFunc   *);
    void            (*setRender)(PvContextID,void   *renderData,initFunc *,cleanupFunc *,evaluateFunc *);
    void            (*setOptions)(PvContextID,LWMutableCStringUTF8 *list,optionsFunc  *,int   selection);

    void            (*startRender)(PvContextID);
    void            (*stopRender)(PvContextID);

    void            (*getPixel)(PvSample    *pixel);
    LWImageID       (*getBitmap)(int    *width,int  *height);
    LWItemID        (*getCamera)(double pos[3],double rot[3],double *zoomFactor);
    void            (*getView)(int  *width,int  *height,double  *pixelAspect);

    void            (*setPreset)(PvContextID,presetFunc *);
} LWPreviewFuncs;

#endif