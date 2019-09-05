/********************************************************* 
 *  DC_motor_test
 *  Jonathan Gusler
 *  August, 2019
 *  
 *  Description: This program controls a motor in two ways.
 *  The program controls the motors speed and spin direction.
 *  The default/starting state is off and blowing air
 *  toward the motor. The yellow button controls the speed, the 
 *  green button controls the direction. The speed changes from 
 *  off to high to low to off. Whenever the yellow button is pressed
 *  the program waits 50ms and then checks if the green button is 
 *  also pressed. If both are pressed, the motor is reset to off
 *  and blowing towards the motor.
 *  
 *  To handle debouncing, a delay is added after each button press 
 *  detection to wait before double checking that the button is pressed.
 *********************************************************/
void setup()
{
pinMode(14,OUTPUT); //init pin 14 as output 
pinMode(12,OUTPUT); //init pin 12 as output
pinMode(13,INPUT);  //init pin 13 as yellow button which changes motor speed
pinMode(15,INPUT);  //init pin 15 as green button which changes motor direction
}



/****************************************/



//Create variable to keep track of yellow button, which correlates to the motor speed
int YellowButtonState = 0;

//Create variable to keep track of green button, which correlates to the spin direction
int GreenButtonState = 0;

//How to reset motor to off and default direction: press both buttons simultaneously
void MotorReset (){
    YellowButtonState = 0;
    GreenButtonState = 0;
}


void loop()
{
  
  //This section keeps track of the yellow button 
  if (digitalRead(13) == HIGH){
    delay(100); //Makes the program wait before reading again to see if the button
                // is still pressed, indicating an actual press, not a bounce
    //Off to High
    if (digitalRead(13) == HIGH && YellowButtonState == 0){
      //delay(50);
      if (digitalRead(15) == HIGH){
        MotorReset();
        return;
      }
      YellowButtonState = 1;
    }
  
    //High to low
    if (digitalRead(13) == HIGH && YellowButtonState == 1){
      //delay(50);
      if (digitalRead(15) == HIGH){
        MotorReset();
        return;
      }
      YellowButtonState = 2;
    }
  
    //Low to off
    if (digitalRead(13) == HIGH && YellowButtonState == 2){
      //delay(50);
      if (digitalRead(15) == HIGH){
        MotorReset();
        return;
      }
      YellowButtonState = 0;
    }
  }

  //This section keeps track of the green button state
  if (digitalRead(15) == HIGH){
    delay(100); //Makes the program wait before reading again to see if the button
                // is still pressed, indicating an actual press, not a bounce
    //Blow away from motor
    if (digitalRead(15) == HIGH && GreenButtonState == 1){
      //delay(50);
      if (digitalRead(13) == HIGH){
        MotorReset();
        return;
      }
      GreenButtonState = 0;
    }
  
    //Blow towards motor
    if (digitalRead(15) == HIGH && GreenButtonState == 0){
      //delay(50);
      if (digitalRead(13) == HIGH){
        MotorReset();
        return;
      }
      GreenButtonState = 1;
    }
  }

  //This section sends the speed and direction signals to the motor
  if(YellowButtonState == 0){
    if(GreenButtonState == 0){
      counterclockwise(0);
    }
    else 
      clockwise(0);
  }
  if(YellowButtonState == 1){
    if(GreenButtonState == 0){
      counterclockwise(1000);
    }
    else 
      clockwise(1000);
  }
  if(YellowButtonState == 2){
    if(GreenButtonState == 0){
      counterclockwise(500);
    }
    else 
      clockwise(500);
  } 
}

/****************************************/
//The function to drive motor rotate clockwise
void clockwise(int Speed)
{
  analogWrite(14,Speed); //turn one pin on
  analogWrite(12,0);     //turn the other pin off
}
//The function to drive motor rotate counterclockwise
void counterclockwise(int Speed)
{
  analogWrite(14,0);     //turn one pin off
  analogWrite(12,Speed); //turn the other pin on
}
/****************************************/
