/*
 * Arduino Mega
 * Motor Relay Control
 * 
 * Date : 20150903
 * Artist by SiRyuA.
 */

#define UP 1
#define DOWN 0
#define STOP 2

// Relay Port
int Motor_pinRelay[6]={22, 28, 36, 27, 12, 37};
int timedelay = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Motor_pinSetup();

  timedelay=2500;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    char Serial_Read = (char)Serial.read();
  
    if(Serial_Read == 'u') {
      Serial.println("Motor 0/1/2 UP");
        
      for(char i=0; i<3; i++) {
        Motor_Control(i, UP);
      }
      delay(timedelay);

      Motor_Stop();
    }
      
    else if(Serial_Read == 'd') {
      Serial.println("Motor 0/1/2 DOWN");
      
      for(char i=0; i<3; i++) {
        Motor_Control(i, DOWN);
      }
      delay(timedelay);
      Motor_Stop();
    }

    else if(Serial_Read == 'l') {
      Serial.println("Motor 0 DOWN + Motor 1/2 UP");

      Motor_Control(0, DOWN);
      Motor_Control(1, UP);
      Motor_Control(2, UP);

      delay(timedelay);

      Motor_Stop();
    }

    else if(Serial_Read == 'r') {
      Serial.println("Motor 0/1 UP + Motor 2 DOWN");

      Motor_Control(0, UP);
      Motor_Control(1, UP);
      Motor_Control(2, DOWN);

      delay(timedelay);

      Motor_Stop();
    }

    else if(Serial_Read == 'f') {
      Serial.println("Motor 0/2 UP + Motor 1 DOWN");

      Motor_Control(0, UP);
      Motor_Control(1, DOWN);
      Motor_Control(2, UP);

      delay(timedelay);

      Motor_Stop();
    }

    else if(Serial_Read == 'b') {
      Serial.println("Motor 0/2 DOWN + Motor 2 UP");

      Motor_Control(0, DOWN);
      Motor_Control(1, UP);
      Motor_Control(2, DOWN);

      delay(timedelay);

      Motor_Stop();
    }


     
    else {
      Motor_Stop();
    }
  }
}

// Pin Include
void Motor_pinSetup(void) {
  for(char i=0; i<=8; i++) {
    pinMode(Motor_pinRelay[i], OUTPUT);
  }
}

// Motor Control
void Motor_Control(int motor, char mode) {
  if(mode == UP) {
    digitalWrite(Motor_pinRelay[motor], HIGH);
    digitalWrite(Motor_pinRelay[(motor+3)], LOW);
  }
  else if(mode == DOWN) {
    digitalWrite(Motor_pinRelay[motor], LOW);
    digitalWrite(Motor_pinRelay[(motor+3)], HIGH);
  }
  else {
    digitalWrite(Motor_pinRelay[motor], LOW);
    digitalWrite(Motor_pinRelay[(motor+3)], LOW);
  }
}

void Motor_Stop(void) {
  for(char i=0; i<3; i++) {
    Motor_Control(i, STOP);
  }
  delay(1000);
}

