#include "PCA9685.h"
#include <Wire.h> 

PCA9685 driver(B000000); //address pin for first driver
PCA9685 driver1(B000001);//address pin for second driver

//Servo Mappings
//Left Side
//First Leg 
PCA9685_ServoEval pwmServo(82, 481); // (-90deg, +90deg)
PCA9685_ServoEval pwmServo1(82, 481); // (-90deg,+90deg)
PCA9685_ServoEval pwmServo2(82, 481); // (-90deg,+90deg)
//Second Leg 
PCA9685_ServoEval pwmServo3(82, 481); // (-90deg, +90deg)
PCA9685_ServoEval pwmServo4(82, 481); // (-90deg,+90deg)
PCA9685_ServoEval pwmServo5(82, 481); // (-90deg,+90deg)
//Third Leg 
PCA9685_ServoEval pwmServo6(82, 481); // (-90deg, +90deg)
PCA9685_ServoEval pwmServo7(82, 481); // (-90deg,+90deg)
PCA9685_ServoEval pwmServo8(82, 481); // (-90deg,+90deg)

//Right Side
//Fourth Leg 
PCA9685_ServoEval pwmServo9(82, 481); // (-90deg, +90deg)
PCA9685_ServoEval pwmServo10(82, 481); // (-90deg, +90deg)
PCA9685_ServoEval pwmServo11(82, 481); // (-90deg, +90deg)
//Fifth Leg 
PCA9685_ServoEval pwmServo12(82, 481); // (-90deg, +90deg)
PCA9685_ServoEval pwmServo13(82, 481); // (-90deg, +90deg)
PCA9685_ServoEval pwmServo14(82, 481); // (-90deg, +90deg)
//Sixth Leg
PCA9685_ServoEval pwmServo15(82, 481); // (-90deg, +90deg)
PCA9685_ServoEval pwmServo16(82, 481); // (-90deg, +90deg)
PCA9685_ServoEval pwmServo17(82, 481); // (-90deg, +90deg)

int i1L1 = 0;
int i2L1 = 0;
int i3L1 = 0;
int i4L1 = 0;

int i1L2 = 0;
int i2L2 = 0;
int i3L2 = 0;
int i4L2 = 0;

int m = 0;

boolean l1status = LOW;
boolean l2status = LOW;
byte inputData = 0;

void setup() {
  Wire.begin();                 // Wire must be started first
  Wire.setClock(400000);        // Supported baud rates are 100kHz, 400kHz, and 1000kHz
  Serial.begin(9600);
  delay(20);

  driver.resetDevices();        // Software resets all PCA9685 devices on Wire line
  driver1.resetDevices();
  
  driver.init ();         
  driver1.init();
  driver.setPWMFrequency(50);   // Set frequency to 50Hz first driver
  driver1.setPWMFrequency(50);  // Ser frequency to 50Hz second driver

//Move to initial positions
//Leg1
//driver.setChannelPWM(servo number on the driver, pwmServo.pwmForAngle(0));
  driver.setChannelPWM(0, pwmServo.pwmForAngle(60));
  driver.setChannelPWM(1, pwmServo.pwmForAngle(50));
  driver.setChannelPWM(2, pwmServo.pwmForAngle(10));
  delay(500);
//Leg2
  driver.setChannelPWM(3, pwmServo.pwmForAngle(45));
  driver.setChannelPWM(4, pwmServo.pwmForAngle(45));
  driver.setChannelPWM(5, pwmServo.pwmForAngle(6));
  delay(500);
//Leg3
  driver.setChannelPWM(6, pwmServo.pwmForAngle(30));
  driver.setChannelPWM(7, pwmServo.pwmForAngle(50));
  driver.setChannelPWM(8, pwmServo.pwmForAngle(13));
  delay(500);
//Leg4
  driver1.setChannelPWM(0, pwmServo.pwmForAngle(-20));
  driver1.setChannelPWM(1, pwmServo.pwmForAngle(-10));
  driver1.setChannelPWM(2, pwmServo.pwmForAngle(25));
  delay(500);
//Leg5
  driver1.setChannelPWM(3, pwmServo.pwmForAngle(-11));
  driver1.setChannelPWM(4, pwmServo.pwmForAngle(-22));
  driver1.setChannelPWM(5, pwmServo.pwmForAngle(25));
  delay(500);
//Leg6
  driver1.setChannelPWM(6, pwmServo.pwmForAngle(8));
  driver1.setChannelPWM(7, pwmServo.pwmForAngle(-20));
  driver1.setChannelPWM(8, pwmServo.pwmForAngle(10));
  delay (3000);
}

