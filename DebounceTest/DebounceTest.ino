void setup() {
  // put your setup code here, to run once:
  pinMode(15,INPUT);
  Serial.begin(9600);
}
int n = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(15) == HIGH){
    Serial.println(n);
    n++;
  }
 
}
