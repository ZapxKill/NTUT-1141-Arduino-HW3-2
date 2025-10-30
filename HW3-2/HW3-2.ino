unsigned int lastPressTime, lastLedUpdateTime = 0;
byte pressed = 0;
int blinkMode = 0;
int blinkTimes[4] = {0, 1000, 500, 100};
bool ledState = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(11, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonStateUpdate();
  if(blinkMode != 0){
    ledStateUpdate();
  }
  else{
    digitalWrite(3,1);
  }
}

void buttonStateUpdate(){
  unsigned int t = millis();
  if(digitalRead(11) == 1){
    pressed = 0;
  }
  // put your main code here, to run repeatedly:
  if(digitalRead(11) == 0 &&  pressed == 0){
    lastPressTime = t; 
    pressed = 1;
  }
  if(pressed == 1 && t - lastPressTime > 50){
    
    lastPressTime = t;
    pressed = 2;
    blinkMode = (blinkMode == 3)? 0 : ++blinkMode;
  }
}

void ledStateUpdate(){
  unsigned int t = millis();
  if(t-lastLedUpdateTime >= blinkTimes[blinkMode]){
    ledState = !ledState;
    digitalWrite(3, ledState);
    lastLedUpdateTime = t;
  }
}