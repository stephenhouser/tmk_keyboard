# T.M.K. Changes and Notes

## Highlights of my Keymap for macOS

| ---                   | ---               | ---           |
| Keyboard Key          | macOS Key         | TMK Key       |
| ---                   | ---               | ---           |
| Caps Lock             | ⌥ Option          | LALT          |
| Left Control          | ^ Left Control    | LCTL          |
| Left Alt              | ⌘ Command (LGUI)  | LGUI          |
| Right Alt             | ⌥ Option          | RALT          |
| Right Control         | ^ Right Control   | RCTL          |
| ---                   | ---               | ---           |
| Print Screen          | Volume Down       | VOLDN         |
| Scroll Lock           | Volume Up         | VOLUP         |
| Pause                 | Mute              | MUTE          |
| ---                   | ---               | ---           |

## Compilation Notes

Some important things to keep in mind:

* My converter uses a Pro Micro `atmega32u4` so to program it, you need something like:

    ```
    avrdude -p atmega32u4 -c avr109 -U flash:w:/Users/houser/Projects/tmk_keyboard/converter/ps2_usb/ps2_usb_rev2_unimap.hex:i -P /dev/cu.usbmodem49 -C avrdude.conf
    ```

    NOTE: I copied this out of the [QMK Toolbox](https://github.com/qmk/qmk_toolbox) command window when trying to get things working.

    The important things here are:

    * The Pro Micro clone uses the `avr109` programmer
    * The port changes every time, you have to look for it and act quickly
    * To progrm _short the *GND* and *RST*_ pins.

* I'm using the `unimap` configuration in `unimap_stephen.c`.

* I've modified the USB vendor and product identifiers in my own `config_stephen.c`. This are completely vanity changes and really don't affect the working of anything.

* I'm using my own `Makefile.stephen` to keep things simple. It manages the keymap, config, and device type.

# Workflow

1. Modify `unimap_stephen.c` to my liking.
2. Check `config_stephen.h` for any changes there.
3. Clean `make -f Makefile.stephen clean`
4. Build `make -f Makefile.stephen`
5. Upload with `avrdude` or [QMK Toolbox](https://github.com/qmk/qmk_toolbox) (easy)