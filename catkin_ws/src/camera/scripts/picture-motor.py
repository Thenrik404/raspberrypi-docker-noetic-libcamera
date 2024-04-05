import gpiod
import time
import numpy as np
from picamera2 import Picamera2, Preview
import cv2

picam = Picamera2()
for m in picam.sensor_modes:
   print(m)
mode = picam.sensor_modes[1]
print()
print(mode)
config = picam.create_video_configuration(
# config = picam.create_still_configuration(
   # {'format': 'SBGGR12'},
   # raw={'format': 'SRGGB12'},
   sensor={
      # 'output_size': (680, 680), 
      'output_size': mode['size'], 
      'bit_depth':mode['bit_depth'],
   }
)

picam.configure(config)
picam.set_controls({"FrameRate": 50})
picam.start()
# picam.video_configuration.controls.FrameRate. = 25.0
time.sleep(2)
s = 0.0001
s = 0.02
ENABLE_PIN = 17
DIR_PIN = 27
STEP_PIN = 22
chip = gpiod.Chip('gpiochip4')   
enable_pin = chip.get_line(ENABLE_PIN)
dir_pin = chip.get_line(DIR_PIN)
step_pin = chip.get_line(STEP_PIN)

enable_pin.request(consumer="LED", type=gpiod.LINE_REQ_DIR_OUT)
dir_pin.request(consumer="LED", type=gpiod.LINE_REQ_DIR_OUT)
step_pin.request(consumer="LED", type=gpiod.LINE_REQ_DIR_OUT)


def rotate_motor():
   dir_pin.set_value(1)
   steps_per_revolution = 200
   step_delay = 0.000790
   for i in range(steps_per_revolution):
      step_pin.set_value(1)
      time.sleep(step_delay)
      step_pin.set_value(0)
      time.sleep(step_delay)
      
   pass
fps = []
frames = []
print("starting")
t00 = time.time()
# csteps = 2
csteps = 101
try:
   for i in range(csteps):
         t0 = time.time()
         # frames.append(picam.capture_array("raw"))
         img = picam.capture_array()
         # cv2.imwrite(f'/home/henrik/Projects/camera/scripts/images/1.jpg', img)
         # time.sleep(0.5)
         # print(i)
         frames.append(img)
         rotate_motor()
         t1 = time.time()
         dt = t1-t0
         fps.append(1/dt)
finally:
   enable_pin.release()
   dir_pin.release()
   step_pin.release()

# print(np.shape(f))
for i, img in enumerate(frames):
   img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB ) 
   cv2.imwrite(f'/home/henrik/Projects/camera/scripts/images/{i}.jpg', img )

print(f'total_time {time.time()-t00}')
print(np.mean(fps))
picam.close()