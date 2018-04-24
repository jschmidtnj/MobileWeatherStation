#include "RunningMedian.h"


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
unsigned int delay_in_between = 10; //ms

void setup() {
  // put your setup code here, to run once:
  pinMode (signalPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  RunningMedian wind_speed_samples = RunningMedian(100);
  for(int i=0; i<num_loop; i++){
    wind_speed_samples = get_speed(wind_speed_samples);
    delay(delay_in_between);
  }
  delay(1000);
  Serial.println(wind_speed_samples.getMedian());
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
      wind_speed_samples.add(long(1000000 * 60 / (current_time_speed - previous_time_speed + delay_in_between)) * (60 * PI * diameter / 5280)); //get the speed
      print_now_speed = not print_now_speed;
    }
    else {
      print_now_speed = not print_now_speed;
    }
    previous_time_speed = current_time_speed;
  }
  return wind_speed_samples;
}
