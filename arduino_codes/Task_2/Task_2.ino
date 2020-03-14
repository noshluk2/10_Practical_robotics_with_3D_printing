// Going 2 sec fast and then 2 sec going medium speed

// Defing the pins 
#define motorRa 25
#define motorRb 26
#define motorLa 33
#define motorLb 32
#define Rpwm 27
#define Lpwm 14

const int channel_R = 0;
const int channel_L = 1;
const int freq = 5000;
const int res =8;

void setup(){ 
  setup_motors();
  Serial.begin(115200);
}

void loop(){
  delay(2000);
  Serial.println("Fast");
  start();
  ledcWrite(channel_R , 175);
  ledcWrite(channel_L , 175);
  delay(2000);
  Serial.println("Stopping Fast");
  stopp();
  delay(1000);
  start();
  Serial.println("SLOW");
  ledcWrite(channel_R , 120);
  ledcWrite(channel_L , 120);
  delay(2000);
  Serial.println("Stopping SLOW");
  stopp();
  }



void stopp(){
  digitalWrite(motorLa,LOW);
  digitalWrite(motorRa,LOW);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
}

void start(){
  digitalWrite(motorLa,HIGH);
  digitalWrite(motorRa,HIGH);
  digitalWrite(motorLb,LOW);
  digitalWrite(motorRb,LOW);
}

void setup_motors(){

  pinMode(motorLa, OUTPUT);
  pinMode(motorLb, OUTPUT);
  pinMode(motorRa, OUTPUT);
  pinMode(motorRb, OUTPUT);
  ledcSetup(channel_R ,freq , res);
  ledcSetup(channel_L ,freq , res);
  ledcAttachPin(Rpwm,channel_R);
  ledcAttachPin(Lpwm,channel_L);
}
