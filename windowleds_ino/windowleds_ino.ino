const int sensorPin = A0;    // pin that the sensor is attached to
const int arraySize=100;
const int r=8;
const int g=9;
const int b=10;
const int sensitivity=100;

float rawValueArray[arraySize];
float commulatedSensorValue=0;
float sensorValue = 0;         // the sensor value
float sensorMin = 1023;        // minimum sensor value
float sensorMax = 0;           // maximum sensor value
float temp=0;

int rFade = (int) random(0, 255);
int gFade = (int) random(0, 255);
int bFade = (int) random(0, 255);

int rTarget = (int) random(0, 255);
int gTarget = (int) random(0, 255);
int bTarget = (int) random(0, 255);

void setup() {

  Serial.begin(115200);

}


void loop() {
  calibration();
  for(int i=1000;i>0;i--){ //Rekalibrierung etwa alle 2 Minuten

    fetchNewSensorValue();
    if(commulatedSensorValue<-10){
      jump();

    }
    else{
      rainbowRandom();
    }

    //delay(100);
  }
}


void fetchNewSensorValue(){
  for(int i=arraySize; i>0;i--){
    sensorValue = analogRead(sensorPin);

    sensorValue = map(sensorValue, sensorMin, sensorMax, 0, sensitivity);
    rawValueArray[i]=sensorValue;    

  }
  temp=0;
  for(int a=arraySize;a>0;a--){
    temp+=rawValueArray[a];
    //Serial.println(temp); 
    rawValueArray[a]=0;
    ; 
  }
  commulatedSensorValue=temp/float(arraySize)/float(100);
  //Serial.println(commulatedSensorValue);
  /*
 commulatedSensorValue= map(commulatedSensorValue, -3200, 3200, -100, 100);
   Serial.println(commulatedSensorValue);
   */
  //commulatedSensorValue=0;
}

void calibration(){
  //Serial.println("calibration...");
  sensorMin = 1023;        // minimum sensor value
  sensorMax = 0;           // maximum sensor value

  for(int i =1000;i>0;i--){
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }

  }
  /*
  Serial.print("max: ");
  Serial.println(sensorMax);
  Serial.print("min: ");
  Serial.println(sensorMin);
*/
}


void jump() {
  int sleep=100;

  for(int h=0; h < 3; h++) {
    //Serial.print("h: ");
    //Serial.println(h);
    if(h==0) {
      analogWrite(r, 255);
      delay(sleep);
      analogWrite(r, 0);
      delay(sleep);
    }
    if(h==1) {
      analogWrite(g, 255);
      delay(sleep);
      analogWrite(g, 0);
      delay(sleep);
    }
    if(h==2) {
      analogWrite(b, 255);
      delay(sleep);
      analogWrite(b, 0);
      delay(sleep);
    }
  }

}

void rainbowRandom() {

  if(rFade == rTarget) {
    rTarget = (int) random(0, 255);
  }
  if(gFade == gTarget) {
    gTarget = (int) random(0, 255);
  }
  if(bFade == bTarget) {
    bTarget = (int) random(0, 255);
  }

  if(rFade < rTarget) {
    rFade++;
  } 
  else {
    rFade--;
  }
  if(gFade < gTarget) {
    gFade++;
  } 
  else {
    gFade--;
  }
  if(bFade < bTarget) {
    bFade++;
  } 
  else {
    bFade--;
  }

  rFade = max(rFade, 0);
  rFade = min(rFade, 255);

  gFade = max(gFade, 0);
  gFade = min(gFade, 255);

  bFade = max(bFade, 0);
  bFade = min(bFade, 255);

  analogWrite(r, rFade);
  analogWrite(g, gFade);
  analogWrite(b, bFade);

  delay(100);

}