void loop() {
  while (Serial.available())
  {
    int inputData= (Serial.read()-'0');
    if (inputData == 1) {
      m = 1;
  }
    if (inputData == 2) {
      m =2; 
  }
    if (inputData == 3) {
      m = 3;
    }
    if (inputData == 4) {
      m = 4;
    }
    if (inputData ==0) {
      initialPosition();
    }
  }
  //Forward
  if (m == 1) {
    moveLeg1();
    moveLeg3();
    moveLeg5();
    if (l1status == HIGH) { 
      moveLeg2();
      moveLeg4();
      moveLeg6();
    }
  }
  //Reverse
  if (m == 2) {
    moveLeg1Rev();
    moveLeg3Rev();
    moveLeg5Rev();
    if (l1status == HIGH) {
      moveLeg2Rev();
      moveLeg4Rev();
      moveLeg6Rev();
    }
  }
  //Left
  if ( m == 4) {
    moveLeg1();
    moveLeg3();
    moveLeg5Left();
    if (l1status == HIGH){
      moveLeg2();
      moveLeg4Left();
      moveLeg6Left();
    }
  }
  //Right
  if ( m == 3) {
    moveLeg1Right();
    moveLeg3Right();
    moveLeg5();
    if (l1status == HIGH){
      moveLeg2Right();
      moveLeg4();
      moveLeg6();
    }
  }
  delay(30); // Walking speed(Recommended==30)
}


void moveLeg1() {
  // Swign phase - move leg though air - from initial to final position
  // Rise the leg
  if (i1L1 <= 10)
  {
    driver.setChannelPWM(1, pwmServo.pwmForAngle(50 + i1L1 * 2));
    driver.setChannelPWM(2, pwmServo.pwmForAngle(10 + i1L1 * 3));
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    driver.setChannelPWM(0, pwmServo.pwmForAngle(60+i2L1));
    i2L1++;
  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 <= 10) {
    driver.setChannelPWM(1, pwmServo.pwmForAngle(70 - i3L1 * 2));        //(the degree here is the result after adding (i1L1*2 and i1L1*3) from initial positions)
    driver.setChannelPWM(2, pwmServo.pwmForAngle(40 - i3L1 * 3));
    i3L1++;
  }
  
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    driver.setChannelPWM(0, pwmServo.pwmForAngle(90 - i4L1));
    i4L1++;
    l1status = HIGH;
  }
  // Reset the counters for repeating the process
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
  }
}


void moveLeg2(){
   if (i1L2 <= 10) {
    driver.setChannelPWM(4, pwmServo.pwmForAngle(45 + i1L2 * 2));
    driver.setChannelPWM(5, pwmServo.pwmForAngle(6 + i1L2 * 3));
    i1L2++;
  }
  if (i2L2 <= 30) {
    driver.setChannelPWM(3, pwmServo.pwmForAngle(45+i2L2));
    i2L2++;
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    driver.setChannelPWM(4, pwmServo.pwmForAngle(65 - i3L2 * 2));
    driver.setChannelPWM(5, pwmServo.pwmForAngle(36 - i3L2 * 3));
    i3L2++;
  }
  if (i2L2 >= 30) {
    driver.setChannelPWM(3, pwmServo.pwmForAngle(75 - i4L2));
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
}
}

