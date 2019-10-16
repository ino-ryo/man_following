const int lin1pin = 6;
const int lin2pin = 5;
const int rin1pin = 3;
const int rin2pin = 11;
double last_position = 0;
double diff[5];

void setup(){
  pinMode(lin1pin,OUTPUT);
  pinMode(lin2pin,OUTPUT);
  pinMode(rin1pin,OUTPUT);
  pinMode(rin2pin,OUTPUT);
  Serial.begin(9600);
}

void driveMotor(int lval,int rval){
  lval = constrain(lval,-255,255);
  rval = constrain(rval,-255,255);
  if(lval>0){
    analogWrite(lin1pin,lval);
    digitalWrite(lin2pin,LOW);
  }else{
    lval = abs(lval);
    analogWrite(lin2pin,lval);
    digitalWrite(lin1pin,LOW);
  }
  if(rval>0){
    analogWrite(rin1pin,rval);
    digitalWrite(rin2pin,LOW);
  }else{
    rval = abs(rval);
    analogWrite(rin2pin,rval);
    digitalWrite(rin1pin,LOW);
  }
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
