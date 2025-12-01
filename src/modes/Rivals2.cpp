#include "modes/Rivals2.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

Rivals2::Rivals2() : ControllerMode() {}

void Rivals2::UpdateDigitalOutputs(const InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.rt1;
    outputs.b = inputs.rf1;
    outputs.x = inputs.rf2;
    outputs.y = inputs.rf6;
    //outputs.buttonL = inputs.rf7; //left bumper
    outputs.buttonR = inputs.rf3 || inputs.rf8; //Z
    outputs.triggerLDigital = inputs.lf4;
    outputs.triggerRDigital = inputs.rf5;
    outputs.start = inputs.mb1;

    // Turn on D-Pad layer by holding Mod X + Mod Y or Nunchuk C button.
    if ((inputs.lt1 && inputs.lt2) || inputs.nunchuk_c || inputs.lf5) {
        outputs.dpadUp = inputs.rt4;
        outputs.dpadDown = inputs.rt2;
        outputs.dpadLeft = inputs.rt3;
        outputs.dpadRight = inputs.rt5;
    }

    // Hidden Buttons for remapp.ing options
    outputs.leftStickClick = inputs.lf6;
    outputs.rightStickClick = inputs.lf7;
    outputs.capture = inputs.lf8;
    outputs.dpadUp = inputs.lf9;
    outputs.dpadDown = inputs.lf10;
    outputs.dpadLeft = inputs.lf11;
    outputs.dpadRight = inputs.lf12;
    //outputs.select = inputs.mb2; //Select Input
    outputs.home = inputs.mb3;
}

void Rivals2::UpdateAnalogOutputs(const InputState &inputs, OutputState &outputs) {
   // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.lf3, // Left
        inputs.lf1, // Right
        inputs.lf2, // Down
        inputs.rf4, // Up
        inputs.rt3, // C-Left
        inputs.rt5, // C-Right
        inputs.rt2, // C-Down
        inputs.rt4, // C-Up
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.lf4 || inputs.rf5;

    if (inputs.lt1) {
        // MX + Horizontal = 6625 = 53
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 53);
            // Horizontal Shield tilt = 51
            if (shield_button_pressed) {
                outputs.leftStickX = 128 + (directions.x * 51);
            }
            // Horizontal Tilts = 36
            if (inputs.rt1) {
                outputs.leftStickX = 128 + (directions.x * 36);
            }
        }
        // MX + Vertical = 44
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 44);
            // Vertical Shield Tilt = 51
            if (shield_button_pressed) {
                outputs.leftStickY = 128 + (directions.y * 51);
            }
        }
        if (directions.diagonal && shield_button_pressed) {
            // MX + L, R, LS, and MS + q1/2/3/4 = 6375 3750 = 51 30
            outputs.leftStickX = 128 + (directions.x * 51);
            outputs.leftStickY = 128 + (directions.y * 30);
        }

        /* Up B angles */
        if (directions.diagonal && !shield_button_pressed) {
            // MX + q1/2/3/4 = 33.44 degrees | 53 35
            outputs.leftStickX = 128 + (directions.x * 53);
            outputs.leftStickY = 128 + (directions.y * 35);
            // (39.05) = 53 43
            if (inputs.rt2) {
                outputs.leftStickX = 128 + (directions.x * 53);
                outputs.leftStickY = 128 + (directions.y * 43);
            }
            // (36.35) = 53 39
            if (inputs.rt3) {
                outputs.leftStickX = 128 + (directions.x * 53);
                outputs.leftStickY = 128 + (directions.y * 39);
            }
            // (30.32) = 56 41
            if (inputs.rt4) {
                outputs.leftStickX = 128 + (directions.x * 53);
                outputs.leftStickY = 128 + (directions.y * 31);
            }
            // (27.85) = 49 42
            if (inputs.rt5) {
                outputs.leftStickX = 128 + (directions.x * 53);
                outputs.leftStickY = 128 + (directions.y * 28);
            }

            /* Extended Up B Angles */
            if (inputs.rf1) {
                // (33.29) = 67 44
                outputs.leftStickX = 128 + (directions.x * 67);
                outputs.leftStickY = 128 + (directions.y * 44);
                // (39.38) = 67 55
                if (inputs.rt2) {
                    outputs.leftStickX = 128 + (directions.x * 67);
                    outputs.leftStickY = 128 + (directions.y * 55);
                }
                // (36.18) = 67 49
                if (inputs.rt3) {
                    outputs.leftStickX = 128 + (directions.x * 67);
                    outputs.leftStickY = 128 + (directions.y * 49);
                }
                // (30.2) = 67 39
                if (inputs.rt4) {
                    outputs.leftStickX = 128 + (directions.x * 67);
                    outputs.leftStickY = 128 + (directions.y * 39);
                }
                // (27.58) = 67 35
                if (inputs.rt5) {
                    outputs.leftStickX = 128 + (directions.x * 67);
                    outputs.leftStickY = 128 + (directions.y * 35);
                }
            }

            // Angled fsmash/ftilt with C-Stick + MX
            if (directions.cx != 0) {
                outputs.rightStickX = 128 + (directions.cx * 127);
                outputs.rightStickY = 128 + (directions.y * 59);
            }

            // Angled Ftilts
            if (inputs.rt1) {
                outputs.leftStickX = 128 + (directions.x * 36);
                outputs.leftStickY = 128 + (directions.y * 26);
            }
        }
    }

    if (inputs.lt2) {
        // MY + Horizontal (even if shield is held) = 41
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 25);
            // MY Horizontal Tilts
            if (inputs.rt1) {
                outputs.leftStickX = 128 + (directions.x * 25);
            }
        }
        // MY + Vertical (even if shield is held) = 53
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 25);
            // MY Vertical Tilts
            if (inputs.rt1) {
                outputs.leftStickY = 128 + (directions.y * 25);
            }
        }

        /* Up B angles */
        if (directions.diagonal && !shield_button_pressed) {
            // MY + q1/2/3/4 = 35 59
            outputs.leftStickX = 128 + (directions.x * 25);
            outputs.leftStickY = 128 + (directions.y * 25);
            if (directions.x == -1) {
                outputs.leftStickX = 128 + (directions.x * 25);
                outputs.leftStickY = 128 + (directions.y * 25);
            }
        }
    }

    if (inputs.rf7) 
    {
        // left bumper is the "mode" switch, it overrides things
        outputs.leftStickX = 128 + (directions.x * 1);
        outputs.leftStickY = 128 - 69 + (directions.y * 1);
        if (inputs.lt2) {
            // tilt plus mode gives only horizontal displacement
            outputs.leftStickX = 128 + (directions.x * 59);
            outputs.leftStickY = 128 - 69;
        }
    }

    if (inputs.mb2) // Select Input for Remapping (Turn Around Modifier)
    {
        outputs.leftStickX = 128 + (directions.x * -37);

    }


    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    if (directions.cx != 0 && directions.cy != 0) {
        // 5250 8500 = 42 68
        outputs.rightStickX = 128 + (directions.cx * 42);
        outputs.rightStickY = 128 + (directions.cy * 68);
    }

    if (inputs.lf4) {
        outputs.triggerLAnalog = 140;
    }

    if (inputs.rf5) {
        outputs.triggerRAnalog = 140;
    }

    // Shut off C-stick when using D-Pad layer.
    if ((inputs.lt1 && inputs.lt2) || inputs.nunchuk_c || inputs.lf5) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
