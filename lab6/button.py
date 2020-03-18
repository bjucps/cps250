import RPi.GPIO as GPIO
import time

BUTTON_PIN=32        #Button to GPIO12
GPIO.setmode(GPIO.BOARD)

GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP) 

try:
    while True:
         button_state = GPIO.input(BUTTON_PIN)
         if button_state == False:
             print('Button Pressed...')
             time.sleep(0.2)
except:
    GPIO.cleanup()
    
