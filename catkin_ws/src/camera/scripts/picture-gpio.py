import gpiod
import time

from picamera2 import Picamera2, Preview


picam = Picamera2()
config = picam.create_preview_configuration()
picam.configure(config)

picam.start()
time.sleep(2)

LED_PIN = 17
chip = gpiod.Chip('gpiochip4')
led_line = chip.get_line(LED_PIN)
led_line.request(consumer="LED", type=gpiod.LINE_REQ_DIR_OUT)
try:
   while True:
        picam.capture_file("/home/docker/catkin_ws/src/camera/scripts/test-python.jpg")
        led_line.set_value(1)
        time.sleep(0.1)
        led_line.set_value(0)
        time.sleep(0.5)  # Sleep for one second

finally:
   led_line.release()

picam.close()