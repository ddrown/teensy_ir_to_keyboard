NOTE: this needs the git repo https://github.com/ddrown/teensy_usb_android installed as your $ARDUINO_HOME/hardware/teensy/cores/usb_hid/ (be sure to save the previous contents!)

This needs the library LiquidCrystal_I2C (see http://www.dfrobot.com/wiki/index.php/I2C_TWI_LCD2004_(SKU:DFR0154) )
as well as the library IRremote (see https://github.com/shirriff/Arduino-IRremote.git )

remote used: LG remote AKB69491503

remote button = keyboard button
enter   = enter
left    = left
right   = right
up      = up
down    = down
1       = 1
2       = 2
3       = 3
4       = 4
5       = 5
6       = 6
7       = 7
8       = 8
9       = 9
0       = 0
volup   = volup
voldown = voldown
mute    = mute
play    = play
stop    = stop
power   = power
skip << = media prev
scan << = rewind
scan >> = fast fwd
skip >> = media next
d. menu = app menu
pause   = play/pause toggle
return  = back
search  = search
home    = homescreen


circuit:
VS1838B or other 38khz IR receiver wired to pin RECV_PIN

optional debug:
i2c LCD screen on the i2c pins with the following parameters: I2C_LCD_ADDRESS, I2C_LCD_WIDTH, I2C_LCD_HEIGHT
