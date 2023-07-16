#pragma once

/* This generated file contains includes for project dependencies */
#include "flecs.h"
#include <SDL2/SDL_stdinc.h>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif

    namespace WindowModule
    {

    struct Window
    {
        std::string title;
        int width;
        int height;
        Uint32 flags;
        bool quit;
    };

    typedef enum WindowFlags
    {
        Fullscreen = 0x00000001,      /**< fullscreen window */
        Shown = 0x00000004,           /**< window is visible */
        Hidden = 0x00000008,          /**< window is not visible */
        Borderless = 0x00000010,      /**< no window decoration */
        Resizable = 0x00000020,       /**< window can be resized */
        Minimized = 0x00000040,       /**< window is minimized */
        Maximized = 0x00000080,       /**< window is maximized */
        MouseGrabbed = 0x00000100,    /**< window has grabbed mouse input */
        HasInputFocus = 0x00000200,   /**< window has input focus */
        HasMouseFocus = 0x00000400,   /**< window has mouse focus */
        AllowHighDPI = 0x00002000,    /**< window should be created in high-DPI mode if supported.
                                                       On macOS NSHighResolutionCapable must be set true in the
                                                       application's Info.plist for this to have any effect. */
        MouseCaptured = 0x00004000,   /**< window has mouse captured (unrelated to MOUSE_GRABBED) */
        AlwaysOnTop = 0x00008000,     /**< window should always be above others */
        SkipTaskbar = 0x00010000,     /**< window should not be added to the taskbar */
        Utility = 0x00020000,         /**< window should be treated as a utility window */
        ToolTip = 0x00040000,         /**< window should be treated as a tooltip */
        PopUpMenu = 0x00080000,       /**< window should be treated as a popup menu */
        KeyboardGrabbed = 0x00100000, /**< window has grabbed keyboard input */
    } WindowFlags;

    struct WindowModule
    {
        WindowModule(flecs::world &world); // Ctor that loads the module
    };

    } // namespace WindowModule

#ifdef __cplusplus
}
#endif