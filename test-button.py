import RPi.GPIO as GPIO
import time

#button input:
GPIO.setmode(GPIO.BCM)
main_button_pin = 3
GPIO.setup(main_button_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
state_1 = GPIO.input(main_button_pin)

while True:
    button_state = GPIO.input(main_button_pin)
    if button_state != state_1:
      time.sleep(1)
      button_state = GPIO.input(main_button_pin)
      if button_state == state_1:
        print("shutdown")
      else:
        print("send data")
      state_1 = button_state