void moveLeg3() {
  if (i1L1 <= 10) {
    driver.setChannelPWM(7, pwmServo.pwmForAngle(50 + i1L1 * 2));
    driver.setChannelPWM(8, pwmServo.pwmForAngle(13 + i1L1 * 3));
  }
  if (i2L1 <= 30) {
    driver.setChannelPWM(6, pwmServo.pwmForAngle(30+i2L1));
  }
  if (i2L1 > 20 & i3L1 <= 10) {
    driver.setChannelPWM(7, pwmServo.pwmForAngle(70 - i3L1 * 2));
    driver.setChannelPWM(8, pwmServo.pwmForAngle(43 - i3L1 * 3));
  }
  if (i2L1 >= 30) {
    driver.setChannelPWM(6, pwmServo.pwmForAngle(60 - i4L1)); 
  }
}


void moveLeg4() {
  if (i1L2 <= 10) {
    driver1.setChannelPWM(1, pwmServo.pwmForAngle(-10 - i1L2 *2));
    driver1.setChannelPWM(2, pwmServo.pwmForAngle(25 - i1L2 *3));
  }
  if (i2L2 <= 30) {
    driver1.setChannelPWM(0, pwmServo.pwmForAngle(-20 - i2L2));
  }
  if (i2L2 > 20 & i3L2 <= 30) {
    driver1.setChannelPWM(1, pwmServo.pwmForAngle(-30 + i3L2 *2));
    driver1.setChannelPWM(2, pwmServo.pwmForAngle(-5 + i3L2 *3));
  }
  if (i2L2 >= 30) {
    driver1.setChannelPWM(0, pwmServo.pwmForAngle(-50 + i4L2));
  }
}
void moveLeg5() {
  if (i1L1 <= 10) {
    driver1.setChannelPWM(4, pwmServo.pwmForAngle(-22 - i1L1 *2));
    driver1.setChannelPWM(5, pwmServo.pwmForAngle(25 - i1L1 *3));
  }
  if (i2L1 <= 30) {
    driver1.setChannelPWM(3, pwmServo.pwmForAngle(-11 - i2L1));
  }
  if (i2L1 > 20 & i3L1 <= 30) {
    driver1.setChannelPWM(4, pwmServo.pwmForAngle(-42 + i3L1 *2));
    driver1.setChannelPWM(5, pwmServo.pwmForAngle(-5 + i3L1 *3));
  }
  if (i2L1 >= 30) {
    driver1.setChannelPWM(3, pwmServo.pwmForAngle(-41 + i4L1));
  }
}
void moveLeg6() {
  if (i1L2 <= 10) {
    driver1.setChannelPWM(7, pwmServo.pwmForAngle(-20 - i1L2 *2));
    driver1.setChannelPWM(8, pwmServo.pwmForAngle(10 - i1L2 *3));
  }
  if (i2L2 <= 30) {
    driver1.setChannelPWM(6, pwmServo.pwmForAngle(8 - i2L2));
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    driver1.setChannelPWM(7, pwmServo.pwmForAngle(-40 + i3L2 *2));
    driver1.setChannelPWM(8, pwmServo.pwmForAngle(-20 + i3L2 *3));
  }
  if (i2L2 >= 30) {
    driver1.setChannelPWM(6, pwmServo.pwmForAngle(-22 + i4L2));
  }
}
void moveLeg1Rev(){
  if (i1L1 <= 10)
  {
    driver.setChannelPWM(1, pwmServo.pwmForAngle(50 + i1L1 * 2));
    driver.setChannelPWM(2, pwmServo.pwmForAngle(10 + i1L1 * 3));
    i1L1++;
  }
  if (i2L1 <= 30) {
    driver.setChannelPWM(0, pwmServo.pwmForAngle(60-i2L1));
    i2L1++;
  }

  if (i2L1 > 20 & i3L1 <= 10) {
    driver.setChannelPWM(1, pwmServo.pwmForAngle(70 - i3L1 * 2)); //(the degree here is the result after adding (i1L1*2 and i1L1*3) from initial positions)
    driver.setChannelPWM(2, pwmServo.pwmForAngle(40 - i3L1 * 3));
    i3L1++;
  }
  if (i2L1 >= 30) {
    driver.setChannelPWM(0, pwmServo.pwmForAngle(30 + i4L1));
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
  }
}
void moveLeg2Rev(){
  if (i1L2 <= 10) {
    driver.setChannelPWM(4, pwmServo.pwmForAngle(45 + i1L2 * 2));
    driver.setChannelPWM(5, pwmServo.pwmForAngle(6 + i1L2 * 3));
    i1L2++;
  }
  if (i2L2 <= 30) {
    driver.setChannelPWM(3, pwmServo.pwmForAngle(45-i2L2));
    i2L2++;
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    driver.setChannelPWM(4, pwmServo.pwmForAngle(65 - i3L2 * 2));
    driver.setChannelPWM(5, pwmServo.pwmForAngle(36 - i3L2 * 3));
    i3L2++;
  }
  if (i2L2 >= 30) {
    driver.setChannelPWM(3, pwmServo.pwmForAngle(15+i4L2));
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
}
}
void moveLeg3Rev(){
  if (i1L1 <= 10) {
    driver.setChannelPWM(7, pwmServo.pwmForAngle(50 + i1L1 * 2));
    driver.setChannelPWM(8, pwmServo.pwmForAngle(13 + i1L1 * 3));
  }
  if (i2L1 <= 30) {
    driver.setChannelPWM(6, pwmServo.pwmForAngle(30-i2L1));
  }
  if (i2L1 > 20 & i3L1 <= 10) {
    driver.setChannelPWM(7, pwmServo.pwmForAngle(70 - i3L1 * 2));
    driver.setChannelPWM(8, pwmServo.pwmForAngle(43 - i3L1 * 3));
  }
  if (i2L1 >= 30) {
    driver.setChannelPWM(6, pwmServo.pwmForAngle(0 + i4L1)); 
  }
}
void moveLeg4Rev(){
  if (i1L2 <= 10) {
    driver1.setChannelPWM(1, pwmServo.pwmForAngle(-10 - i1L2 *2));
    driver1.setChannelPWM(2, pwmServo.pwmForAngle(25 - i1L2 *3));

  }
  if (i2L2 <= 30) {
    driver1.setChannelPWM(0, pwmServo.pwmForAngle(-20 + i2L2));

  }
  if (i2L2 > 20 & i3L2 <= 30) {
    driver1.setChannelPWM(1, pwmServo.pwmForAngle(-30 + i3L2 *2));
    driver1.setChannelPWM(2, pwmServo.pwmForAngle(-5 + i3L2 *3));
  }
  if (i2L2 >= 30) {
    driver1.setChannelPWM(0, pwmServo.pwmForAngle(10 - i4L2));
  }
}
void moveLeg5Rev(){
  if (i1L1 <= 10) {
    driver1.setChannelPWM(4, pwmServo.pwmForAngle(-22 - i1L1 *2));
    driver1.setChannelPWM(5, pwmServo.pwmForAngle(25 - i1L1 *3));
  }
  if (i2L1 <= 30) {
    driver1.setChannelPWM(3, pwmServo.pwmForAngle(-11 + i2L1));

  }
  if (i2L1 > 20 & i3L1 <= 30) {
    driver1.setChannelPWM(4, pwmServo.pwmForAngle(-42 + i3L1 *2));
    driver1.setChannelPWM(5, pwmServo.pwmForAngle(-5 + i3L1 *3));
  }
  if (i2L1 >= 30) {
    driver1.setChannelPWM(3, pwmServo.pwmForAngle(19 - i4L1));
  }
}
void moveLeg6Rev(){
  if (i1L2 <= 10) {
    driver1.setChannelPWM(7, pwmServo.pwmForAngle(-20 - i1L2 *2));
    driver1.setChannelPWM(8, pwmServo.pwmForAngle(10 - i1L2 *3));
  }
  if (i2L2 <= 30) {
    driver1.setChannelPWM(6, pwmServo.pwmForAngle(8 + i2L2));
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    driver1.setChannelPWM(7, pwmServo.pwmForAngle(-40 + i3L2 *2));
    driver1.setChannelPWM(8, pwmServo.pwmForAngle(-20 + i3L2 *3));
  }
  if (i2L2 >= 30) {
    driver1.setChannelPWM(6, pwmServo.pwmForAngle(38 - i4L2));
  }
}
void moveLeg1Right() {
  if (i1L1 <= 10)
  {
    driver.setChannelPWM(1, pwmServo.pwmForAngle(50 + i1L1 * 2));
    driver.setChannelPWM(2, pwmServo.pwmForAngle(10 + i1L1 * 3));
    i1L1++;
  }
  if (i2L1 <= 30) {
    driver.setChannelPWM(0, pwmServo.pwmForAngle(60-i2L1));
    i2L1++;
  }

  if (i2L1 > 20 & i3L1 <= 10) {
    driver.setChannelPWM(1, pwmServo.pwmForAngle(70 - i3L1 * 2)); //(the degree here is the result after adding (i1L1*2 and i1L1*3) from initial positions)
    driver.setChannelPWM(2, pwmServo.pwmForAngle(40 - i3L1 * 3));
    i3L1++;
  }
  if (i2L1 >= 30) {
    driver.setChannelPWM(0, pwmServo.pwmForAngle(30 + i4L1));
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
  }
}
void moveLeg2Right(){
  if (i1L2 <= 10) {
    driver.setChannelPWM(4, pwmServo.pwmForAngle(45 + i1L2 * 2));
    driver.setChannelPWM(5, pwmServo.pwmForAngle(6 + i1L2 * 3));
    i1L2++;
  }
  if (i2L2 <= 30) {
    driver.setChannelPWM(3, pwmServo.pwmForAngle(45-i2L2));
    i2L2++;
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    driver.setChannelPWM(4, pwmServo.pwmForAngle(65 - i3L2 * 2));
    driver.setChannelPWM(5, pwmServo.pwmForAngle(36 - i3L2 * 3));
    i3L2++;
  }
  if (i2L2 >= 30) {
    driver.setChannelPWM(3, pwmServo.pwmForAngle(15+i4L2));
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
}
}
void moveLeg3Right() {
  if (i1L1 <= 10) {
    driver.setChannelPWM(7, pwmServo.pwmForAngle(50 + i1L1 * 2));
    driver.setChannelPWM(8, pwmServo.pwmForAngle(13 + i1L1 * 3));
  }
  if (i2L1 <= 30) {
    driver.setChannelPWM(6, pwmServo.pwmForAngle(30-i2L1));
  }
  if (i2L1 > 20 & i3L1 <= 10) {
    driver.setChannelPWM(7, pwmServo.pwmForAngle(70 - i3L1 * 2));
    driver.setChannelPWM(8, pwmServo.pwmForAngle(43 - i3L1 * 3));
  }
  if (i2L1 >= 30) {
    driver.setChannelPWM(6, pwmServo.pwmForAngle(0 + i4L1)); 
  }
}
void moveLeg4Left() {
  if (i1L2 <= 10) {
    driver1.setChannelPWM(1, pwmServo.pwmForAngle(-10 - i1L2 *2));
    driver1.setChannelPWM(2, pwmServo.pwmForAngle(25 - i1L2 *3));
  }
  if (i2L2 <= 30) {
    driver1.setChannelPWM(0, pwmServo.pwmForAngle(-20 + i2L2));
  }
  if (i2L2 > 20 & i3L2 <= 30) {
    driver1.setChannelPWM(1, pwmServo.pwmForAngle(-30 + i3L2 *2));
    driver1.setChannelPWM(2, pwmServo.pwmForAngle(-5 + i3L2 *3));
  }
  if (i2L2 >= 30) {
    driver1.setChannelPWM(0, pwmServo.pwmForAngle(10 - i4L2));
  }
}
void moveLeg5Left() {
  if (i1L1 <= 10) {
    driver1.setChannelPWM(4, pwmServo.pwmForAngle(-22 - i1L1 *2));
    driver1.setChannelPWM(5, pwmServo.pwmForAngle(25 - i1L1 *3));
  }
  if (i2L1 <= 30) {
    driver1.setChannelPWM(3, pwmServo.pwmForAngle(-11 + i2L1));
  }
  if (i2L1 > 20 & i3L1 <= 30) {
    driver1.setChannelPWM(4, pwmServo.pwmForAngle(-42 + i3L1 *2));
    driver1.setChannelPWM(5, pwmServo.pwmForAngle(-5 + i3L1 *3));
  }
  if (i2L1 >= 30) {
    driver1.setChannelPWM(3, pwmServo.pwmForAngle(19 - i4L1));
  }
}
void moveLeg6Left() {
  if (i1L2 <= 10) {
    driver1.setChannelPWM(7, pwmServo.pwmForAngle(-20 - i1L2 *2));
    driver1.setChannelPWM(8, pwmServo.pwmForAngle(10 - i1L2 *3));
  }
  if (i2L2 <= 30) {
    driver1.setChannelPWM(6, pwmServo.pwmForAngle(8 + i2L2));
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    driver1.setChannelPWM(7, pwmServo.pwmForAngle(-40 + i3L2 *2));
    driver1.setChannelPWM(8, pwmServo.pwmForAngle(-20 + i3L2 *3));
  }
  if (i2L2 >= 30) {
    driver1.setChannelPWM(6, pwmServo.pwmForAngle(38 - i4L2));
  }
}
void initialPosition() {
  m = 0;
  l1status = LOW;
  l2status = LOW;
  //delay(30);
//Leg1
  driver.setChannelPWM(0, pwmServo.pwmForAngle(60));
  driver.setChannelPWM(1, pwmServo.pwmForAngle(50));
  driver.setChannelPWM(2, pwmServo.pwmForAngle(10));
  delay(10);
//Leg2
  driver.setChannelPWM(3, pwmServo.pwmForAngle(45));
  driver.setChannelPWM(4, pwmServo.pwmForAngle(45));
  driver.setChannelPWM(5, pwmServo.pwmForAngle(6));
  delay(10);
//Leg3
  driver.setChannelPWM(6, pwmServo.pwmForAngle(30));
  driver.setChannelPWM(7, pwmServo.pwmForAngle(50));
  driver.setChannelPWM(8, pwmServo.pwmForAngle(13));
  delay(10);
//Leg4
  driver1.setChannelPWM(0, pwmServo.pwmForAngle(-20));
  driver1.setChannelPWM(1, pwmServo.pwmForAngle(-10));
  driver1.setChannelPWM(2, pwmServo.pwmForAngle(25));
  delay(10);
//Leg5
  driver1.setChannelPWM(3, pwmServo.pwmForAngle(-11));
  driver1.setChannelPWM(4, pwmServo.pwmForAngle(-22));
  driver1.setChannelPWM(5, pwmServo.pwmForAngle(25));
  delay(10);
//Leg6
  driver1.setChannelPWM(6, pwmServo.pwmForAngle(8));
  driver1.setChannelPWM(7, pwmServo.pwmForAngle(-20));
  driver1.setChannelPWM(8, pwmServo.pwmForAngle(10));
  delay(10);

  i1L1 = 0;
  i2L1 = 0;
  i3L1 = 0;
  i4L1 = 0;

  i1L2 = 0;
  i2L2 = 0;
  i3L2 = 0;
  i4L2 = 0;
}
