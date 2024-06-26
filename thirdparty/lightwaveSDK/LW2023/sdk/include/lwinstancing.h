/*
 * LWSDK Header File
 *
 * LWINSTANCING.H -- LightWave Item Instancing.
 *
 *Copyright © 2024 LightWave Digital, Ltd. and its licensors. All rights reserved.
 *
 *This file contains confidential and proprietary information of LightWave Digital, Ltd.,
 *and is subject to the terms of the LightWave End User License Agreement (EULA).
 */
#ifndef LWSDK_INSTANCING_H
#define LWSDK_INSTANCING_H

#include <lwserver.h>
#include <lwrender.h>

#define LWINSTANCER_HCLASS          "InstancerHandler"
#define LWINSTANCER_ICLASS          "InstancerInterface"
#define LWINSTANCER_GCLASS          "InstancerGizmo"
#define LWINSTANCER_VERSION         2

#define LWITEMINSTANCERFUNCS_GLOBAL "ItemInstancerFuncs 2"
#define LWITEMINSTANCEINFO_GLOBAL   "ItemInstanceInfo"

#define LWINSTEVAL_RENDER 0
#define LWINSTEVAL_OPENGL 1

// The LWInstancerAccess struct.
typedef struct LWInstancerAccess_t {
    LWItemInstancerID   instancer;
    int                 mode;
} LWInstancerAccess;


// Instancer handler activation.
typedef struct st_LWInstancerHandler {
    LWInstanceFuncs     *inst;
    LWItemFuncs         *item;
    LWRenderFuncs       *rend;
    void                (*evaluate)( LWInstance, const LWInstancerAccess* );
} LWInstancerHandler;

typedef enum { INSTDRAW_NONE = 0, INSTDRAW_POINT, INSTDRAW_BBOX, INSTDRAW_MESH, INSTDRAW_BKFACE, INSTDRAW_SOLID, INSTDRAW_TEXTUR } InstanceDrawerMode;

// Instancer funcs.
typedef struct LWItemInstancerFuncs_t {
    unsigned int        (*numInstances)( LWItemInstancerID instancer );
    LWItemInstanceID    (*instanceByIndex)( LWItemInstancerID instancer, unsigned int index );
    LWItemInstanceID    (*first)( LWItemInstancerID instancer );
    LWItemInstanceID    (*next)( LWItemInstancerID instancer, LWItemInstanceID instance );

    LWItemInstanceID    (*createInstance)( LWItemInstancerID instancer );
    void                (*destroyInstance)( LWItemInstancerID instancer, LWItemInstanceID instance );
    void                (*setInstance)( LWItemInstanceID instance, unsigned int ID, LWItemID item, unsigned int steps );
    void                (*setMotionStep)( LWItemInstanceID instance, unsigned int step,
                                          const LWDVector pos, const LWDVector scl, const LWDVector rot );
    void                (*setMotions)( LWItemInstanceID instance, unsigned int steps,
                                       const LWDVector *pos, const LWDVector *scl, const LWDVector *rot );
    void                (*setMotionStepM)( LWItemInstanceID instance, unsigned int step,
                                           const LWDVector pos, const double matrix[9] );
    void                (*setMotionsM)( LWItemInstanceID instance, unsigned int steps,
                                        const LWDVector *pos, const double *matrix[9] );

    // GUI only
    void                (*setInstanceDrawer)( LWItemInstanceID instance, InstanceDrawerMode drawmode );
    void                (*setInstanceDrawerColor)( LWItemInstanceID instance, unsigned int color ); // Use RGB_(r, g, b) macro to make colors.

    // LW2018: Use this in favour of the other set**** functions.
    void                (*setMotionStepAuto)( LWItemInstanceID vinstance, LWTime time , unsigned int step,
                                              const LWDVector p, const double m[9] );
} LWItemInstancerFuncs;

// Instance information.
typedef struct LWItemInstanceInfo_t {
    LWItemID            (*item)( LWItemInstanceID inst );                                       // The LWItemID of the item being instanced.
    unsigned int        (*steps)( LWItemInstanceID inst);                                       // The motion steps stored in the instance.
    void                (*pos)( LWItemInstanceID inst, unsigned int step, LWDVector p );        // The position of the instance.
    void                (*scale)( LWItemInstanceID inst, unsigned int step, LWDVector s );      // The scale of the instance.
    void                (*rotation)( LWItemInstanceID inst, unsigned int step, LWDVector r );   // The rotation of the instance.
    unsigned int        (*ID)( LWItemInstanceID inst );                                         // The ID set by the generator.
    void                (*matrix)( LWItemInstanceID inst, unsigned int step, double m[9] );     // The rotation and scale matrix of the instance.
} LWItemInstanceInfo;

#endif