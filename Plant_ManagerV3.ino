//Lance Einfeld ENME351 FINAL PROJECT 5-12-2020

//Sensor readings for callibration-----------------------------------------
//moist ~(air water dry wet):~(595 280 460 360)
//moist1 basil ~(air water dry wet):(595 280 460 320)
//light window ~100
//light low/indoor ~260
//temp1 [10k]: 523@74 535@72 600@62
//temp2 [503]: 542@74 553@72 626@62

//configurables------------------------------------------------------------
int plantnum=1;//number of plants (1 to 4)
int setlevels[][4]={{350,480,100,525},//plant 1 {wetsoil,drysoil,light,temp} [sensor readings]
                   {360,490,260,543},//plant 2 "   "
                   {0,0,0,0},
                   {0,0,0,0}};
int pumppins[]={2,3,99,99};//{plant1,2,3,4}(99 is no pin)
int sensorpins[][3]={{0,2,4},{1,3,5},//{{moist1,light1,temp1},{moist2,light2,...}}(99 is no pin)
                    {99,99,99},{99,99,99}};
//-------------------------------------------------------------------------
bool watering=false;
bool wait=false;

void setup() {
for(int i=0;i<plantnum;i++){
pinMode(pumppins[i],OUTPUT);
digitalWrite(pumppins[i],LOW);
}
Serial.begin(9600);
}

void loop() {
for(int i=0;i<plantnum;i++){//cycles plant to water, still reads all plants
  int moist=analogRead(sensorpins[i][0]);
  if(moist>=setlevels[i][1]){
    watering=true;
  }
  while(watering==true){
    if(wait==false){
      digitalWrite(pumppins[i],HIGH);
      for(int m=0;m<30;m++){//water for 30*100 ms while reading out
        printout(plantnum,setlevels,sensorpins);
        delay(100);
        wait=true;
      }
    }
    else if(wait==true){
      digitalWrite(pumppins[i],LOW);
      for(int m=0;m<150;m++){//wait for 150*100 ms while reading out
        printout(plantnum,setlevels,sensorpins);
        delay(100);
        wait=false;
      }
    }
    moist=analogRead(sensorpins[i][0]);
    if(moist<=setlevels[i][0]){//check if moisture level is met
      watering=false;
    }
  }
  printout(plantnum,setlevels,sensorpins);
  delay(100);
}
}



//print values to serial monitor
void printout(int x,int setlevels[][4],int sensorpins[][3]){
  Serial.print(x);
  for(int j=0;j<x;j++){
    for(int k=0;k<4;k++){
      Serial.print(",");
      Serial.print(setlevels[j][k]);
    }
    for(int l=0;l<3;l++){
      Serial.print(",");
      Serial.print(analogRead(sensorpins[j][l]));
    }
    }
    Serial.println();
    }
