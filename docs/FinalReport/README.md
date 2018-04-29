Weather Anemometer Report

By Joshua Schmidt, Lorie Rosado, and Angelina Contreras

May 3, 2018

E-122-S Engineering Design II

Group 3

*I pledge my honor that I have abided by the Stevens Honor System.*

X_____________________Lorie Rosado______________________

______________________Angelina Contreras_______________________

_____________________Joshua Schmidt______________________

[[TOC]]

# Abstract

In Engineering Design II, students are expected to design, build, and code a weather station that is able to collect data such as wind speed, temperature, and humidity. This report goes over how the team planned and executed their ideas in order to meet the requirements of Engineering Design II. This includes the mechanical design, electrical wiring design, software design, as well as the trials and tribulations faced while making this design as efficient as possible. In conclusion, this report encompasses the group’s efforts and creative ability to build a weather station. 

# Table of Contents

[[TOC]]

# Discussion

## Requirements

	This project focuses on the creation of a field-ready weather station. The weather station is to be equipped with temperature, humidity, and wind speed sensors. The wind speed sensor, anemometer, which is designed by the students should read between 5-25 miles per hour, within a ± 1 mph accuracy. The temperature sensor should read between  0 and 110 °F within a ± 4 °F accuracy. Lastly, the humidity sensor should read between 20 and 80 % within a ± 5 % accuracy.

This weather station must be operable for at least seven days, and fit into a 12" (304.8 mm) x 12” x 12” envelope including the 4” dia x 6” tall PVC pipe where all components that need to be protected from the elements are contained. Using LabView as a graphical user interface (GUI), the following data will be neatly recorded:

* Time interval selection

* Time history of wind speeds, humidity, and temperature (instantaneous and historical)

* High and low values for selected time periods

Besides this, the weather station must be easily maintainable and able to withstand the following environmental conditions:

* Temperature range between -10  and 120 °F

* Wind gusts of up to 50 mph

* Include a picture of the entire thing outside

* Picture of our Labview 

## System Design (ANG will do this)

1. Write a detailed report with block  diagrams detailing the functionality of each subsystem. Use a top-down approach (system, subsystem, component) to describe mechanical, electrical and software components. Identify all connections and interfaces (mechanical, electrical, and data) 

1. Discuss the overall evolution of your system design. Discuss the steps taken and the results obtained. Much of this information can be found in the various submissions you generated during the course of the semester.

2. Provide details of your final design. Include both a system block diagram showing the various major system components and the interface between those components.

* Include picture of ???

## Mechanical Design (LORIE will do this)

A completed SolidWorks model of the assembly and all parts  (submit as Zip file)  with appropriate part numbering. Follow a part file naming protocol that identifies your section, team number, and the part number. Eg. E122M_5_M555-2.sldprt indicating section M, team 5 with mechanical part number M555-2. 

    1. Bill of Materials: Include Quantities and Associated costs (if applicable).

    2. Show exploded view and views of components in the Appendix. 

*   Provide the details of your system’s mechanical design. What materials were used? What were the major components and how were they produced? Include CAD drawings for any components that were 3D printed or laser cut.

* Include picture of previous designs, find them submitted 

* Include picture of final design

* Include key parts of final design

    * All the brackets and shit

* Explain how we didn’t need the PVC pipe

## Electrical and Wiring Design

### Overview

When deciding the electrical and wiring design, the team focused on creating a system that is scalable and includes the features required for this project, while also providing the ability to complete remote data analysis and analytics. At the core of the system is the Wemos D1 R2 development board, which completes the initial data acquisition from the integrated sensors of the weather station. The sensors themselves are the next entity, and the BMP-180 and DHT-22 were used to gather the necessary weather data. Additionally, a rotary encoder was used for the wind-speed anemometer apparatus. A raspberry pi was responsible for the main data collection and processing, and an off-the-grid system provided power to the whole apparatus. This system ensures that sensors can easily be attached to the wemos and integrated into the weather station, without much modification to the code or circuits. Additionally, the system can be run indefinitely because it is reliant on a solar panel for power. Therefore, this approach was arguably the best for this project, as it enables the weather station to be utilized in many different ways in various situations.

### Wemos D1 R2

#### ESP8266

