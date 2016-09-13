uint16_t debug =1;
int sensorPin[] = {A0, A1, A2};    // pin that the lightsensor is attached to
int piezoPin[] = {A3};
const int arraySize=100;
const int r[] ={5, 11};
const int g[] ={6, 12};
const int b[] = {7, 13};
const int sensitivity=100;
const int piezoSensitivity = 1000;

float rawValueArray[arraySize];
float piezoValueArray[arraySize];
float commulatedSensorValue[3];
float commulatedPiezoValue[3];
int piezoSensorValue[3];
float sensorValue = 0;         // the sensor value
float piezoValue = 0;
float sensorMin[] = {1023, 1023, 1023};        // minimum sensor value
float sensorMax[] = {0, 0, 0};           // maximum sensor value
float piezoMax[] = {1023, 1023, 1023};        // minimum sensor value
float piezoMin[] = {0, 0, 0};           // maximum sensor value
float temp=0;

int rFade = (int) random(0, 255);
int gFade = (int) random(0, 255);
int bFade = (int) random(0, 255);

int rTarget = (int) random(0, 255);
int gTarget = (int) random(0, 255);
int bTarget = (int) random(0, 255);

void setup() {

  Serial.begin(9600);

}


void loop() {
  
  calibration();
  for(int i=1000;i>0;i--){ //Rekalibrierung etwa alle 2 Minuten

    fetchNewSensorValue();
    if(commulatedSensorValue[0]>2.5){
      jump();
    }
    else if(commulatedSensorValue[1]>2.5){
      singleColor(random(0, 255), random(0, 255), random(0, 255));
    }
    else if(commulatedSensorValue[2]>2.5){
      singleFade(10);
    }
    else{
      rainbowRandom();
    }
    delay(100);
    //Serial.println(commulatedPiezoValue[0]);
  }
  
  singleColor(random(0, 255), random(0, 255), random(0, 255));
}


void fetchNewSensorValue(){
  //fetch piezo values
  //fetch values
    /*for(int h=0; h<1; h++) {
  for(int i=arraySize; i>0;i--){
      piezoValue = analogRead(piezoPin[h]);
  
      piezoValue = map(piezoValue, piezoMin[h], piezoMax[h], 0, piezoSensitivity);
      piezoValueArray[i]=piezoValue;    
  
    }
    temp=0;
    for(int a=arraySize;a>0;a--){
      temp+=piezoValueArray[a];
      //Serial.println(temp); 
      piezoValueArray[a]=0;
      ; 
    }
    //commulatedPiezoValue[h]=temp/float(arraySize)/float(100);
    }*/
  
  //fetch values
    for(int h=0; h<3; h++) {
  for(int i=arraySize; i>0;i--){
      sensorValue = analogRead(sensorPin[h]);
      if (i==10&&debug!=0) {
        Serial.println(sensorValue);
      }
      sensorValue = map(sensorValue, sensorMin[h], sensorMax[h], 0, sensitivity);
      rawValueArray[i]=sensorValue;    
  
    }
    temp=0;
    for(int a=arraySize;a>0;a--){
      temp+=rawValueArray[a];
      //Serial.println(temp); 
      rawValueArray[a]=0;
    }
    commulatedSensorValue[h]=temp/float(arraySize)/float(100);
  Serial.println(commulatedSensorValue[0]);
  /*
 commulatedSensorValue= map(commulatedSensorValue, -3200, 3200, -100, 100);
   Serial.println(commulatedSensorValue);
   */
  //commulatedSensorValue=0;
  }
}

void calibration(){
  Serial.println("calibration...");
    //light
    for(int h=0; h<3; h++) {
  sensorMin[h] = 1023;        // minimum sensor value
  sensorMax[h] = 0;           // maximum sensor value
  for(int i =1000;i>0;i--){
    sensorValue = analogRead(sensorPin[h]);

    // record the maximum sensor value
    if (sensorValue > sensorMax[h]) {
      sensorMax[h] = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin[h]) {
      sensorMin[h] = sensorValue;
    }
    }
  }
  for(int i=0; i <1; i++) {
  Serial.println(i);
  Serial.print("lightmax: ");
  Serial.println(sensorMax[i]);
  Serial.print("ligmin: ");
  Serial.println(sensorMin[i]);
  }
  //piezo
  /*for(int h=0; h<3; h++) {
  piezoMin[h] = 1023;        // minimum sensor value
  piezoMax[h] = 0;           // maximum sensor value
  for(int i =100;i>0;i--){
    sensorValue = analogRead(piezoPin[h]);

    // record the maximum sensor value
    if (sensorValue > piezoMax[h]) {
      piezoMax[h] = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < piezoMin[h]) {
      piezoMin[h] = sensorValue;
    }
    }
  }
  for(int i=0; i <1; i++) {
  Serial.println(i);
  Serial.print("piezomax: ");
  Serial.println(piezoMax[i]);
  Serial.print("piezomin: ");
  Serial.println(piezoMin[i]);
  }*/
}


void jump() {
  int sleep=100;

  for(int h=0; h < 3; h++) {
    //Serial.print("h: ");
    //Serial.println(h);
    if(h==0) {
      light('r', 255);
      delay(sleep);
      light('r', 0);
      delay(sleep);
    }
    if(h==1) {
      light('g', 255);
      delay(sleep);
      light('g', 0);
      delay(sleep);
    }
    if(h==2) {
      light('b', 255);
      delay(sleep);
      light('b', 0);
      delay(sleep);
    }
  }

}

void singleColor(int rColor, int gColor, int bColor) {
    int sleep = 100;
    rFade = rColor;
    gFade = gColor;
    bFade = bColor;
    
   light('r', rFade);
   light('g', gFade);
   light('b', bFade);
   delay(sleep); 
  }
  
  void singleFade(int tempo) {
   rFade = 0;
   gFade = 0;
   bFade = 0;
   
   light('r', rFade); 
   light('g', gFade); 
   light('b', bFade); 
  
  for(int h=0; h < 2; h++) {
   for(int i = 0; i < 256; i++) {
    switch(h) {
     case 0:
        light('r', i);
        delay(tempo);
       break; 
       case 1:
        light('g', i);
        delay(tempo);
       break; 
       case 2:
        light('b', i);
        delay(tempo);
       break; 
    }
    for(int i = 256; i < 0; i--) {
    switch(h) {
     case 0:
        light('r', i);
        delay(tempo);
       break; 
       case 1:
        light('g', i);
        delay(tempo);
       break; 
       case 2:
        light('b', i);
        delay(tempo);
       break; 
    }
   } 
  }
  }
  }

void rainbowRandom() {
  int sleep = 1;

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

  light('r', rFade);
  light('g', gFade);
  light('b', bFade);

  //delay(sleep);

}
//function that cotrols multiple LEDS at once
void light(char color, int brightness) {
   switch(color) {
    
    case 'r':
              for(int i= 0; i < 2; i++) {
                analogWrite(r[i], brightness);
              }
                break;
                
    case 'g':
              for(int i= 0; i < 2; i++) {
                analogWrite(g[i], brightness);
              }
                break;
                
    case 'b':
              for(int i= 0; i < 2; i++) {
                analogWrite(b[i], brightness);
              }
                break;
   }
}

