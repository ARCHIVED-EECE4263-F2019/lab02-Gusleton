//DC Motor Control

//The DC motor will begin rotating left and right, and its speed will vary accordingly.
//Email:support@sunfounder.com
//Website:www.sunfounder.com
//2015.5.7

void setup()
{
Serial.begin(9600);
pinMode(14,OUTPUT); //initialize the motorIn1 pin as output 
pinMode(12,OUTPUT); //initialize the motorIn2 pin as output 
pinMode(13,INPUT);  //init pin 13 as yellow button which changes motor speed
pinMode(15,INPUT);  //init pin 15 as green button which changes motor direction
}



/****************************************/



//Create variable to keep track of yellow button
int YellowButtonState = 0;

//Create variable to keep track of green button
int GreenButtonState = 0;

//Variable that controls delay in milliseconds to debounce buttons
int debounce = 250;

  //How to reset motor to off and default direction: press both buttons simultaneously
void MotorReset (){
    YellowButtonState = 0;
    GreenButtonState = 0;
    delay(debounce); //Debounce.... hopefully
    Serial.println("Reset");
}


void loop()
{
  
  //Keep track of yellow button state
  if (digitalRead(13) == HIGH && YellowButtonState == 0){
    delay(50);
    if (digitalRead(15) == HIGH){
      MotorReset();
      return;
    }
    delay(debounce); //Debounce.... hopefully
    YellowButtonState = 1; //Motor high
    Serial.println("high");
  }
  if (digitalRead(13) == HIGH && YellowButtonState == 1){
    delay(50);
    if (digitalRead(15) == HIGH){
      MotorReset();
      return;
    }
    delay(debounce); //Debounce.... hopefully
    YellowButtonState = 2; //Motor low
    Serial.println("low");
  }
  if (digitalRead(13) == HIGH && YellowButtonState == 2){
    delay(50);
    if (digitalRead(15) == HIGH){
      MotorReset();
      return;
    }
    delay(debounce); //Debounce.... hopefully
    YellowButtonState = 0; //Motor off
    Serial.println("off");
  }

  //Keep track of green button state
  if (digitalRead(15) == HIGH && GreenButtonState == 1){
    delay(50);
    if (digitalRead(13) == HIGH){
      MotorReset();
      return;
    }
    delay(debounce); //Debounce.... hopefully
    GreenButtonState = 0;  //Direction clockwise relative to the motor, blows away from the motor
    Serial.println("Counterclockwise");
  }
  if (digitalRead(15) == HIGH && GreenButtonState == 0){
    delay(50);
    if (digitalRead(13) == HIGH){
      MotorReset();
      return;
    }
    delay(debounce); //Debounce.... hopefully
    GreenButtonState = 1;  //Direction counterclockwise relative to the motor, blows towards motor
    Serial.println("Clockwise");
  }

  
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
      
delay(1);
}

/****************************************/
//The function to drive motor rotate clockwise
void clockwise(int Speed)
{
  analogWrite(14,Speed); //set the speed of motor
  analogWrite(12,0); //stop the motorIn2 pin of motor
}
//The function to drive motor rotate counterclockwise
void counterclockwise(int Speed)
{
  analogWrite(14,0); //stop the motorIn1 pin of motor
  analogWrite(12,Speed); //set the speed of motor
}
/****************************************/
