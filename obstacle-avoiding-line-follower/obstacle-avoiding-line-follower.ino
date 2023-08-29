//initializing motor pins
#define enA 10 
#define in1 9 
#define in2 8
#define in3 7 
#define in4 6  
#define enB 5 

//IR sensor
#define L_S A0
#define R_S A1

#define echo A2
#define trigger A3

#define servo A5

int Set=15;
int distance_L, distance_F, distance_R; 

void setup(){

//declaring input output pins
pinMode(R_S, INPUT);  
pinMode(L_S, INPUT);

pinMode(echo, INPUT );
pinMode(trigger, OUTPUT); 

pinMode(enA, OUTPUT);  
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT); 
pinMode(in3, OUTPUT);   
pinMode(in4, OUTPUT); 
pinMode(enB, OUTPUT);  

//speed control(0-255)
analogWrite(enA, 190);
analogWrite(enB, 190);


//servo motor condition
pinMode(servo, OUTPUT);

 for (int angle = 70; angle <= 140; angle += 5)
   {
   servoPulse(servo, angle); 
    }
 for (int angle = 140; angle >= 0; angle -= 5)  
 {
   servoPulse(servo, angle);
     }

 for (int angle = 0; angle <= 70; angle += 5) 
  {
   servoPulse(servo, angle); 
    }

distance_F = Ultrasonic_read();

delay(500);//.5sec delay
}


void loop(){  

distance_F = Ultrasonic_read();

//both sensor in white color
 if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0))
 {
  if(distance_F > Set)
  { 
    forword();
  }
   else{
     Check_side();
     }  
 }  
 
//if Right sensor in black & Left in white
else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0))
{
  turnRight();
  }  

//if right sensor in  white & Left in Black
else if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1))
{
  turnLeft();
  } 

 else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1))
 {
   turnLeft();
   }    
delay(10);
}

void servoPulse (int pin, int angle){

int pwm = (angle*11) + 500; 
 digitalWrite(pin, HIGH);
 delayMicroseconds(pwm);
 digitalWrite(pin, LOW);
 delay(50);
}


long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (echo, HIGH);
  return time / 29 / 2;
}

void compareDistance(){
    if(distance_L > distance_R){
  turnLeft();
  delay(500);
  forword();
  delay(600);
  turnRight();
  delay(500);
  forword();
  delay(600);
  turnRight();
  delay(400);
  }
  else{
  turnRight();
  delay(500);
  forword();
  delay(600);
  turnLeft();
  delay(500);
  forword();
  delay(600);  
  turnLeft();
  delay(400);
  }
}

void Check_side(){
    Stop();
    delay(100);
 for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle); 
    }
    delay(300);
    distance_R = Ultrasonic_read();

    delay(100);
  for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle); 
    }
    delay(500);
    distance_L = Ultrasonic_read();

    delay(100);
 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle); 
    }
    delay(300);
    compareDistance();
}

void forword(){ 

digitalWrite(in1, LOW);
digitalWrite(in2, HIGH); 
digitalWrite(in3, HIGH); 
digitalWrite(in4, LOW); 
}

void backword(){ 

digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW); 
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void turnRight(){ 

digitalWrite(in1, LOW); 
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void turnLeft(){

digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW); 
digitalWrite(in3, HIGH); 
digitalWrite(in4, LOW); 
}

void Stop(){

digitalWrite(in1, LOW); 
digitalWrite(in2, LOW); 
digitalWrite(in3, LOW);
digitalWrite(in4, LOW); 
}