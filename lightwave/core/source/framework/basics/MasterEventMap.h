
#pragma once

#include "LWsdk.h"

struct LWEVENT_Description
{
    std::map<int, std::string> eventMap;

    LWEVENT_Description()
    {
        // General events
        eventMap[LWEVNT_NOTHING] = "No event";
        eventMap[LWEVNT_COMMAND] = "Command issued";
        eventMap[LWEVNT_TIME] = "Time changed";
        eventMap[LWEVNT_SELECT] = "Selection changed";
        eventMap[LWEVNT_RENDER_DONE] = "Rendering completed";

        // Detailed notification events
        eventMap[LWEVNT_NOTIFY_MOTION_UPDATE_STARTING] = "Motion update starting";
        eventMap[LWEVNT_NOTIFY_MOTION_UPDATE_COMPLETE] = "Motion update completed";
        eventMap[LWEVNT_NOTIFY_MESH_REPLACED] = "Mesh replaced";
        eventMap[LWEVNT_NOTIFY_MESH_UPDATE_STARTING] = "Mesh update starting";
        eventMap[LWEVNT_NOTIFY_MESH_UPDATE_AFTERMORPHING] = "Mesh update after morphing";
        eventMap[LWEVNT_NOTIFY_MESH_UPDATE_AFTERBONES] = "Mesh update after bones";
        eventMap[LWEVNT_NOTIFY_MESH_UPDATE_AFTERLOCALDISPLACEMENTS] = "Mesh update after local displacements";
        eventMap[LWEVNT_NOTIFY_MESH_UPDATE_AFTERMOTION] = "Mesh update after motion";
        eventMap[LWEVNT_NOTIFY_MESH_UPDATE_COMPLETE] = "Mesh update complete";
        eventMap[LWEVNT_NOTIFY_RENDER_FRAME_STARTING] = "Render frame starting";
        eventMap[LWEVNT_NOTIFY_RENDER_FRAME_COMPLETE] = "Render frame complete";
        eventMap[LWEVNT_NOTIFY_RENDER_STARTING] = "Render sequence starting";
        eventMap[LWEVNT_NOTIFY_RENDER_COMPLETE] = "Render sequence complete";
        eventMap[LWEVNT_NOTIFY_SCENE_CLEAR_STARTING] = "Scene clear starting";
        eventMap[LWEVNT_NOTIFY_SCENE_CLEAR_COMPLETE] = "Scene clear complete";
        eventMap[LWEVNT_NOTIFY_SCENE_LOAD_STARTING] = "Scene load starting";
        eventMap[LWEVNT_NOTIFY_SCENE_LOAD_COMPLETE] = "Scene load complete";
        eventMap[LWEVNT_NOTIFY_SCENE_SAVE_STARTING] = "Scene save starting";
        eventMap[LWEVNT_NOTIFY_SCENE_SAVE_COMPLETE] = "Scene save complete";
        eventMap[LWEVNT_NOTIFY_ITEM_ADDED] = "Item added";
        eventMap[LWEVNT_NOTIFY_ITEM_REMOVING] = "Item removing";
        eventMap[LWEVNT_NOTIFY_ITEM_REPARENTED] = "Item reparented";
        eventMap[LWEVNT_NOTIFY_SURFACE_ALTERED] = "Surface altered";
        eventMap[LWEVNT_NOTIFY_SURFACE_ADDED] = "Surface added";
        eventMap[LWEVNT_NOTIFY_SURFACE_REMOVING] = "Surface removing";
        eventMap[LWEVNT_NOTIFY_CHANNEL_ADDED] = "Channel added";
        eventMap[LWEVNT_NOTIFY_CHANNEL_REMOVING] = "Channel removing";
        eventMap[LWEVNT_NOTIFY_PLUGIN_CHANGED] = "Plugin instance changed";
        eventMap[LWEVNT_NOTIFY_RENDER_ABORTED] = "Render aborted";
        eventMap[LWEVNT_NOTIFY_TEXTURE_REMOVING] = "Texture removing";
        eventMap[LWEVNT_NOTIFY_IMAGE_REMOVING] = "Image removing";
        eventMap[LWEVNT_NOTIFY_IMAGE_ALTERED] = "Image altered";
        eventMap[LWEVNT_NOTIFY_TEXTURE_ALTERED] = "Texture altered";
        eventMap[LWEVNT_NOTIFY_LIST_UPDATE_OBJECTS] = "Object list updated";
        eventMap[LWEVNT_NOTIFY_LIST_UPDATE_LIGHTS] = "Light list updated";
        eventMap[LWEVNT_NOTIFY_LIST_UPDATE_CAMERAS] = "Camera list updated";
        eventMap[LWEVNT_NOTIFY_LIST_UPDATE_BONES] = "Bone list updated for an object";
        eventMap[LWEVNT_NOTIFY_OBJECT_SAVE_STARTING] = "Object save starting";
        eventMap[LWEVNT_NOTIFY_OBJECT_SAVE_COMPLETE] = "Object save complete";
        eventMap[LWEVNT_VIEWPORT_OBJECT_ADDED] = "Viewport renderer like VPR activated";
        eventMap[LWEVNT_VIEWPORT_OBJECT_REMOVED] = "Viewport renderer like VPR removed";
        eventMap[LWEVNT_NOTIFY_SCENETREE_UPDATED] = "Scenetree updated";
        eventMap[LWEVNT_NOTIFY_ITEMS_ADDING] = "Start of adding many items";
        eventMap[LWEVNT_NOTIFY_ITEMS_ADDED] = "End of adding many items";
        eventMap[LWEVNT_NOTIFY_ITEMS_REMOVING] = "Start of removing many items";
        eventMap[LWEVNT_NOTIFY_ITEMS_REMOVED] = "End of removing many items";
        eventMap[LWEVNT_NOTIFY_NEWTIME_START] = "Start of processing a frame";
        eventMap[LWEVNT_NOTIFY_NEWTIME_END] = "End of processing a frame";
        eventMap[LWEVNT_NOTIFY_LOAD_ITEMS_FROM_SCENE] = "Items loaded from scene";
        eventMap[LWEVNT_NOTIFY_LIGHT_ALTERED] = "Light settings altered";
        // eventMap[LWEVNT_NOTIFY_NEWTIME_PREP] = "Preparation phase of newTime";
    }

    std::string getEventDescription (int eventCode)
    {
        auto it = eventMap.find (eventCode);
        return it != eventMap.end() ? it->second : "Unknown event";
    }
};
