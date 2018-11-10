/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>
#include "app.h"

/////////////////////////////////////////////////////////////////////////////
// Local definitions
/////////////////////////////////////////////////////////////////////////////
int enc_pushed[5] = {0, 0, 0, 0, 0};
int enc_pushed_previous[5] = {0, 0, 0, 0, 0};


/////////////////////////////////////////////////////////////////////////////
// This hook is called after startup to initialize the application
/////////////////////////////////////////////////////////////////////////////
void APP_Init(void)
{
  // initialize all LEDs
  MIOS32_BOARD_LED_Init(0xffffffff);

  // initialize pins
  int pin;
  for(pin=0; pin<8; ++pin)
    MIOS32_BOARD_J10_PinInit(pin, MIOS32_BOARD_PIN_MODE_INPUT_PU);

  for(pin=0; pin<8; ++pin)
    MIOS32_BOARD_J5_PinInit(pin, MIOS32_BOARD_PIN_MODE_INPUT_PU);

  // initialize rotary encoders
  int enc;
  for(enc=0; enc<10; enc++)
  {
    mios32_enc_config_t enc_config;
    enc_config = MIOS32_ENC_ConfigGet(enc);
    enc_config.cfg.type = DETENTED2;
    enc_config.cfg.sr = 0;
    enc_config.cfg.pos = 0;
    enc_config.cfg.speed = NORMAL;
    enc_config.cfg.speed_par = 0;
    MIOS32_ENC_ConfigSet(enc, enc_config);
  }
}


/////////////////////////////////////////////////////////////////////////////
// This task is running endless in background
/////////////////////////////////////////////////////////////////////////////
void APP_Background(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the main task which also handles DIN, ENC
// and AIN events. You could add more jobs here, but they shouldn't consume
// more than 300 uS to ensure the responsiveness of buttons, encoders, pots.
// Alternatively you could create a dedicated task for application specific
// jobs as explained in $MIOS32_PATH/apps/tutorials/006_rtos_tasks
/////////////////////////////////////////////////////////////////////////////
void APP_Tick(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the MIDI task which checks for incoming
// MIDI events. You could add more MIDI related jobs here, but they shouldn't
// consume more than 300 uS to ensure the responsiveness of incoming MIDI.
/////////////////////////////////////////////////////////////////////////////
void APP_MIDI_Tick(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a MIDI package has been received
/////////////////////////////////////////////////////////////////////////////
void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called before the shift register chain is scanned
/////////////////////////////////////////////////////////////////////////////
void APP_SRIO_ServicePrepare(void)
{
  u16 state;

  state = MIOS32_BOARD_J10_Get();

  MIOS32_ENC_StateSet(0, state & 3);
  MIOS32_ENC_StateSet(1, (state & 24) >> 3);
  MIOS32_ENC_StateSet(2, (state & 192) >> 6);

  enc_pushed[0] = (state & 4) >> 2;
  enc_pushed[1] = (state & 32) >> 5;

  state = MIOS32_BOARD_J5_Get();

  MIOS32_ENC_StateSet(3, (state & 6) >> 1);
  MIOS32_ENC_StateSet(4, (state & 48) >> 4);

  enc_pushed[2] = (state & 1);
  enc_pushed[3] = (state & 8) >> 3;
  enc_pushed[4] = (state & 64) >> 6;

  int i;
  for(i = 0; i < 5; i++)
  {
    if(enc_pushed[i] != enc_pushed_previous[i])
    {
        enc_pushed_previous[i] = enc_pushed[i];
        MIOS32_MIDI_SendCC(DEFAULT, Chn1, 20 + i, (1 - enc_pushed[i]) * 127);
    }
  }
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called after the shift register chain has been scanned
/////////////////////////////////////////////////////////////////////////////
void APP_SRIO_ServiceFinish(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a button has been toggled
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
void APP_DIN_NotifyToggle(u32 pin, u32 pin_value)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when an encoder has been moved
// incrementer is positive when encoder has been turned clockwise, else
// it is negative
/////////////////////////////////////////////////////////////////////////////
void APP_ENC_NotifyChange(u32 encoder, s32 incrementer)
{
  // toggle Status LED on each AIN value change
  MIOS32_BOARD_LED_Set(0x0001, ~MIOS32_BOARD_LED_Get());

  // NRPN
  MIOS32_MIDI_SendCC(DEFAULT, Chn1, 99, encoder);
  MIOS32_MIDI_SendCC(DEFAULT, Chn1, 98, 0);

  if (incrementer > 0)
    MIOS32_MIDI_SendCC(DEFAULT, Chn1, 97, 0);  // decrease
  else
    MIOS32_MIDI_SendCC(DEFAULT, Chn1, 96, 0);  // increase

}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a pot has been moved
/////////////////////////////////////////////////////////////////////////////
void APP_AIN_NotifyChange(u32 pin, u32 pin_value)
{
}

