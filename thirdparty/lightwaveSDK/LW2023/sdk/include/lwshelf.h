/*
 * LWSDK Header File
 *
 *Copyright © 2024 LightWave Digital, Ltd. and its licensors. All rights reserved.
 *
 *This file contains confidential and proprietary information of LightWave Digital, Ltd.,
 *and is subject to the terms of the LightWave End User License Agreement (EULA).
 */
#ifndef LWSHELF_H
#define LWSHELF_H

/* Standard */
#include <stdio.h>
#include <stdlib.h>

#include <lwtypes.h>
#include <lwdialog.h>
#include <lwglobsrv.h>
#include <lwimage.h>
#include <lwio.h>

/****
 * Callback Prototypes:
 * --------------------
 * LWShelfLoadOkFunc - Asks the subscribed client if it is ready to accept
 *                     loading a preset.
 * LWShelfLoadFunc - Called to have the client load settings
 * LWShelfSaveFunc - Called during save to obtain client settings
 *
 *     These load and save callbacks provide for loading and
 *     saving client settings using the LW Load and Save State (LWIO.H)
 *     OR as a separate data file.
 *
 *     Use of the LWIO states is recommended.
 *
 *     Which format is used depends on the subscription flags
 *     where SHLF_BIN or SHLF_ASC uses the corresponding LWIO
 *     load/save states and SHLF_SEP indicates the client will
 *     save data to a separate file in whatever manner best suits
 *     its needs. The filename argument to the Load/SaveFunc
 *     callbacks is the filename the client should use for this
 *     activity.
 *
 * API Description:
 * ----------------
 * subscribe      - Adds a client to the Preset Shelf and returns a client ID.
 * unsubscribe    - Unsubscribes the client. Clients should, at a minimum,
 *                  do this when its instance is destroyed.
 * open           - Opens the Preset Shelf window and sets focus to the client.
 * close          - Closes the Shelf.
 * setContext     - Grabs the focus of the Shelf. This differs from the Open
 *                  method by making the client the active client but this
 *                  does not open the Shelf window.
 * addPreset      - Called by the client to add a preset settings
 * addNamedPreset   file to the Presets Shelf. The 'img' is an
 *                  LWImageID to use as the preset's thumbnail. The
 *                  'parms' is a NULL terminated list of string
 *                  parameter tags which can be used to conditionally
 *                  load settings from the preset.
 * (Independent Operations)
 * load/save      - These load/save preset settings files to an
 *                  arbitrary location specified by 'filename'. As part
 *                  of the shelf API, the load and save methods reuse
 *                  the client subscription settings (like userdata,
 *                  callbacks, etc.). If 'prompt_user' is true and the
 *                  preset contains a parameter list, this will prompt
 *                  user for input.
 ****
 */

#define LWSHELFFUNCS_GLOBAL "LWShelfFuncs 3"

typedef void *LWShelfCltID; /* opaque handle to shelf client */
typedef LWMutableCStringASCII *LWShelfParmList; /* 0-terminated array of 0-terminated character strings */

typedef int  LWShelfLoadOkFunc ( void *userdata );
typedef void LWShelfLoadFunc   ( void *userdata, const LWLoadState *load, LWCStringUTF8 filename, LWShelfParmList parms );
typedef void LWShelfSaveFunc   ( void *userdata, const LWSaveState *save, LWCStringUTF8 filename );

/* Load and Save Options */
#define SHLF_BIN    (1<<1)   /* Binary LWIO State */
#define SHLF_ASC    (1<<2)   /* Ascii LWIO State */
#define SHLF_SEP    (1<<3)   /* Client uses separate file */

/* LoadOk Codes */
enum en_SHELF_LOADOK {
  SHLC_NOWAY = 0,  /* Do not load. Client told user reason */
  SHLC_DFLT,       /* Use default confirmation dialog. */
  SHLC_FORCE       /* Load. Do Not confirm with user. */
};

/* Preset Location Flags */
#define SHLF_LOCATION_WRITABLE    (1<<1)    /* The location can be saved to. */
#define SHLF_LOCATION_DEFAULTSAVE (1<<2)    /* The default destination for new presets. */


typedef struct st_LWShelfFuncs {
  /* Client subscriptions */
  LWShelfCltID (*subscribe)      ( LWCStringUTF8 name, LWCStringUTF8 subName, void *userData, int flags,
                                   LWShelfLoadOkFunc *loadOk_callback,
                                   LWShelfLoadFunc *load_callback,
                                   LWShelfSaveFunc *save_callback );
  void         (*unsubscribe)    ( LWShelfCltID clt );
  /* Shelf Operations */
  void         (*open)           ( LWShelfCltID clt );
  int          (*isOpen)         ( LWShelfCltID clt );
  void         (*close)          ( LWShelfCltID clt );
  void         (*setContext)     ( LWShelfCltID clt );
  int          (*addPreset)      ( LWShelfCltID clt, LWImageID img, LWShelfParmList parms );
  /* Independent Load and Save */
  void         (*load)           ( LWShelfCltID clt, LWCStringUTF8 filename, int prompt_user );
  void         (*save)           ( LWShelfCltID clt, LWCStringUTF8 filename, LWImageID thumimg, LWShelfParmList parms );
  int          (*addNamedPreset) ( LWShelfCltID clt, LWImageID img, LWShelfParmList parms, LWCStringUTF8 name, LWCStringUTF8 comment );
  /* Preset Location Info */
  unsigned int  (*locationCount)  (void);
  LWCStringUTF8 (*locationName)   (unsigned int index);
  LWCStringUTF8 (*locationPath)   (unsigned int index);
  unsigned int  (*locationFlags)  (unsigned int index);
} LWShelfFuncs;

/* Close the header */
#endif