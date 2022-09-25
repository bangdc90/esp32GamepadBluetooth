/*
 * This example turns the ESP32 into a Bluetooth LE gamepad that presses buttons and moves axis
 *
 * At the moment we are using the default settings, but they can be canged using a BleGamepadConfig instance as parameter for the begin function.
 *
 * Possible buttons are:
 * BUTTON_1 through to BUTTON_16
 * (16 buttons by default. Library can be configured to use up to 128)
 *
 * Possible DPAD/HAT switch position values are:
 * DPAD_CENTERED, DPAD_UP, DPAD_UP_RIGHT, DPAD_RIGHT, DPAD_DOWN_RIGHT, DPAD_DOWN, DPAD_DOWN_LEFT, DPAD_LEFT, DPAD_UP_LEFT
 * (or HAT_CENTERED, HAT_UP etc)
 *
 * bleGamepad.setAxes sets all axes at once. There are a few:
 * (x axis, y axis, z axis, rx axis, ry axis, rz axis, slider 1, slider 2)
 *
 * Library can also be configured to support up to 5 simulation controls
 * (rudder, throttle, accelerator, brake, steering), but they are not enabled by default.
 *
 * Library can also be configured to support different function buttons
 * (start, select, menu, home, back, volume increase, volume decrease, volume mute)
 * start and select are enabled by default
 */

#include <Arduino.h>
#include <BleGamepad.h>
#include <WiFi.h>
#include "FlySkyIBus.h"

BleGamepad bleGamepad;
QueueHandle_t joystick_q;

typedef struct joystick_command {
  /** @brief Button mask, allows 8 different buttons */
  uint16_t CH1;
  /** @brief X-axis value, 1000 - 2000 */
  uint16_t CH2;
  /** @brief Y-axis value, 1000 - 2000 */
  uint16_t CH3;
  /** @brief X-rotate value, 1000 - 2000 */
  uint16_t CH4;
  /** @brief Y-rotate value, 1000 - 2000 */
  uint16_t CH5;
  uint16_t CH6;
  uint16_t CH7;
  uint16_t CH8;
} joystick_command_t;

void setup()
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    
    BleGamepadConfiguration *config = new BleGamepadConfiguration();
    config->setVid(0x0483);
    config->setPid(0x5720);
    bleGamepad.begin(config);
    // The default bleGamepad.begin() above enables 16 buttons, all axes, one hat, and no simulation controls or special buttons

    IBus.begin(Serial2);
  
    // Set log level to >= INFO for all
    esp_log_level_set("*", ESP_LOG_INFO); 
  
    // Make sure the serial connection is real
    while(!Serial2)
    {
      delay(50);
    }

    joystick_q = xQueueCreate(32, sizeof(joystick_command_t));
}

void loop()
{
    joystick_command_t joystickCmd;
    uint16_t channels[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    IBus.loop();
    for(int i=0; i<8; i++)
    {
      channels[i] = IBus.readChannel(i);
    }

    if(bleGamepad.isConnected())
    {
      joystickCmd.CH1 = map(channels[0], 1000, 2000, 0, 32767);
      joystickCmd.CH2 = map(channels[1], 1000, 2000, 0, 32767);
      joystickCmd.CH3 = map(channels[2], 1000, 2000, 0, 32767);
      joystickCmd.CH4 = map(channels[3], 1000, 2000, 0, 32767);
      joystickCmd.CH5 = map(channels[4], 1000, 2000, 0, 32767);
      joystickCmd.CH6 = map(channels[5], 1000, 2000, 0, 32767);
      joystickCmd.CH7 = map(channels[6], 1000, 2000, 0, 32767);
      joystickCmd.CH8 = map(channels[7], 1000, 2000, 0, 32767);
   
      bleGamepad.setAxes(joystickCmd.CH1 ,joystickCmd.CH2, joystickCmd.CH3, joystickCmd.CH6, joystickCmd.CH4, joystickCmd.CH5, joystickCmd.CH7, joystickCmd.CH8);
    }

}
