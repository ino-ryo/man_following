
#include <Servo.h>

#define MOTOR_B 9
#define DIR_B 8
#define MOTOR_R 10
#define DIR_R 11
#define MOTOR_L 3
#define DIR_L 2

int pwm=180;
float val = 1/sqrt(3);
float sld = pwm * val;


const int width = 640


double last_position = 0;
double diff[5];

void setup(){
  pinMode(lin1pin,OUTPUT);
  pinMode(lin2pin,OUTPUT);
  pinMode(rin1pin,OUTPUT);
  pinMode(rin2pin,OUTPUT);
  Serial.begin(9600);
}

void rotateRight(){
digitalWrite(DIR_L,HIGH);
digitalWrite(DIR_R,HIGH);
digitalWrite(DIR_B,HIGH);
analogWrite(MOTOR_L, pwm);
analogWrite(MOTOR_R, pwm);
analogWrite(MOTOR_B, pwm);
}

void rotateLeft(){
digitalWrite(DIR_L,LOW);
digitalWrite(DIR_R,LOW);
digitalWrite(DIR_B,LOW);
analogWrite(MOTOR_L, pwm);
analogWrite(MOTOR_R, pwm);
analogWrite(MOTOR_B, pwm);
}



double linePosition(){
  int w = 0;
  double s_position = 0;
  for(int i=0;i<5;i++){
    if(analogRead(i)>500){
      s_poition += i;
      w = w+1;
    }
  }
  if(w!=0){
    s_position = s_position / w -2;
    last_position = s_position;
  }else{
    if(last_position == -2){
      s_position = -3;
    }else if(last_position == 2){
      s_position = 3;
    }
  }
  return s_position;
}

double pd(double sensor,double target){
  double kp = 30;
  double kv = 0;
  double ki = 0;
  diff[4] = diff[3];
  diff[3] = diff[2];
  diff[2] = diff[1];
  diff[1] = diff[0];
  diff[0] = sensor;
  p = (target - diff[0]) * kp;
  d = (diff[4] - diff[0]) * kv;
  i = 0;
  return p+i+d;
}

void loop(){
  double mv;
  double spd = 130;
  mv = pd(linePosition(),0);
  if(mv>0){
    driveMotor(spd-mv,spd);
  }else{
    driveMotor(spd,spd+mv);
  }
  delayMicroseconds(1);
}
