 #include <Servo.h>

Servo servo1;
Servo servo2;

const int IR1 = A1;
const int IR2 = A2;
const int IR3 = A3;
const int IR4 = A4;
const int IR5 = A5;

int waiter = 0;

 int sensor4 = 0;
 int plastic = 0;
 int sensor5 = 0;
 int led = 11;
void setup() {
  servo1.attach(8);  // Attach the servo motor to pin 9
  servo2.attach(9);  // Set the initial angle to 90 degrees
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  servo1.write(90);
  servo2.write(90);
  pinMode(led, OUTPUT);
}

void loop() {
  waiter = 0;
  // Read data from sensors
  //motor.step(100);  // Rotate 100 steps (adjust as needed)
  int sensor1 = analogRead(IR1);//value is below 500 if detected something
  if(sensor1<500){
    digitalWrite(led, HIGH);
  }
  Serial.println("Start");
  int sensor2 = analogRead(IR2);//value is below 500 if detected something
  int metal = digitalRead(7);  //value is below 1 if detected something
  int sensor3 = analogRead(IR3);//value is below 500 if detected something

  sensor4 = analogRead(IR4) - 200;//value is below 500 if detected something
  plastic = digitalRead(6);//value is below 1 if detected something
  sensor5 = analogRead(IR5);//value is below 500 if detected something
  
  while(sensor2 < 500 && waiter < 4000){
    waiter++;
    metal = digitalRead(7);
    Serial.print("waiting for metal, metal VALUE: ");
    Serial.print(metal);
    Serial.print(" WAITER: ");
    Serial.println(waiter);
    if( metal == 1 && waiter < 150){
      Serial.println("Metal is detected");
      while(metal == 1){
        sensor3 = analogRead(IR3);
        if(sensor3<500){
        metal = 0;
        sensor2 = 1023;
        sensor1 = 1023;
        digitalWrite(led, LOW);
        }
      }
    }
    else if(metal == 0 && waiter > 150){
      delay(1);
      waiter = 0;
      Serial.println("No metal detected");
      servo1.write(135);

      while(sensor4 > 500 && sensor4 < 900){
            sensor4 = analogRead(IR4)-200;
            Serial.println("waiting for IR4 to be triggered, Trigger the IR4 SENSOR");
            if(sensor4 < 500){
              Serial.println("Sensor 4 is triggered"); //IR4 is below 500
              servo1.write(50);
              waiter = 0;
            }
                                    while(sensor4 < 500){
                                        servo2.write(90);    
                                        Serial.println(plastic);                                    
                                        Serial.print("Waiting for the plastic, PLASTIC VALUE: ");                                        
                                        waiter++;
                                        plastic = digitalRead(6);//value is 1 if detected something
                                        Serial.println(waiter);
                                        Serial.println(plastic);
                                        if( plastic == 1 && waiter < 3500){
                                            Serial.println("Plastic is detected"); 
                                            waiter = 0;   
                                                                  
                                                      while(plastic == 1){
                                                        waiter++;
                                                        Serial.println("Waiting for IR5 to be triggered");
                                                        sensor5 = analogRead(IR5);
                                                        if(sensor5<500){
                                                          Serial.println("Sensor 5 is triggered");                                    
                                                          plastic = 0;
                                                          sensor4 = 1023;
                                                          sensor1 = 1023;
                                                          sensor2 = 1023;
                                                          digitalWrite(led, LOW);
                                                        } 
                                                        delay(1);
                                                      }
                                                      
                                        }
                                        else if(plastic == 0 && waiter > 150){
                                          Serial.println("No metal or plastic detected");
                                          servo2.write(135);
                                          delay(6000); //wait 6 seconds before closing again the servo 2
                                          servo2.write(90);
                                          sensor4 = 1023;
                                          sensor1 = 1023;
                                          sensor2 = 1023;
                                          delay(1000);
                                          digitalWrite(led, LOW);
                                        }
                              
                                      delay(1);
                                    }
      }
    }
    delay(1);
  }

  }
