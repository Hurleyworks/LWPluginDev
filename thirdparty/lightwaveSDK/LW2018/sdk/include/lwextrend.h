/*
 * LWSDK Header File
 *
 * LWEXTRENDERER.H -- LightWave Renderer
 *
 *Copyright � 2018 NewTek, Inc. and its licensors. All rights reserved.
 *
 *This file contains confidential and proprietary information of NewTek, Inc.,
 *and is subject to the terms of the LightWave End User License Agreement (EULA).
 */
#ifndef LWSDK_EXTRENDERER_H
#define LWSDK_EXTRENDERER_H

#include <lwserver.h>
#include <lwgeneric.h>
#include <lwhandler.h>
#include <lwrender.h>

#define LWEXTRENDERER_HCLASS  "ExtRendererHandler"
#define LWEXTRENDERER_VERSION 2

typedef int EXTRENDERERIMAGE( int frame, int eye, LWPixmapID displayimage, const char *name, const char *buffer );

typedef struct st_LWExtRendererHandler {
    LWInstanceFuncs *inst;
    LWItemFuncs     *item;
    int            (*options)( LWInstance );
    int            (*render )( LWInstance, int first_frame, int last_frame, int frame_step, EXTRENDERERIMAGE *render_image, int render_mode );
} LWExtRendererHandler;

#endif