The Wemos D1 R2 is based on the ESP8266 chip, which is a low-cost wifi microchip and microcontroller produced by Shanghai-based manufacturer, Espressif Systems. It has a 32-bit processor running at 80 MHz with 32 KiB of RAM, 32 KiB of cache, 80 KiB of user data RAM, and 16 KiB of system data RAM. The processor is a Tensilica L106 32-bit RISC microprocessor. The datasheets for this microchip, in addition to the general schematic of the ESP8266, can be found here: [https://goo.gl/gqzxCk](https://goo.gl/gqzxCk), [http://bit.ly/ESP8266EX](http://bit.ly/ESP8266EX). The ESP8266 Technical reference, instruction set, and command examples can be found here: [http://bit.ly/ESP8266-TechRef](http://bit.ly/ESP8266-TechRef), [http://bit.ly/ESP8266-AT-Insts](http://bit.ly/ESP8266-AT-Insts), [http://bit.ly/ESP8266-AT-CmdEx](http://bit.ly/ESP8266-AT-CmdEx).

#### Wemos

Wemos is a small company based out of Shenzhen, China, and creates the Wemos D1 R2 in addition to the D1 mini, D1 mini pro, D1 mini lite, and others. These boards are primarily based on the same processor - the ESP8266EX. For more information on the company go to [https://www.wemos.cc/](https://www.wemos.cc/).

#### D1 R2

The Wemos D1 R2, is a wifi capable microcontroller-based development board based on the ESP8266EX, in the form of an Arduino UNO. It can be programmed via the Arduino IDE, as it was in this project, and features an on-board switching power supply that can take from 5 - 12 V. In this case the input power was 5V. It is a 3.3V device, so only sensors with 3.3V logic work, unless a logic-level converter is used.

Wemos D1 R2 Schematic ([http://bit.ly/D1-R2-Schematic](http://bit.ly/D1-R2-Schematic)):

![image alt text](image_0.png)

### The Sensors

#### The Anemometer rotary encoder

The Anemometer rotary encoder was created using a disc with 32 hole cut-outs, in addition to a H21A1/2/3 phototransistor optical interrupter switch. Also known as a break beam sensor, this sensor would return a HIGH or LOW if there is a something blocking the sensor or if the sensor reads an opening. In the mechanical design, the encoder reads a wheel with uniform holes punched on the outer rim, so if the encoder reads an opening, at that specific time the encoder would return a 1. And if there is no opening, the encoder would return a 0. Using the encoder as a digital input pin, the program can convert this data into mph, or another unit of wind speed. The datasheet can be found here: [https://goo.gl/RhPdLA](https://goo.gl/RhPdLA). 

#### The DHT-22

The DHT-22 sensor measures temperature and wind-speed, and sends this data via a digital GPIO pin. It does not require i2c because it is not an analog signal, and it does not start outputting its status until it receives a pulse from the MCU host. If it was hooked up to an i2c ADC, the sensor would not output anything. The datasheet for the DHT-22 can be found here: [https://goo.gl/PWb9US](https://goo.gl/PWb9US). 

#### The BMP-180

The BMP-180 sensor measures pressure, altitude, and temperature. This sensor was not required for this project, but was added on anyway because it is ubiquitous for this weather-data gathering purpose. This sensor uses I2C for data transfer. I2C is great because it only requires 2 wires, unlike SPI, which requires 5, and it can support up to 1000 devices. Additionally, this system can have multiple masters on the same bus. See [https://goo.gl/Y5ewC4](https://goo.gl/Y5ewC4) for more information. The datasheet for this sensor can be found here: [https://goo.gl/YBRBK4](https://goo.gl/YBRBK4). 

### Wemos and Sensors Connections

The physical Wemos pins are different from the digital logic pins of the board, primarily because the library used to compile the code for the ESP8266 is generalized for all development boards that use that microchip, and not for Wemos in particular. Therefore, the following chart was utilized when converting from the physical pinout of the Wemos to the programming logic:

![image alt text](image_1.png)

The DHT-22 temperature and humidity sensor was connected to GPIO0, which on the Wemos pinout is D3. The DHT-22 uses the DHT library, which is standard for Arduino libraries and is a submodule in the github repo, linked in the programming section of this report. The anemometer encoder uses GPIO 14, which is D5 on the physical wemos. The BMP 180 uses the SCL and SDA pins on the Wemos, which is D1 and D2, or GPIO5 and GPIO4, respectively. The circuit diagram for the sensors can be found below:

CIRCUIT DIAGRAM FOR SENSORS:

### The Power System

#### The Solar Panel

The solar panel used was a 12-inch 10-watt 12V panel. This was used for the off-the-grid regeneration aspect. The product page can be found here: [http://a.co/03zslCS](http://a.co/03zslCS).

#### The Battery Charging Circuit

The circuit used to charge the battery was a USB DC Solar Lithium Ion charger v2 from Adafruit. It has a 6V input, so a voltage divider was used between the solar panel and the charging circuit, dropping the voltage from 12V to 6V. The product page can be found here: [https://www.adafruit.com/product/390](https://www.adafruit.com/product/390). The charging rate of the battery was increased to 1A by soldering a 1kOhm resistor on the relevant pads, as per the documentation, and a 10K NTC thermistor was added to add temperature - shutoff protection if the battery gets too hot at any time. The datasheets can be found here: [https://goo.gl/T4BmQ8](https://goo.gl/T4BmQ8). Below are the circuit diagrams and schematics:

![image alt text](image_2.png)

![image alt text](image_3.png)

#### The Battery

The battery used was a 6600mAh lithium ion battery pack, at 3.7V, composed of 3 standard 18650 battery cells made by Samsung, each at 2200mAh. Each cell can provide 0.5C (1.1A) of current at peak loads of over 3.3A. It uses a JST jack, making good compatibility with the charging circuit above. The battery pack includes over-charging and voltage protection. See the product page here: [https://www.adafruit.com/product/353](https://www.adafruit.com/product/353).

#### USB female buck converter

A female usb buck converter was used to convert the 5V output of the battery charging circuit to a female USB port at a constant 2A to provide a good supply of power for the raspberry pi to run off of. The USB was connected directly to the charging circuit output, and the product page can be found here: [http://a.co/8t7NNjP](http://a.co/8t7NNjP). 

#### Power Consumption

Power consumption for the Raspberry Pi (below) and the Wemos (above) were calculated to be 120 mA and 80 mA at max, or 200 mA total. Sources: [https://goo.gl/nfo96S](https://goo.gl/nfo96S), [https://goo.gl/anSQF3](https://goo.gl/anSQF3). So with this current draw, and the battery of 6600 mAh, this circuit would theoretically last for 33 hours, or 24 hours to be safe. And the solar panel produces 10 watts every hour, and at 12V that produces 833 mA per hour. So this solar panel is producing far more energy at peak production than is required, and at 500 mA accounting for energy loss. So this panel will theoretically allow for the pi to run indefinitely, as it can produce more than twice the energy needed, preventing cloudy days and the inevitable sunset from also shutting down the data collection. Since the battery circuit never shuts down and the difference in energy consumption from the code is negligible, few steps were taken to reduce energy consumption. One step that was taken was to send data to the github repo every 15 minutes, and refresh the e-ink display every 30 minutes, instead of refreshing them every time the program loops.

### The Raspberry Pi

The last step of the equation is the raspberry pi, essentially connecting this entire project together. The pi gets power from the USB buck converter, as a micro-usb input, and then outputs that power via a micro-usb to micro-usb cable to the Wemos board. Data is transferred through this same between the Pi and the WeMos.

The Raspberry Pi used was a Raspberry Pi Zero, mainly because the processing power did not have to be very high for this project, and the power draw is very low, at about 120 mA at peak use.

The Raspberry Pi Zero W is essentially a low-power, low-cost arm-based computer, and the configuration used runs linux Raspbian, software designed specifically for the raspberry pi. The Pi is powered by a single-core 1GHz ARM v7 system on a chip (SoC), and 512 MB of RAM. Again, this is not a large amount of processing power, but it is sufficient for this project. Full schematics and documentation about the board can be found here: [https://goo.gl/f639zk](https://goo.gl/f639zk). 

#### Raspberry Pi Schematic

![image alt text](image_4.png)

The Raspberry Pi was chosen for this project to process the data coming from the Wemos via the usb cable and save it to a database. The database data was then sent to a github profile, where a simple Github pages website shows the data. This process is further explained in the software design and coding section below, but essentially having the pi allows for the data to be saved to the cloud and then shown concisely in a webpage.

#### The E-Ink Display

One more feature the Raspberry Pi enables is to have different displays and input on the weather station itself. The display used was a 2.9 inch e-ink display created by Waveshare, which has 298x128 resolution, and uses SPI interface to communicate with the Pi. The product page can be found here: [http://a.co/hb4rQ3Y](http://a.co/hb4rQ3Y). The datasheet and more information about using the module can be found here: [https://www.waveshare.com/wiki/2.9inch_e-Paper_Module](https://www.waveshare.com/wiki/2.9inch_e-Paper_Module). The hardware connection to the Pi is as per the following pinout:

![image alt text](image_5.png)

The hardware pins on the Raspberry Pi 3B and Zero W are the same.

#### Push Button

A waterproof push button was also used as input to the raspberry pi, mainly as an on and off switch for the entire station. This was wired to GPIO pins 5 and 6 of the PI, which when shorted turns on the Pi. Part of the python script shown in the programming section uses GPIO pin 5 as input so when the button is pressed, a script is started that saves the data to the cloud and shuts down the Pi safely.

#### Raspberry Pi Pinout

![image alt text](image_6.png)

#### Conclusion

None of this extra functionality - the website, the data-collection and storage in a mysql database, would have been possible without the Pi. And the Pi added amazing functionality to this weather station, adding a display, tactile inputs, and many sensors that could be modularly added to the system. And the off-the-grid circuit with the solar panel allows for data collection from anywhere, at anytime. Even if there is no wifi, the data is stored on the Pi, to be uploaded in the future, with up to 16Gb of storage in remote locations. This system, as implemented, is the best way to create a mobile weather station.

## Software Design and Coding

The software is arguably the integral part of this project, allowing for the data to be collected, processed and then distributed and visualized. To that end, there were four mediums in which software was written. Software was created for the Wemos development board to get the sensor data and send it, for the Raspberry Pi Zero W to interpret that data and distribute it, for the Github pages Bootstrap Javascript webpage for visualization, and on NI Labview for visualization.

These software aspects are discrete in that they take data from one and send it to the next, meaning they were developed independently and integrated afterwards. All of the code that will be referred to is copied in the appendix but is originally on this Github page: [https://github.com/jschmidtnj/MobileWeatherStation](https://github.com/jschmidtnj/MobileWeatherStation). 

### Github

Github is a cloud storage solution for git, which is a software-revision platform. Github was used to allow for collaboration when developing the code, and to allow for the most up-to-date code to be on all of the components of this project. Each time the Pi loads, it runs a script (startup.sh), which creates a fresh copy of this github repository. This ensures that the Pi always has the newest code (read more about git and github here: [https://goo.gl/FHmTgf](https://goo.gl/FHmTgf)).

#### Github Pages

Additionally, Github has a service called Github pages, which allows for Github to act as a web-server for static websites - that is, websites that have discrete html documents which do not change for each user. The website created for showing the data for this project is hosted on Github under the "docs" folder, and can be accessed from the domain [https://anemometer.ml](https://anemometer.ml). Github pages is great because it allows for all of the code for this project to be stored in one place - on that same Github repo, even though the code is comprised of many different systems and parts, as per above.

The only aspect not included in this github repository that is software is the NI Labview application. It would not make sense to include this application because it is not text-based code, so every time there would be a git commit it would just store the file. Github would essentially act like cloud storage at that point, as opposed to a revision-based management system. Therefore the Labview application was stored separately.

### The Flow

![image alt text](image_7.png)

This is essentially the flow of these systems. The sensors send data to the Wemos, and over the USB cable it gets transmitted to the Raspberry Pi. The Data is also sent to a local storage system on the Stevens network, where it is parsed to a csv file. The Raspberry Pi processes the data and saves it to a mySQL database, and a script then saves that data to a csv file. The csv file is uploaded to Github. When people open the website, [https://anemometer.ml](https://anemometer.ml), the javascript file scripts.js runs and processes the data from the csv file on github, adding the data to graphs that are compiled and placed in the html document index.html, on the user’s computer. As the data refreshes every 15 minutes, the website refreshes and users can see the updated data coming in. That way, the data shown is always up-to-date. Finally, a csv document can either be downloaded directly from the Github page or from Stevens servers, to be inputted to the Labview environment. There users can see the data in different graphical forms, and can interpret the data in different ways.

### Wemos code

In this report, the code will be read from top to bottom, following the logic of the program as opposed to the order it was written in, and explained in detail. The best way to follow along is to view the code on github: [https://goo.gl/w8TTPE](https://goo.gl/w8TTPE) as it is explained. In lines 19-28, the various libraries necessary are initialized. ESP8266wifi is self explanatory, PubSubClient and info are for connecting with the Stevens servers to send data, DHT and SFE_BMP180 are for the two sensors, and Wire is for the I2C protocol mentioned in the wiring section. The Running Median library was used to calculate a median of the wind speed, so there are no outliers in the data. The reason why this was not calculated manually was because the C that the Arduino IDE uses does not allow for array lists, and initializing an array each time a value needs to be added would be memory-intensive. This running median library does what is needed with the smallest overhead possible.

The constants on lines 35 and 36 are for the id and password of the Stevens Network. On lines 42-44, the Stevens mySQL server settings that the wemos is accessing to enter the data are initialized. Magic Word is also needed. Lines 50-52 include constants that are used later in the program for publishing delays. Lines 62-65 set up the DHT sensor to pin 0, and on line 73 the anemometer sensor pin is initialized (see electronics section). Lines 76-84 are constants used for interpreting the anemometer data, in the RunningMedian loop (lines 341-361). Lines 86-88 are constants used throughout the program. Line 86, num_loop, is the number of times the wind-speed is calculated and added to the running-median data set. The mult_constant is the calibration constant for the anemometer, and was found by dividing the actual wind-speed (gained from a professional anemometer) by the reading from the custom anemometer sensor created for this project. The delay_in_between is used for the delay between anemometer readings in the loop to gain wind speed readings. Without this variable, the readings would be taken nearly instantaneously, at the clock-speed of the Wemos, which is much faster than the encoder wheel can ever spin. This is measured in milliseconds.

Lines 101-107 initialize self-explanatory values for each of the sensors, and on 109 the current altitude of Hoboken, NJ, is recorded in meters. Lines 146-153 are the configuration of the wificlient and mysql topic, used to communicate and send data to the Stevens server. Lines 154-156 initialize the sensor data variables to be sent to the Stevens server, as do lines 157 and 158. 

#### Setup Function

After this initialization the program goes into the void setup() loop, on lines 250-269. On lines 251 and 252, the built-in LED is initialized as an output and the anemometer pin is initialized as an input. The Serial communication is started on line 253, at a baud rate of 115200. Then on line 264 the setup_wifi() function is called, which starts the wifi connection to the Stevens server. This will not be gone into much detail because it was preconfigured. Then on line 265 the program enters the setup_alt_temp function, which starts the BMP180 sensor. Line 266 starts the DHT sensor, and lines 267-268 wait for a callback from the Stevens server. After the setup loop, the program goes into the main void loop () to be run repeatedly (lines 271-318.

#### Loop Function

The loop function starts on lines 273-276 by checking if the Stevens server is connected, and if not, reconnects to the server. Lines 278-279 check if the time between the last message and the current time is greater than the publish delay, and if it is it publishes the data in the if statement. Line 282 re-initializes the lastMsg variable, and lines 283-284 are where the temperature and humidity read by the DHT sensor is read and stored. Next line 285 goes into the loop_alt_temp function, lines 289-557, which stores the pressure, altitude, and temperature from the BMP180 sensor, and stores the values. Lines 286-295 are for publishing the data to the Stevens mySQL database. In line 298, the wind_speed_samples variable, of type RunningMedian, is created from the get_speed function (lines 341-361).

#### get_speed Function

In the get_speed function, the wind-speed read by the anemometer is calculated. This is done by comparing two modes - mode_1_speed and mode_2_speed, which are both boolean values. mode_1_speed is defined by the digital reading of the anemometer signal pin, so if the two modes are equal, there has been one movement from a hole to the next hole. The current time that this occurs is recorded on line 349, in microseconds since the program started. And if the print_now variable is true, which occurs every second time the program goes through the if statement on line 350. Then on line 352, the value of the wind_speed_sample is stored in the RunningMedian type variable. The multiplication constant is used to account for the physical errors of creating the anemometer - its inertia and friction in the system, and was calculated as explained earlier through experiment. The wind_speed was calculated by dividing the circumference of the wheel (in miles) by the time it took for the movement in the encoder. This time is in microseconds, so it was converted to hours. The multiplication constant takes care of any logical errors in the calculation, to ensure the data gathered from the anemometer is accurate.

#### The loop again

On lines 297-300, the wind_speed_samples are found and averaged. The average is found using the for loop. Then the average temperature from the BMP180 and DHT22 sensors was calculated on line 302. In lines 310 and 311, the temperature and humidity are printed to Serial, and on line 312 the string of data the Pi will interpret is sent to the Serial, at a baud rate of 115200. This data then goes through the USB cable to the Pi, where is it processed (see below for an explanation of this process). Finally, the loop function sleeps for the length of the SLEEP_DELAY (in milliseconds).

#### Flow Chart

![image alt text](image_8.png)

### The Pi

Now that the Wemos data collection code is explained, it is necessary to explain how the Raspberry Pi Zero works in this equation. When the Raspberry Pi starts up, it is configured so that in shell it runs the startup script (./startup.sh). 

#### startup.sh

In this script, as you can see in the appendix or here: [https://goo.gl/NCVAXu](https://goo.gl/NCVAXu), the pi accesses the directory of the github repository, in the Desktop "MobileWeatherStation" (line 1). One line 2, the Pi pulls the newest code from the github repository, ensuring that the programs that are on the pi are up to date. Lien 3 creates a variable called ip4 that stores the ip address of the pi at that moment, and line 4 adds that variable to a new line in the file ip-address.txt, also in the MobileWeatherStation directory. The purpose of this step, of saving the ip address to the github repository, is to allow for me to access the pi via ssh (secure shell, read more here: [https://www.ssh.com/ssh/](https://www.ssh.com/ssh/)). The Stevens network uses dynamic ip addresses, meaning every day or so the ip-address of the Pi changes on the network, especially if the Pi was off and then was turned on. By saving the ip address, I can look at this ip-addresses.txt file on github and see the current ip before ssh-ing to the Pi (the file is located here: [https://goo.gl/MjDMhS](https://goo.gl/MjDMhS), and you can see how the ip changes sometimes). Lines 5-7 add, commit, and push these changes to the ip address to the online github repository. Line 8 starts the python script testdisplay.py, which is used to test the weather station’s e-ink display. And after that python script is done, the script app.py runs, which does all of the data processing and display of the data from the Wemos.

#### testdisplay.py

The testdisplay.py python script is a heavily modified python script originally created by waveshare to test this display (see the code here: [https://goo.gl/vVnTNx](https://goo.gl/vVnTNx)). It prints the labels of the data - "Anemometer Data: “, “Wind Speed: “, “Humidity: ", “Temp 1: ”, and “Temp 2: ” to the screen. Lines 27-31 are import statements for the necessary python scripts, as provided by Waveshare. On lines 122-123, the function enters the main loop. In the main loop, the e-ink display is initialized as a 2.9 inch display on line 32. And then updated on line 35. Line 60 initializes the font for the text, and line 61 creates the image to be sent to the the e-ink display. Lines 63-64 create the character width and height of the lines of text, and lines 66 through 74 create the text as per above and draw the text to the image. Line 78 clears the memory of the display, and line 79 sets the memory of the frame to be the rotated image 270 degrees, because the display is mounted in the weather station upside-down. Finally line 80 displays the frame that was created in lines 60-74. At the end of this python script, the labels of the e-ink display are printed, and the display is verified as tested and working.

#### app.py

After the testdisplay.py the Pi enters the app.py python script, written again in python 3 (see [https://www.python.org/doc/essays/blurb/](https://www.python.org/doc/essays/blurb/) for more information about python). I will again go line by line, so be sure to follow along at this link: [https://goo.gl/Eq4B6u](https://goo.gl/Eq4B6u) or in the appendix. Lines 27-38 are import functions for the various libraries used in this script. Note that the same libraries used in testdisplay.py were used here as well. Lines 41-43 initialize the physical on-off button for the weather station, and lines 44-45 create a variable state_1 that is the initial state of the switch. The variables for wind speed, temperature, humidity, altitude and pressure are defined on lines 46-59 as global variables, meaning they can be accessed by any function, and the variable for the e-ink display is initialized in lines 62-64, also as a global variable, in the same fashion as in the testdisplay.py script. Lines 66-74 are where global variables for different functions, such as the current time, the delay between each screen refresh, and the delay between each data push, are initialized. Lines 77-78 define the mySQL database used - "WeatherStationData", with the user being “station” and the password being “data” for the database. The delay time on line 80 is the delay in between each loop of the main() function (lines 197-259).

#### Peewee Library and Class

The Peewee library is used for inputting mySQL database information via a python script. Lines 82-93 create a class called Data that creates the character fields for each of the data-points that are inputted into the mySQL database, in the "Data" table. The class Meta initializes the database to default to the name db. For more information on Peewee, see [http://docs.peewee-orm.com/](http://docs.peewee-orm.com/). Line 95 creates the Data table in the WeatherStationData database, with the charfield parameters for each of the data-points. 

Lines 97-100 create the serial connection to the Wemos device through the usb port, with the baud rate of 115200, and flush the input. On lines 261-263, the main() loop (lines 197-259) is called forever, using a while True: statement. 

#### main loop

The main loop starts by initializing the priorly-created global variables on lines 198-210. Then on line 214 the state of the button is recorded, and if it different from the initial state, the Pi sends the data to the github repo via the send_data() function on line 220. The send_data function (lines 102-106) uses the os and evoy libraries to run the end-script.sh script.

##### end.sh script

The end.sh script ([https://goo.gl/cLZtGd](https://goo.gl/cLZtGd)) starts by starting the squ-to-csv.sql mySQL script on line 4 ([https://goo.gl/NonnHp](https://goo.gl/NonnHp)). This mySQL script takes the WeatherStationData mySQL database and selects all of the data, outputting it into a csv file called data.csv in the directory /tmp/. Then lines 5 and 6 change the file permissions, and line 7 goes into the tmp directory. Lines 8-10 create a new filename for the data.csv file from the current date, time, year, etc., and line 11 moves this new file to the data folder of the WeatherStationData git repository. Line 12 clears the file current_data_file.csv of its data, and line 13 fills that file with the data from the newly created file, and puts the current_data_file.csv in the git repository. Lines 14-17 navigate into the git repository, add all of the changes, commit the changes with the message "added data files", and push these files to github.

##### main loop

After the end_script.sh script is called on line 106, the program returns to the main loop, and on lines 221-222 the Pi shuts down. If the button was not pressed, the program does not go into the if-statement on lines 218-222 and instead records the current button state on line 223. On line 225, the program reads the incoming data from the serial port, connected to the Wemos. Line 227 splits this data into an array by comma, and lines 228 through 242 save this data into the discrete variable for each data point. The program checks if the datapoint is equal to "nan" and “0.00” because sometimes the sensors do not register an accurate value, and instead return “nan”. Through this method, every time the sensors do not produce an accurate reading, the data stays the same as it was before.

Lines 244-245 add the data to the mySQL database, and line 247 updates the current_time variable. Lines 249-251 send the data to the screen using the show_on_screen function, if the time delay is larger than the variable screen_delay (in minutes). The show_on_screen function (lines 109-195) is very similar to the code used for the testdisplay.py script explained above, but substituting the actual values of the current data-points.

Finally lines 253-255 send the data to the mysql database, and to the github repository, through the same method, using a time delay of "data_delay". Then on line 259 the program sleeps for delay_time, in milliseconds. 

##### conclusion

With app.py explained, all of the python programs are now finished describing. The Wemos reads sensor data and sends it to the Pi over the USB cable, where app.py sends the data to the database and to the e-ink display after a time delay, and every time the method loops to the mySQL database. Now the next aspect of the software that has not been explained yet is the website.

### The Website

In the appendix, and under the "docs" folder of the github repository ([https://goo.gl/rsnV4i](https://goo.gl/rsnV4i)), there is the file index.html. This is the main html file for the website, [https://anemometer.ml/](https://anemometer.ml/). When you enter anemometer.ml into your browser, the domain name service (DNS) Freenom, through which the domain name was registered, redirects the nameservers to Cloudflare (read more here: [https://goo.gl/2sR1um](https://goo.gl/2sR1um)), where Cloudflare attaches an ssl certificate (read more here: [https://goo.gl/k8RC3C](https://goo.gl/k8RC3C)) and redirects the user to the github pages repository, linked above in the docs folder. The index.html page is loaded, and this page is rendered to display all of the weather station data.

This page uses bootstrap ([https://goo.gl/xRMvFi](https://goo.gl/xRMvFi)) as the library framework, making it easy to create material-design ui styling ([https://material.io/guidelines/](https://material.io/guidelines/)) and advanced, modern elements. I will not go into extreme detail about how the html page was created, because it is fairly self-explanatory if you know html. Html is a writing language, not a programming language. I do use Javascript, located in the js folder as scripts.js ([https://goo.gl/p3REAK](https://goo.gl/p3REAK)), and in the appendix under the same name. The scripts.js function is called in line 19 of the index.html file. Javascript is a programming language, and it was used for a few features on the website.

#### Contact us

The first was, on the bottom of the web-page, for taking the contact info of people who want to get in touch, and sending it to a Google Sheets document ([https://goo.gl/QCG6FF](https://goo.gl/QCG6FF)). When people enter their information at the bottom of the webpage and click submit, the information would be sent to the Google Sheet. The javascript program for this is on lines 138-149 of index.html, and essentially the data is entered to a script published online through Google’s form api ([https://goo.gl/AY86yV](https://goo.gl/AY86yV)). The script is saved as the scriptURL variable on line 140, and if there is a response from Google sheet then it worked (line 146).

#### Styling

The styling is located in the custom.css document in the appendix and the github repository, under the css folder: [https://goo.gl/skLZcH](https://goo.gl/skLZcH). Again, this styling is just in css and is not a programming language, so I will not go over how it functions. But in scripts.js, in lines 212-222, there is a function that modifies the css in javascript. This function constantly loops and checks if the user scrolled down past 2000 pixels of the window, and if so, makes the navigation bar transparent. This small styling function makes the website more responsive and look better.

#### scripts.js

The rest of scripts.js is all dedicated to creating the graphs for the data. On line 1, window.onload, the function starts when the user first loads the html document. The graphs are all compiled on the client side, not the server side, in order to make the website static. Lines 4-20 initialize the function "getDataPointsFromCSV", which takes a url for the csv and the column that the data is in, and pushes datapoints for the y and x axis. On line 6, the function uses regex ([https://goo.gl/YD4wXB](https://goo.gl/YD4wXB)) to split the csv into each of the lines, saved as an array, and the for loop from lines 7-18 iterates through the csvlines. Line 11 ignores any “NaN” data, or data that is invalid. Finally, on line 19 the dataPoints are returned.

The rest of the functions in scripts.js are exactly the same, but modify different divs in the html document - different graphs. The graph api used is taucharts ([https://www.taucharts.com/](https://www.taucharts.com/)), which makes it very easy to add beautiful graphs to an html document. Following the documentation, the graphs are created and then rendered to each div (ex. Line 46 to the windspeed div). jQuery.get() is used to get the datapoints from the csv file, and each of the code blocks uses the getDataPointsFromCSV function to get the datapoints for that specific graph (line 25). Rawgit urls are used to ensure the csv file from github is in its raw form, so it can be accessed ([https://rawgit.com/](https://rawgit.com/)). The tooltip plugin is used to allow the user to pan the graph for specific point values (line 43).

#### Conclusion

With the scripts.js file explained, that is essentially how the website works. The website has a static index.html file, served from Github pages, Cloudflare, and Freenom, and uses the custom.css and scripts.js files to render the styling and graphs on the client-side. The result is an intuitive, interactive way of looking at the data coming from the weather station, in real-time.

#### Screen-shots

![image alt text](image_9.png)

![image alt text](image_10.png)

![image alt text](image_11.png)

![image alt text](image_12.png)

![image alt text](image_13.png)

![image alt text](image_14.png)

## Final Evaluation:

1. Discuss the overall performance / field results.

2. Provide a complete analysis of the data captured during fielding.

3. Detail the analysis and the analysis software tools (LabView VIs and Excel based) employed to complete that analysis

# Conclusions and Recommendations

* Describe the results in terms of accomplishments, successful or unsuccessful. Provide recommendations to improve your system. Provide recommendations with regard to  improving  the  project in terms of enhancing  students basic knowledge gained.Describe any lessons learned and their applicability to your future design activities.

# Attachments

## Organization Chart with Roles and Responsibilities

## Supporting CAD drawings
# a
# a
# a

## The Code

See [https://github.com/jschmidtnj/MobileWeatherStation](https://github.com/jschmidtnj/MobileWeatherStation) and [https://anemometer.ml/](https://anemometer.ml/) for the code with line numbers.

### Wemos

```c++

/*
  E122 - Wemos With MQTT and DHT11 - Version 0.1
  Updated: February 20th, 2018. at 4:07 PM.

  Integrated from components picked off the net by Prof.KP.
  Check  the configuration section for what you can tinker with.
  Modify code on your own risk.... But, ... do take risks....

********/
/*  Installation of drivers and other set up needed - Check CANVAS...

  To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/

#include "RunningMedian.h"
#include <ESP8266WiFi.h>
#include "PubSubClient.h"
#include "info.h"
#include "DHT.h"
// Your sketch must #include this library, and the Wire library.
// (Wire is a standard library included with Arduino.):

#include <SFE_BMP180.h>
#include <Wire.h>

// CONFIGURATION SETTINGS ....BEGIN

//Wifi Settings
//const char* ssid = "DLabsPrivate1";
//const char* password = "L3tsM@keSometh1n";
const char* ssid = "Stevens-Media";
const char* password = "Stevens1870";
// ANY WEMOS WITH A STICKER ON THE BACK IS REGISTERED TO THE NETWORK...
// THOSE WITHOUT THE STICKERS DO NOT WORK...


//MQTT Settings
const char* mqtt_server = "155.246.18.226";
const char* MQusername = "jojo";
const char* MQpassword = "hereboy";
// This magic word is added to the topic for control messages E122/<MAC4>/Control/MAGIC_WORD Param, Value
// Params Accepted PUBLISH_DELAY  VALUE in ms
//                 SLEEP_DELAY VALUE in ms
//
const char* MAGIC_WORD = "XYZZYPQQRT";
#define PUBLISH_DELAY  10000
#define SLEEP_DELAY 500
#define DEEP_SLEEP_SECONDS  10
//const char* mqtt_server = "broker.hivemq.com"; //This is a public server - no username/pwd
// Sleep delay is how long Wemos goes into sleep mode before re-checking --
// May help conserve power in the field -- you may have to check.
// Want to put it in Deepsleep while in field -else will burn through batteries. - power conserve mode...
// convert to microseconds
//ESP.deepSleep(sleepSeconds * 1000000);



//Set up the DHT22
#define DHTPIN 0//This is GPIO0 which is WeMos D3.
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);






//Set up anemometer
#define signalPin 14
//GPIO14 in  WeMos D1 R2 is D5
bool mode_1_speed = false;
bool mode_2_speed = not mode_1_speed;

double current_time_speed = 0;
double previous_time_speed = 0;
bool print_now_speed = false;

double diameter = .25; //in feet
unsigned int num_decimal = 2;
unsigned int speed_pin = 3;

#define num_loop 100
#define mult_constant .25894
unsigned int delay_in_between = 10; //ms







//Set-up BMP180 Temp Altimeter sensor




float measured_altitude = 0;
float measured_temp = 0;
float measured_pressure = 0;

// You will need to create an SFE_BMP180 object, here called "pressure":

SFE_BMP180 pressure;

#define ALTITUDE 7.925 // Altitude of Hoboken, NJ, in meters

void setup_alt_temp()
{

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    Serial.println("BMP180 init success");
  /*
    else
    {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
    }
  */
}








//MQTT  - 5000 ms is 5 sec.


//
//Note that since this is a real Wemos board -- it runs forever as opposed to
// the fakemos -- http://www.dmi.stevens.edu/fakemos/

// CONFIGURATION SETTINGS ....END

WiFiClient espClient;
info board_info;
PubSubClient client(espClient);
long lastMsg = 0;
char msg1[20], msg2[20];
char MQTopic1[50], MQTopic2[50];
char ControlTopic[50];
char BoardMac4[5];
float temp = 0;
float hum = 0;
float freq = 0;
int tm = 0;
int dt, ta, ha;


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Board Last 4.
  BoardMac4[0] = board_info.mac()[12];
  BoardMac4[1] = board_info.mac()[13];
  BoardMac4[2] = board_info.mac()[15];
  BoardMac4[3] = board_info.mac()[16];
  BoardMac4[4] = '\0';
  //
  // Need the null termination for the string stuff to work, declare 1 extra character...
  //
  Serial.println(" MAC  4 of the board");
  Serial.println(BoardMac4);
  sprintf(MQTopic1, "E122/%4s/Temperature", BoardMac4);
  sprintf(MQTopic2, "E122/%4s/Humidity", BoardMac4);
  sprintf(ControlTopic, "E122/%4s/control/%s", BoardMac4, MAGIC_WORD);
  Serial.println("Setting the topics");
  Serial.println(MQTopic1);
  Serial.println(MQTopic2);
  Serial.println("This Wemos Control channel is");
  Serial.println(ControlTopic);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQusername, MQpassword)) {
      //    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish(MQtopic1, "00000");
      // ... and resubscribe ---- Dont subscribe KP
      // Wemos subscribes to its control channel E122/<mac4>/control
      client.subscribe(ControlTopic);
      // #KP - No announcements --- No Subscribes.
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode (signalPin, INPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.println("********************************************************");
  Serial.println("* E 122 Design II: Field Sustainable Systems           *");
  Serial.println("*                                                      *");
  Serial.println("* Wemos Firmware with MQTT and DHT11 Support           *");
  Serial.println("*                                                      *");
  Serial.println("* Version 0.1  Feb 20 2018  (Stevens)                  *");
  Serial.println("********************************************************");
  Serial.print("Board Mac Address:");
  Serial.println(board_info.mac());
  setup_wifi();
  setup_alt_temp();
  dht.begin();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  dt = now - lastMsg ;

  if (dt > PUBLISH_DELAY) {
    lastMsg = now;
    temp = dht.readTemperature(true);
    hum = dht.readHumidity();
    loop_alt_temp();
    Serial.print("Published :" );
    Serial.print(MQTopic1);
    Serial.print(" with value: " );
    Serial.println(msg1);
    client.publish(MQTopic1, msg1);
    Serial.print("Published :" );
    Serial.print(MQTopic2);
    Serial.print(" with value: " );
    Serial.println(msg2);
    client.publish(MQTopic2, msg2);
    RunningMedian wind_speed_samples = RunningMedian(100);
    for (int i = 0; i < num_loop; i++) {
      wind_speed_samples = get_speed(wind_speed_samples);
      delay(delay_in_between);
    }
    //print the data:
    float avg_temp = (temp + measured_temp) / 2;
    //avg_temp = 50;
    //speed_data = "51";
    //temp = 52;
    //measured_temp = 53;
    //hum = 54;
    //measured_pressure = 55;
    //measured_altitude = 56;
    snprintf (msg1, 20, "%d", (int) temp);
    snprintf (msg2, 20, "%d", (int) hum);
    Serial.println("Data," + check_nan(String(wind_speed_samples.getMedian(), num_decimal)) + "," + check_nan(String(temp, num_decimal)) + "," + check_nan(String(measured_temp, num_decimal)) + "," + check_nan(String(avg_temp, num_decimal)) + "," + check_nan(String(hum, num_decimal)) + "," + check_nan(String(measured_altitude, num_decimal)) + "," + check_nan(String(measured_pressure, num_decimal)) + ",DataEnd,");
  }
  //ESP.deepSleep(DEEP_SLEEP_SECONDS * 1000000);
  //digitalWrite(BUILTIN_LED, LOW);
  delay(SLEEP_DELAY);
  //digitalWrite(BUILTIN_LED, HIGH);
}


String check_nan(String data){
  if(data == "nan"){
      data = "0";
      data += ".";
      for(int i=0; i<num_decimal; i++){
        data += "0";
      }
    }
  return data;
}










RunningMedian get_speed(RunningMedian wind_speed_samples) {
  // put your main code here, to run repeatedly:
  //RPM data input

  //speed data input
  mode_1_speed = digitalRead(signalPin);
  if (mode_1_speed == mode_2_speed) {
    mode_2_speed = not mode_1_speed;
    current_time_speed = micros();
    if (print_now_speed == true) {
      //mph = rpm * 60min/hr * pi * diameter_of_wheel (feet) / 5280 ft/mile
      wind_speed_samples.add(long(mult_constant * 1000000 * 60 / (current_time_speed - previous_time_speed + delay_in_between)) * (60 * PI * diameter / 5280)); //get the speed
      print_now_speed = not print_now_speed;
    }
    else {
      print_now_speed = not print_now_speed;
    }
    previous_time_speed = current_time_speed;
  }
  return wind_speed_samples;
}
















//BMP 180 Temperature pressure sensor:



/* SFE_BMP180 library example sketch
  This sketch shows how to use the SFE_BMP180 library to read the
  Bosch BMP180 barometric pressure sensor.
  https://www.sparkfun.com/products/11824
  Like most pressure sensors, the BMP180 measures absolute pressure.
  This is the actual ambient pressure seen by the device, which will
  vary with both altitude and weather.
  Before taking a pressure reading you must take a temparture reading.
  This is done with startTemperature() and getTemperature().
  The result is in degrees C.
  Once you have a temperature reading, you can take a pressure reading.
  This is done with startPressure() and getPressure().
  The result is in millibar (mb) aka hectopascals (hPa).
  If you'll be monitoring weather patterns, you will probably want to
  remove the effects of altitude. This will produce readings that can
  be compared to the published pressure readings from other locations.
  To do this, use the sealevel() function. You will need to provide
  the known altitude at which the pressure was measured.
  If you want to measure altitude, you will need to know the pressure
  at a baseline altitude. This can be average sealevel pressure, or
  a previous pressure reading at your altitude, in which case
  subsequent altitude readings will be + or - the initial baseline.
  This is done with the altitude() function.
  Hardware connections:
  - (GND) to GND
  + (VDD) to 3.3V
  (WARNING: do not connect + to 5V or the sensor will be damaged!)
  You will also need to connect the I2C pins (SCL and SDA) to your
  Arduino. The pins are different on different Arduinos:
  Any Arduino pins labeled:  SDA  SCL
  Uno, Redboard, Pro:        A4   A5
  Mega2560, Due:             20   21
  Leonardo:                   2    3
  Leave the IO (VDDIO) pin unconnected. This pin is for connecting
  the BMP180 to systems with lower logic levels such as 1.8V
  Have fun! -Your friends at SparkFun.
  The SFE_BMP180 library uses floating-point equations developed by the
  Weather Station Data Logger project: http://wmrx00.sourceforge.net/
  Our example code uses the "beerware" license. You can do anything
  you like with this code. No really, anything. If you find it useful,
  buy me a beer someday.
  V10 Mike Grusin, SparkFun Electronics 10/24/2013
  V1.1.2 Updates for Arduino 1.6.4 5/2015
*/

void loop_alt_temp()
{
  char status;
  double T, P, p0, a;

  // Loop here getting pressure readings every 10 seconds.

  // If you want sea-level-compensated pressure, as used in weather reports,
  // you will need to know the altitude at which your measurements are taken.
  // We're using a constant called ALTITUDE in this sketch:

  /*
    Serial.println();
    Serial.print("provided altitude: ");
    Serial.print(ALTITUDE,0);
    Serial.print(" meters, ");
    Serial.print(ALTITUDE*3.28084,0);
    Serial.println(" feet");
  */

  // If you want to measure altitude, and not pressure, you will instead need
  // to provide a known baseline pressure. This is shown at the end of the sketch.

  // You must first get a temperature measurement to perform a pressure reading.

  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      measured_temp = (9.0 / 5.0) * T + 32.0; //deg F
      /*
        // Print out the measurement:
        Serial.print("temperature: ");
        Serial.print(T,2);
        Serial.print(" deg C, ");
        Serial.print((9.0/5.0)*T+32.0,2);
        Serial.println(" deg F");
      */

      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          /*
            // Print out the measurement:
            Serial.print("absolute pressure: ");
            Serial.print(P,2);
            Serial.print(" mb, ");
            Serial.print(P*0.0295333727,2);
            Serial.println(" inHg");
          */
          // The pressure sensor returns abolute pressure, which varies with altitude.
          // To remove the effects of altitude, use the sealevel function and your current altitude.
          // This number is commonly used in weather reports.
          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
          // Result: p0 = sea-level compensated pressure in mb

          p0 = pressure.sealevel(P, ALTITUDE); // we're at 1655 meters (Boulder, CO)
          /*
            Serial.print("relative (sea-level) pressure: ");
            Serial.print(p0,2);
            Serial.print(" mb, ");
            Serial.print(p0*0.0295333727,2);
            Serial.println(" inHg");
          */
          measured_pressure = p0 * 0.0295333727; //in Hg

          // On the other hand, if you want to determine your altitude from the pressure reading,
          // use the altitude function along with a baseline pressure (sea-level or other).
          // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
          // Result: a = altitude in m.
          a = pressure.altitude(P, p0);
          /*
            Serial.print("computed altitude: ");
            Serial.print(a,0);
            Serial.print(" meters, ");
            Serial.print(a*3.28084,0);
            Serial.println(" feet");
          */
          measured_altitude = a * 3.28084; //in feet from sea level
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  delay(5000);  // Pause for 5 seconds.
}

```

### Raspberry Pi App Code (python)

```python

##
 #  @filename   :   app.py
 #  @brief      :   2.9inch e-paper display and weather data
 #  @author     :  Joshua Schmidt
 #
 #  Copyright (C) Joshua Schmidt, Waveshare e-ink library    April 2018
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
screen_delay = .05 #minutes
global data_delay
data_delay = 15 #minutes


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
    #print(data)
    data_parsed = [x for x in data.split(',')] #split by comma
    if len(data_parsed) > 7:
        if data_parsed[1] != "nan" and data_parsed[1] != "0.00":
            speed = data_parsed[1]
        if data_parsed[2] != "nan" and data_parsed[2] != "0.00":
            temp_1 = data_parsed[2]
        if data_parsed[3] != "nan" and data_parsed[3] != "0.00":
            temp_2 = data_parsed[3]
        if data_parsed[4] != "nan" and data_parsed[4] != "0.00":
            avg_temp = data_parsed[4]
        if data_parsed[5] != "nan" and data_parsed[5] != "0.00":
            humidity = data_parsed[5]
        if data_parsed[6] != "nan" and data_parsed[6] != "0.00":
            alt = data_parsed[6]
        if data_parsed[7] != "nan" and data_parsed[7] != "0.00":
            pressure = data_parsed[7]
    
        #add data to database:
        datapoint = Data.create(the_time_and_date = str(datetime.now()), windSpeed = speed, humidity = humidity, temp_1 = temp_1, temp_2 = temp_2, avg_temp = avg_temp, altitude = alt, pressure = pressure)
        
        current_time = time.time()
        #print((current_time - last_time_screen) / 100)
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

```

### Raspberry Pi Startup Script:

```shell

cd /home/pi/Desktop/MobileWeatherStation
git pull origin master
ip4=$(/sbin/ip -o -4 addr list wlan0 | awk '{print $4}' | cut -d/ -f1)
echo $ip4 >> ip-address.txt
git add -A
git commit -m "added ip-addresses"
git push origin master
python3 testdisplay.py
python3 app.py

```

### Raspberry Pi End script send data:

```shell

#!/bin/sh

#use git config remote.origin.url https://jschmidtnj:PASSWORD@github.com/jschmidtnj/StevensBajaSAE.git if there are login errors
sudo mysql -u "root" < sql-to-csv.sql
sudo chmod -R 777 /tmp
sudo chmod -R 777 /mnt
cd /tmp
file_name=data.csv
current_time=$(date +"%Y-%m-%d-%H-%M-%S")
new_filename=$current_time-$file_name
mv $file_name /home/pi/Desktop/MobileWeatherStation/data/$new_filename
cat /home/pi/Desktop/MobileWeatherStation/data/$new_filename > /home/pi/Desktop/MobileWeatherStation/data/current_data_file.csv
cd /home/pi/Desktop/MobileWeatherStation
git add -A
git commit -m "added data files"
git push origin master

```

### Send data to csv file from mysql

```mysql

use WeatherStationData;
select the_time_and_date, windSpeed,humidity,temp_1,temp_2,avg_temp,altitude,pressure from data
into outfile '/tmp/data.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';
exit

```

### Website index.html: 

```html

<!DOCTYPE html>
<html>
<head>
  <title>Weather Station</title>
  <meta charset="utf-8">
  <meta name="description" content="A Mobile, Remote Weather Station">
  <meta name="author" content="Joshua Schmidt">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="https://rawgit.com/jschmidtnj/MobileWeatherStation/master/docs/assets/favicon.ico">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
  <!-- Custom styles for this template -->
  <link href="https://rawgit.com/jschmidtnj/MobileWeatherStation/master/docs/css/custom.css" rel="stylesheet" type="text/css">
  <!-- Import JQuery Right now to avoid errors -->
  <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
  <script src="https://cdn.jsdelivr.net/d3js/3.5.17/d3.min.js" charset="utf-8"></script>
  <script src="https://cdn.jsdelivr.net/npm/taucharts@1/build/production/tauCharts.min.js" type="text/javascript"></script>
  <link rel="stylesheet" type="text/css" href="https://cdn.jsdelivr.net/npm/taucharts@1/build/production/tauCharts.min.css">
  <!-- adding custom scripts -->
  <script src="https://rawgit.com/jschmidtnj/MobileWeatherStation/master/docs/js/scripts.js"> </script>



</head>
<body>
  <nav class="navbar navbar-expand-md navbar-light fixed-top">
    <a class="navbar-brand" href="#">Weather Station</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>

    <div class="collapse navbar-collapse" id="navbarsExampleDefault">
      <ul class="navbar-nav mr-auto">
        <li class="nav-item">
          <a class="nav-link" href="#about">About</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#data">Data</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#team">Team</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#connect">Connect</a>
        </li>
      </ul>
    </div>
  </nav>

  <main role="main">
    <!-- Main jumbotron for a primary marketing message or call to action -->
    <div class="hero-header jumbotron paral hero-image" id="hero">
      <div class="container">
        <h1 class="display-3" align="center">Mobile Weather Station</h1>
        <br/>
        <br/>
        <br/>
        <br/>
        <p><a class="btn btn-primary btn-lg" href="#about" role="button">About &raquo;</a></p>
      </div>
    </div>

    <div class="about-section jumbotron paral about-image container-fluid text-center" id="about">
      <div class="container">
        <h1 class="display-3" align="center">About</h1>
        <p class="lead" align="center">This is a remote weather station with real-time data logging. View the code here:  <a href="https://github.com/jschmidtnj/MobileWeatherStation">Github</a> </p>
      </div>
    </div>

    <div class="Data-section jumbotron justify-content-center Data-image" id="data">
      <div class="container">
        <h1 class="display-3" align="center">Data</h1>
        <p class="lead" align="center">
          <br/><br/><hr/><br/><br/>
          <h2 align="center">Wind Speed</h2>
          <div id="windspeed" class="graph_styling"></div>
          <br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
          <h2 align="center">Humidity</h2>
          <div id="humidity" class="graph_styling"></div>
          <br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
          <h2 align="center">Average Temperature</h2>
          <div id="avg_temp" class="graph_styling"></div>
          <br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
          <h2 align="center">Temp 1</h2>
          <div id="temp_1" class="graph_styling"></div>
          <br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
          <h2 align="center">Temp 2</h2>
          <div id="temp_2" class="graph_styling"></div>
          <br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
          <h2 align="center">Altitude</h2>
          <div id="altitude" class="graph_styling"></div>
          <br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
          <h2 align="center">Pressure</h2>
          <div id="pressure" class="graph_styling"></div>
          <br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
        </div>
      </div>
    
    <div class="people-section jumbotron paral people-image" id="team">
      <div class="container">
        <h1 class="display-3" align="center">People</h1>
        <p class="lead" align="center">Meet the team - Joshua, Lorie, and Ang.</p>
      </div>
    </div>

      <div class="connect-section jumbotron justify-content-center" id="connect">
        <div class="container">
          <h1 class="display-3" align="center">Connect</h1>
          <br/>
          <br/>
          <br/>
          <form class="form-inline my-2 my-lg-0 justify-content-center" id="submit-to-google-sheet">
            <input class="form-control mr-sm-2" name="email" type="email" placeholder="Email" aria-label="Email">
            <input class="form-control mr-sm-2" name="firstName" type="text" placeholder="First Name" aria-label="First Name">
            <input class="form-control mr-sm-2" name="lastName" type="text" placeholder="Last Name" aria-label="Last Name">
            <button class="btn btn-outline-success my-2 my-sm-0" id="submit" type="submit">Enter</button>
          </form>
          <br/>
          <br/>
          <br/>
          <br/>
          <br/>
          <br/>
        </div>
      </div>

      <hr>
    </main>

    <footer class="container">
      <p>&copy; Locnet 2018</p>
    </footer>

  <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
    <script>
      //see https://github.com/jamiewilson/form-to-google-sheets
const scriptURL = 'https://script.google.com/macros/s/AKfycbz77HuNxSiVaaODk46yAl8XZRTLS_kMGUUY5-zAEqJg9eplBrQ/exec'
  const form = document.forms["submit-to-google-sheet"]

  form.addEventListener('submit', e => {
    e.preventDefault()
    fetch(scriptURL, { method: 'POST', body: new FormData(form)})
      .then(response => console.log('Success!', response))
      .catch(error => console.error('Error!', error.message))
  })
    </script>
  </body>
  </html>

```

### Website Custom Javascript for loading graphs:

```javascript

window.onload = function() {
        var dataPoints = [];
	 
        function getDataPointsFromCSV(csv, column) {
            var dataPoints = csvLines = points = [];
            csvLines = csv.split(/[\r?\n|\r|\n]+/);
            for (var i = 0; i < csvLines.length; i++)
                if (csvLines[i].length > 0) {
                    points = csvLines[i].split(",");
                    var y_axis_data = (points[column]);
                    if (y_axis_data == "NaN"){
                    	y_axis_data = "0"
                    }
                    dataPoints.push({
                        y_axis: parseFloat((y_axis_data).slice(1, (points[1]).length - 1)),
                        x_axis: parseFloat(i)
                    });
                }
            return dataPoints;
        }
	
	jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
		var column = 1;
		var windspeed_chart = new tauCharts.Chart({
			data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'WindSpeed (mph)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
		        tauCharts.api.plugins.get('tooltip')()
		    ]
        });
        windspeed_chart.renderTo('#windspeed');
	});

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 2;
    var humidity_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'humidity',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        humidity_chart.renderTo('#humidity');
  });

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 3;
    var temp_1_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'temp_1 (F)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        temp_1_chart.renderTo('#temp_1');
  });

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 4;
    var temp_2_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'Temp 2 (F)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        temp_2_chart.renderTo('#temp_2');
  });

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 5;
    var avg_temp_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'avg_temp (F)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        avg_temp_chart.renderTo('#avg_temp');
  });

  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 6;
    var altitude_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'altitude (m)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        altitude_chart.renderTo('#altitude');
  });
  jQuery.get("https://rawgit.com/jschmidtnj/MobileWeatherStation/master/data/current_data_file.csv?xstart=5&ystart=10&length=10&type=csv", function(data) {
    var column = 7;
    var pressure_chart = new tauCharts.Chart({
      data: getDataPointsFromCSV(data, column),           
            y: 'y_axis',
            x: 'x_axis',
            type: 'line',
            guide:{
              padding:{l:70, t:10, b:70,r:10},
              showGridLines:'xy',
              y:{
                label:{
                  text:'pressure (Pa)',
                  padding:-15
                }
              },
              x:{
                label:'Count',
              }
            },
            plugins: [
            tauCharts.api.plugins.get('tooltip')()
        ]
        });
        pressure_chart.renderTo('#pressure');
    });
  }

$(document).ready(function(){
	$(window).on("scroll",function(){
  	var wn = $(window).scrollTop();
    if(wn > 2000){
    	$(".navbar").css("background","rgba(255,255,255,.5)");
    }
    else{
    	$(".navbar").css("background","rgba(255,255,255,1)");
    }
  });
})

;```

### Custom CSS

```css
.graph_styling {
  width: 100%;
  height: 500px;
  margin: 0;
  padding: 0;
  float: left;
}	
/*add parallax scrolling*/
.paral{
	min-height: 800px;
	background-attachment: fixed;
	background-size: cover;
	background-position: 50% 50%;
}

.paral p{
	font-size: 24px;
	color:#f5f5f5;
	text-align: center;
	line-height: 60px;
}

.paral h1 {
	color: rgba(255, 255, 255, 0.8);
	font-size: 60px;
	text-align: center;
	padding-top: 60px;
	line-height: 100px;
}

.hero-header {
	
}

.hero-image {
	background-image: linear-gradient( rgba(0, 0, 0, .75), rgba(0, 0, 0, 0.5) ), url("https://raw.githubusercontent.com/jschmidtnj/mobileweatherstation/master/docs/assets/hero-background.jpg");
}

.about-section{
	
}

.about-image{
	background-image: linear-gradient( rgba(0, 0, 0, .75), rgba(0, 0, 0, 0.5) ), url("https://raw.githubusercontent.com/jschmidtnj/mobileweatherstation/master/docs/assets/about-background.jpg");
}

.people-section{

}

.people-image{
	background-image: linear-gradient( rgba(0, 0, 0, .75), rgba(0, 0, 0, 0.5) ), url("https://raw.githubusercontent.com/jschmidtnj/mobileweatherstation/master/docs/assets/people-background.jpg");
}
.data-section{
	
}

.data-image{
	background-color: white;
}

.connect-section{
	margin-bottom: 0;
}	
/*remove bottom margin from Jumbotron*/
.jumbotron{
	margin-bottom: 0;
	border-radius: 0px;
}

.navbar{
	background:rgba(255,255,255,1);
}
/* Move down content because we have a fixed navbar that is 50px tall */
body {
	padding-top: 2rem;
}
	
footer{

}
```
