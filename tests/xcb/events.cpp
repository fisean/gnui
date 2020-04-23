#include <iostream>
#include <array>
#include <stdlib.h>
#include <inttypes.h>
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-x11.h>


/* print names of modifiers present in mask */
void
print_modifiers(uint32_t mask)
{
    const char *MODIFIERS[] = {
      "Shift", "Lock", "Ctrl", "Alt",
      "Mod2", "Mod3", "Mod4", "Mod5",
      "Button1", "Button2", "Button3", "Button4", "Button5"
    };

    std::cout << "Modifier mask: ";
    for (const char **modifier = MODIFIERS ; mask; mask >>= 1, ++modifier) {
        if (mask & 1) {
          // std::cout << *modifier;
        }
    }
    std::cout << '\n';
}


int
main()
{
  /* Open the connection to the X server */
  Display *display = XOpenDisplay(nullptr);
  if (display == nullptr)
  {
    std::cerr << "Could not open X display!\n";
    return 1;
  }
  xcb_connection_t *connection = XGetXCBConnection(display);

  /* Get the first screen */
  xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;


  /* Create the window */
  xcb_window_t window = xcb_generate_id(connection);

  uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  // uint32_t values[2] =
  // {
    // screen->white_pixel,
    // 0x1ffffff
  // };
  uint32_t values[2] =
  {
    screen->white_pixel,
    XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
    XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
    XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
    XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE
  };

  xcb_create_window(
    connection,
    0,                             /* depth               */
    window,
    screen->root,                  /* parent window       */
    0, 0,                          /* x, y                */
    150, 150,                      /* width, height       */
    10,                            /* border_width        */
    XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
    screen->root_visual,           /* visual              */
    mask, values );                /* masks */

  /* Map the window on the screen */
  xcb_map_window(connection, window);
  xcb_flush(connection);

  xcb_window_t window2 = xcb_generate_id(connection);

  xcb_create_window(
    connection,
    0,                             /* depth               */
    window2,
    window,                        /* parent window       */
    20, 20,                        /* x, y                */
    50, 50,                        /* width, height       */
    10,                            /* border_width        */
    XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
    screen->root_visual,           /* visual              */
    mask, values );                /* masks */

  xcb_map_window(connection, window2);

  xcb_flush(connection);
  std::cout << "window = " << window;
  std::cout << ", window2 = " << window2 << '\n';

  xcb_generic_event_t *event;
  while ((event = xcb_wait_for_event(connection)))
  {
    switch (event->response_type & ~0x80)
    {
      case XCB_EXPOSE:
      {
        xcb_expose_event_t *expose = (xcb_expose_event_t *)event;
        std::cout << "Window " << expose->window;
        std::cout << " exposed. Region to be redrawn at location (";
        std::cout << expose->x << ", " << expose->y <<"), with dimension (";
        std::cout << expose->width << ", " << expose->height << ")\n";
        break;
      }
      case XCB_BUTTON_PRESS:
      {
        xcb_button_press_event_t *bp = (xcb_button_press_event_t *)event;
        print_modifiers(bp->state);
        switch (bp->detail)
        {
          case 4:
          {
            std::cout << "Wheel Button up in window ";
            std::cout << bp->event << ", at coordinates (";
            std::cout << bp->event_x << ", " << bp->event_y << ")\n";
            break;
          }
          case 5:
          {
            std::cout << "Wheel Button down in window " << bp->event;
            std::cout << ", at coordinates (" << bp->event_x;
            std::cout << "," << bp->event_y << ")\n";
            break;
          }
          default:
          {
            std::cout << "Button " << bp->detail << " pressed in window ";
            std::cout << bp->event << ", at coordinates (" << bp->event_x;
            std::cout << ", " << bp->event_y << ")\n";
            break;
          }
        }
        break;
      }
      case XCB_BUTTON_RELEASE:
      {
        xcb_button_release_event_t *br = (xcb_button_release_event_t *)event;
        print_modifiers(br->state);
        std::cout << "Button " << br->detail << " released in window ";
        std::cout << br->event << ", at coordinates (" << br->event_x;
        std::cout << ", " << br->event_y << ")\n";
        break;
      }
      case XCB_MOTION_NOTIFY:
      {
        xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;
        std::cout << "Mouse moved in window ";
        std::cout << motion->event << ", at coordinates (";
        std::cout << motion->event_x << ", " << motion->event_y << ")\n";
        break;
      }
      case XCB_ENTER_NOTIFY:
      {
        xcb_enter_notify_event_t *enter = (xcb_enter_notify_event_t *)event;
        std::cout << "Mouse entered window " << enter->event;
        std::cout << ", at coordinates (" << enter->event_x;
        std::cout << ", " << enter->event_y << ")\n";
        break;
      }
      case XCB_LEAVE_NOTIFY:
      {
        xcb_leave_notify_event_t *leave = (xcb_leave_notify_event_t *)event;
        std::cout << "Mouse left window " << leave->event;
        std::cout << ", at coordinates (" << leave->event_x;
        std::cout << ", " << leave->event_y << ")\n";
        break;
      }
      case XCB_KEY_PRESS:
      {
        struct xkb_context *ctx;

        ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
        if (!ctx) { std::cerr << "xkb_context_new failed\n"; return 1; }

        int32_t device_id;

        device_id = xkb_x11_get_core_keyboard_device_id(connection);
        if (device_id == -1)
        {
          std::cerr << "xkb_x11_get_core_keyboard_device_id failed\n";
          return 1;
        }
        struct xkb_keymap *keymap;
        keymap = xkb_x11_keymap_new_from_device(
          ctx,
          connection,
          device_id,
          XKB_KEYMAP_COMPILE_NO_FLAGS
        );
        if (!keymap)
        {
          std::cerr << "xkb_x11_keymap_new_from_device failed\n";
          return 1;
        }
        struct xkb_state *state = xkb_x11_state_new_from_device(keymap, connection, device_id);
        if (!state)
        {
          std::cerr << "xkb_x11_state_new_from_device failed\n";
          return 1;
        }
        xcb_key_press_event_t *kp = (xcb_key_press_event_t *)event;
        print_modifiers(kp->state);
        xkb_keycode_t keycode;
        xkb_keysym_t keysym;

        keycode = kp->detail;
        keysym = xkb_state_key_get_one_sym(state, keycode);

        std::string buffer;
        int size;
        size = xkb_state_key_get_utf8(state, keycode, NULL, 0) + 1;
        if (size <= 1) { continue; }
        buffer.resize(size);
        xkb_state_key_get_utf8(state, keycode, buffer.data(), size);
        std::cout << "UTF8: " << buffer << '\n';
        break;
      }
      case XCB_KEY_RELEASE:
      {
        xcb_key_release_event_t *kr = (xcb_key_release_event_t *)event;
        // print_modifiers(kr->state);
        std::cout << "Key released in window " << kr->event << '\n';
        break;
      }
      default:
        /* Unknown event type, ignore it */
        std::cout << "Unknown event: " << event->response_type << '\n';
        break;
    }

    free (event);
  }
  return 0;
}
