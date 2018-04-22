##
 #  @filename   :   main.cpp
 #  @brief      :   2.9inch e-paper display demo
 #  @author     :   Yehui from Waveshare
 #
 #  Copyright (C) Waveshare     September 9 2017
 #
 # Permission is hereby granted, free of charge, to any person obtaining a copy
 # of this software and associated documnetation files (the "Software"), to deal
 # in the Software without restriction, including without limitation the rights
 # to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 # copies of the Software, and to permit persons to  whom the Software is
 # furished to do so, subject to the following conditions:
 #
 # The above copyright notice and this permission notice shall be included in
 # all copies or substantial portions of the Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 # THE SOFTWARE.
 ##

from datetime import datetime
import epd2in9
import envoy
import time
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import peewee
from peewee import *
import RPi.GPIO as GPIO
import serial
import os

#button input:
GPIO.setmode(GPIO.BCM)
main_button_pin = 3
GPIO.setup(main_button_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
global state_1
state_1 = GPIO.input(main_button_pin)
global the_time_and_date
the_time_and_date = str(datetime.now())
global speed
speed = ""
global temp_1
temp_1 = ""
global temp_2
temp_2 = ""
global avg_temp 
avg_temp = ""
global humidity
humidity = ""
global alt 
alt = ""
global pressure
pressure = ""
global epd
epd = epd2in9.EPD()
epd.init(epd.lut_full_update)

current_time = time.time()
global last_time_screen
last_time_screen = current_time
global last_time_data
last_time_data = current_time
global screen_delay
screen_delay = .5 #minutes
global data_delay
data_delay = .65 #minutes


#mysql database stuff
db = MySQLDatabase('WeatherStationData', user='station', passwd='data')

delay_time = 100 #ms

class Data(Model):
    the_time_and_date = CharField()
    windSpeed = CharField()
    humidity = CharField()
    temp_1 = CharField()
    temp_2 = CharField()
    avg_temp = CharField() 
    altitude = CharField()
    pressure = CharField()
    
    class Meta:
        database = db

db.create_tables([Data])

port = '/dev/ttyUSB0'
rate = 115200
ser = serial.Serial(port, rate)
ser.flushInput()

def send_data():
    #optional
    print("sending data")
    my_path = os.path.dirname(os.path.abspath(__file__))
    envoy.run('./end-script.sh', cwd=my_path)

#screen input:
def show_on_screen():
    print("send to screen")
    global epd
    '''
    # For simplicity, the arguments are explicit numerical coordinates
    image = Image.new('1', (epd2in9.EPD_WIDTH, epd2in9.EPD_HEIGHT), 255)  # 255: clear the frame
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf', 16)
    draw.rectangle((0, 10, 128, 34), fill = 0)
    draw.text((8, 12), 'Hello world!', font = font, fill = 255)
    draw.text((8, 36), 'e-Paper Demo', font = font, fill = 0)
    draw.line((16, 60, 56, 60), fill = 0)
    draw.line((56, 60, 56, 110), fill = 0)
    draw.line((16, 110, 56, 110), fill = 0)
    draw.line((16, 110, 16, 60), fill = 0)
    draw.line((16, 60, 56, 110), fill = 0)
    draw.line((56, 60, 16, 110), fill = 0)
    draw.arc((60, 90, 120, 150), 0, 360, fill = 0)
    draw.rectangle((16, 130, 56, 180), fill = 0)
    draw.chord((60, 160, 120, 220), 0, 360, fill = 0)
    
    epd.clear_frame_memory(0xFF)
    epd.set_frame_memory(image.rotate(0, True), 0, 0)
    epd.display_frame()
    '''
    
    font = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf', 16)
    image = Image.new('1', (epd2in9.EPD_HEIGHT, epd2in9.EPD_WIDTH), 255)  # 255: clear the frame
    draw = ImageDraw.Draw(image)
    line_height = 20
    char_width = 5
    content = 'Anemometer Data:'
    draw.text(((epd2in9.EPD_HEIGHT / 2 - char_width * len(content)), line_height * 1 - 15), content, font=font, fill=0)
    content = 'Wind: ' + speed
    draw.text(((epd2in9.EPD_HEIGHT / 4 - char_width * len(content)), line_height * 2), content, font=font, fill=0)
    content = 'Humid: ' + humidity
    draw.text(((3 * epd2in9.EPD_HEIGHT / 4 - char_width * len(content)), line_height * 2), content, font=font, fill=0)
    content = 'Temp-1: ' + temp_1
    draw.text(((epd2in9.EPD_HEIGHT / 4 - char_width * len(content)), line_height * 3), content, font=font, fill=0)
    content = 'Temp-2: ' + temp_2
    draw.text(((3 * epd2in9.EPD_HEIGHT / 4 - char_width * len(content)), line_height * 3), content, font=font, fill=0)
    
    #If there´s time, display icons if cold or hot, windy or not windy, etc.
    
    epd.clear_frame_memory(0xFF)
    epd.set_frame_memory(image.rotate(270, expand=1), 0, 0)
    epd.display_frame()
    
    '''
    epd.delay_ms(2000)

    ##
     # there are 2 memory areas embedded in the e-paper display
     # and once the display is refreshed, the memory area will be auto-toggled,
     # i.e. the next action of SetFrameMemory will set the other memory area
     # therefore you have to set the frame memory twice.
     ##     
        epd.clear_frame_memory(0xFF)
        epd.display_frame()
        epd.clear_frame_memory(0xFF)
        epd.display_frame()

        # for partial update
        epd.init(epd.lut_partial_update)
        image = Image.open('monocolor.bmp')
    ##
     # there are 2 memory areas embedded in the e-paper display
     # and once the display is refreshed, the memory area will be auto-toggled,
     # i.e. the next action of SetFrameMemory will set the other memory area
     # therefore you have to set the frame memory twice.
     ##     
    epd.set_frame_memory(image, 0, 0)
    epd.display_frame()
    epd.set_frame_memory(image, 0, 0)
    epd.display_frame()

    time_image = Image.new('1', (96, 32), 255)  # 255: clear the frame
    draw = ImageDraw.Draw(time_image)
    font = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf', 32)
    image_width, image_height = time_image.size
    while (True):
        # draw a rectangle to clear the image
        draw.rectangle((0, 0, image_width, image_height), fill = 255)
        draw.text((0, 0), time.strftime('%M:%S'), font = font, fill = 0)
        epd.set_frame_memory(time_image.rotate(270), 80, 80)
        epd.display_frame()
    '''

def main():
    global state_1
    global the_time_and_date
    global speed
    global temp_1
    global temp_2
    global avg_temp 
    global humidity
    global alt 
    global pressure
    global last_time_screen
    global last_time_data
    global screen_delay
    global data_delay



    button_state = GPIO.input(main_button_pin)
    if button_state != state_1:
      time.sleep(1)
      button_state = GPIO.input(main_button_pin)
      if button_state != state_1:
        print("send data")
        send_data()
        print("shutdown")
        os.system('sudo shutdown now')
      state_1 = button_state
    #get data:
    data = str(ser.readline())
    print(data)
    data_parsed = [x for x in data.split(',')] #split by comma
    if len(data_parsed) > 7:
        if data_parsed[1] != "nan":
            speed = data_parsed[1]
        if data_parsed[2] != "nan":
            temp_1 = data_parsed[2]
        if data_parsed[3] != "nan":
            temp_2 = data_parsed[3]
        if data_parsed[4] != "nan":
            avg_temp = data_parsed[4]
        if data_parsed[5] != "nan":
            humidity = data_parsed[5]
        if data_parsed[6] != "nan":
            alt = data_parsed[6]
        if data_parsed[7] != "nan":
            pressure = data_parsed[7]
    
        #add data to database:
        datapoint = Data.create(the_time_and_date = str(datetime.now()), windSpeed = speed, humidity = humidity, temp_1 = temp_1, temp_2 = temp_2, avg_temp = avg_temp, altitude = alt, pressure = pressure)
        
        current_time = time.time()
        print((current_time - last_time_screen) / 100)
        if ((current_time - last_time_screen) / 100) > screen_delay:
            show_on_screen()
            last_time_screen = current_time

        if ((current_time - last_time_data) / 100) > data_delay:
            send_data()
            last_time_data = current_time

        #send data to github as csv...

        time.sleep(delay_time / 1000)

if __name__ == '__main__':
    while True:
        main()

