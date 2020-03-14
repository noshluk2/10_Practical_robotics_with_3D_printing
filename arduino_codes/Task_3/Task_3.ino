// go straight 100 cm then stop 
// turn 180 degree and stop
// go straight 150 cm

// Defineing the Pins for the robot -> You can change here easily if your connections are different.

#define enc_RA 5
#define enc_RB 18
#define enc_LA 17
#define enc_LB 16
#define motorRa 27
#define motorRb 14
#define motorLa 25
#define motorLb 26
#define Rpwm 12
#define Lpwm 33

// Global Variables -> to be used by different functions .
// unsigned int because we only need positive values
// short because of only 2 decimal point of accuracy is required.

//Variables
  int count_R = 0;                                  //For Encoders
  int count_L = 0;
  short one_rev_dist = 20.9 ;                       // its in cm
  unsigned int one_rev_ticks = 750 ;                // its an average the encoders are not very accurate so error will be produced.
  short ticks_req = 0;                              //  Defineing only for " ONE MOTOR "
  unsigned int ticks_for_360 = 2964 ;
  const int channel_R = 0;
  const int channel_L = 1;                          // For Pwm setup
  bool car_moving;                                  

void setup() {
  Serial.begin(115200);                             // starting Serial monitor at buad rate 115200 -> you can change it as-well
  setup_motors();
  delay(4000);                                      // given time to setup the Robot
  Perform_task_3();
}

void loop() {}

void Perform_task_3(){
  distance_to_travel(100);
  Serial.println("Went 100cm forward");
  delay(3000);
  degrees_to_turn(180);
  Serial.println("Did 180 Degree Turn");
  delay(2000);
  distance_to_travel(150);
  Serial.println("Went 150cm forward");

}


void distance_to_travel(int centimeters){
  reset_variables();                                // reseting variables so it may not count previous ticks into new task.'
  short rev_req = centimeters / one_rev_dist;       // this will produced revolution required for required distance to travel
  ticks_req = rev_req * one_rev_ticks ;             // this will produced ticks motor should do to complete required distance
  Serial.println(ticks_req); 
  start();                                          //Enable motors
  while(car_moving){
    Serial.println(count_R);
    if(count_R>=ticks_req){
      stopp();            }
                   }
  }

void degrees_to_turn(int degree){
  reset_variables();                                      // reseting variables so it may not count previous ticks into new task.'
  ticks_req = (degree * ticks_for_360)/360 ;
    start();
    digitalWrite(motorLa,LOW);
  while(car_moving){
    Serial.println(count_R);
    if(count_R>=ticks_req){
      stopp();            }
                   }
  }

void reset_variables(){
  ticks_req = 0 ;                                         // restting here because new counting should be started
  count_R =0;
}

// all motor setup is done in one function call
void setup_motors(){
  // pwm setup variables
  const int freq = 5000;
  const int res = 8;

  // direction for motor pinout defination
  pinMode(motorLa, OUTPUT);
  pinMode(motorLb, OUTPUT);
  pinMode(motorRa, OUTPUT);
  pinMode(motorRb, OUTPUT);
  // encoder pinout defination
  pinMode(enc_RA,INPUT);
  pinMode(enc_RB,INPUT);
  pinMode(enc_LA,INPUT);
  pinMode(enc_LB,INPUT);
  // Interrupt connection to gpio pins and defining interrupt case
  attachInterrupt(digitalPinToInterrupt(enc_RA),Update_encR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc_LA),Update_encL,CHANGE);
  // Pwm functionality setup
  ledcSetup(channel_R ,freq , res);
  ledcSetup(channel_L ,freq , res);
  ledcAttachPin(Rpwm,channel_R);
  ledcAttachPin(Lpwm,channel_L);
}
// Encoders-Interrupt callback functions
void Update_encR(){
   if (digitalRead(enc_RA) == digitalRead(enc_RB)) count_R--;
    else count_R++;  
}

void Update_encL(){
 if (digitalRead(enc_LA) == digitalRead(enc_LB)) count_L--;
  else count_L++; 
}

// function to disable the motors of robot
void stopp(){
  ledcWrite(channel_R , 0);                             // giving each motor 0 dutycycle value
  ledcWrite(channel_L , 0);    
  car_moving=false;
}

// function to enable the motors of robot
void start(){
  digitalWrite(motorLa,HIGH);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
  ledcWrite(channel_R , 150);                             // giving each motor 150 dutycycle resolution
  ledcWrite(channel_L , 160);
  car_moving=true;
}
