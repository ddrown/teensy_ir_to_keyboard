#define CODE_NONE 0
#define CODE_MEDIA 1
#define CODE_CHAR 2
#define CODE_PRESS 3

#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int RECV_PIN = 13;

// change the below to 1 to enable i2c LCD-based debugging
#define LCD_ENABLED 0
const int I2C_LCD_ADDRESS = 0x3f;
const int I2C_LCD_WIDTH = 20;
const int I2C_LCD_HEIGHT = 4;

// http://source.android.com/tech/input/keyboard-devices.html page 0x07 (HID Keyboard and Keypad Page)
#define KEYCODE_BACK 0x40f1  /* needs 0x4000 to tell teensy usb layer to skip unicode */


// http://source.android.com/tech/input/keyboard-devices.html page 0x0c (HID Consumer Page)
#define KEYCODE_MEDIA_MUTE      0xe2
#define KEYCODE_MEDIA_VOLUP     0xe9
#define KEYCODE_MEDIA_VOLDOWN   0xea
#define KEYCODE_MEDIA_POWER     0x34
#define KEYCODE_MEDIA_MENU      0x40
#define KEYCODE_MEDIA_STOP      0xb7
#define KEYCODE_MEDIA_NEXT      0xb5
#define KEYCODE_MEDIA_PREV      0xb6
#define KEYCODE_MEDIA_PLAYPAUSE 0xcd
#define KEYCODE_MEDIA_PLAY      0xb0
#define KEYCODE_MEDIA_PAUSE     0xb1
#define KEYCODE_MEDIA_FASTFWD   0xb3
#define KEYCODE_MEDIA_REWIND    0xb4
#define KEYCODE_MEDIA_HOME      0x223
#define KEYCODE_MEDIA_SEARCH    0x221

IRrecv irrecv(RECV_PIN);
#if LCD_ENABLED
LiquidCrystal_I2C lcd(I2C_LCD_ADDRESS, I2C_LCD_WIDTH, I2C_LCD_HEIGHT);
#endif

void setup() {
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  Keyboard.begin();
#if LCD_ENABLED
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.print("Startup");
#endif
}

byte code_type = CODE_NONE;
char code_char = '\0';
uint16_t code_media_press = 0;

void send_ir_code(byte type, char code_char, int code_media_press) {
  if(type == CODE_NONE)
    return;

#if LCD_ENABLED
  lcd.clear();
#endif
  if(type == CODE_MEDIA) {
    Keyboard.set_media(code_media_press);
    Keyboard.send_now();
    delay(100);
    Keyboard.releaseAll();
#if LCD_ENABLED
    lcd.print("Media #");
    lcd.print(code_media_press & 0xff, HEX);
    lcd.print(",");
    lcd.print(code_media_press >> 8, HEX);
#endif
  } else if(type == CODE_CHAR) {
    Keyboard.print(code_char);
#if LCD_ENABLED
    lcd.print("CHAR =");
    lcd.print(code_char, HEX);
#endif
  } else if(type == CODE_PRESS) {
    Keyboard.press(code_media_press);
    delay(100);
    Keyboard.releaseAll();
#if LCD_ENABLED
    lcd.print("Press #");
    lcd.print(code_media_press, HEX);
#endif
  }
}

void loop() {
  decode_results results;

  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0x4AB0F7B6: // send+repeat
        send_ir_code(code_type, code_char, code_media_press);
        break;
      case 0x6AF21320: // Enter, works
        code_type = CODE_CHAR;
        code_char = '\n';
        break;
      case 0x4EBA0422: // left, works
        code_type = CODE_PRESS;
        code_media_press = KEY_LEFT_ARROW;
        break;
      case 0x5EA08104: // right, works
        code_type = CODE_PRESS;
        code_media_press = KEY_RIGHT_ARROW;
        break;
      case 0x9986485A: // up, works
        code_type = CODE_PRESS;
        code_media_press = KEY_UP_ARROW;
        break;
      case 0x1C6A919C: // down, works
        code_type = CODE_PRESS;
        code_media_press = KEY_DOWN_ARROW;
        break;
      case 0xDB2CD85E: // 1, works
        code_type = CODE_CHAR;
        code_char = '1';
        break;
      case 0x72C8CD04: // 2, works
        code_type = CODE_CHAR;
        code_char = '2';
        break;
      case 0xBFA12A36: // 3, works
        code_type = CODE_CHAR;
        code_char = '3';
        break;
      case 0xB8BAFCA0: // 4, works
        code_type = CODE_CHAR;
        code_char = '4';
        break;
      case 0x7ABBFE1A: // 5, works
        code_type = CODE_CHAR;
        code_char = '5';
        break;
      case 0xF1D5E280: // 6, works
        code_type = CODE_CHAR;
        code_char = '6';
        break;
      case 0x567912BA: // 7, works
        code_type = CODE_CHAR;
        code_char = '7';
        break;
      case 0xE4F97B5C: // 8, works
        code_type = CODE_CHAR;
        code_char = '8';
        break;
      case 0x6710681E: // 9, works
        code_type = CODE_CHAR;
        code_char = '9';
        break;
      case 0xB1966184: // 0, works
        code_type = CODE_CHAR;
        code_char = '0';
        break;
      case 0xC20DAA4F: // volup, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_VOLUP;
        break;
      case 0x4D6E48C9: // voldown, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_VOLDOWN;
        break;
      case 0x4D480CAB: // mute, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_MUTE;
        break;
      case 0xC2E92AD6: // play, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_PLAY;
        break;
      case 0xCA9582FA: // stop, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_STOP;
        break;
      case 0xB595064: // power, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_POWER;
        break;
      case 0xBE14D11A: // skip back, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_PREV;
        break;
      case 0x51CEC000: // scan back, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_REWIND;
        break;
      case 0xD380803A: // scan forward, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_FASTFWD;
        break;
      case 0x1E6BA628: // skip forward, works
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_NEXT;
        break;
      case 0x9BED8042: // disc menu = app menu
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_MENU;
        break;
      case 0x22CF7E40: // pause = playpause
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_PLAYPAUSE;
        break;
      case 0xA4F68FBE: // return = back
        code_type = CODE_PRESS;
        code_media_press = KEYCODE_BACK;
        break;
      case 0x82A4D940: // search
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_SEARCH;
        break;  
      case 0x3731A63E: // home
        code_type = CODE_MEDIA;
        code_media_press = KEYCODE_MEDIA_HOME;
        break;
  
      default:
        code_type = CODE_NONE;
#if LCD_ENABLED
        lcd.clear();
        lcd.print("Unknown");
        lcd.setCursor(0,1);
        lcd.print(results.value, HEX);
#endif
        break;
    }
    irrecv.resume(); // Receive the next value
  }
}
