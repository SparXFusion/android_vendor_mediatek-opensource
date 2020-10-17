#ifndef __ANDROID_SURFACE_FLINGER_DISP_SYNC_ENHANCEMENT_DEF_H__
#define __ANDROID_SURFACE_FLINGER_DISP_SYNC_ENHANCEMENT_DEF_H__

namespace {

enum {
    VSYNC_MODE_CALIBRATED_SW_VSYNC = 0,
    VSYNC_MODE_PASS_HW_VSYNC,
    VSYNC_MODE_INTERNAL_SW_VSYNC,
};

enum {
    WAKE_REASON_NONE = 0,
    WAKE_REASON_VSYNC,
};

}

#endif
