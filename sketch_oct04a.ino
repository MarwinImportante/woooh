int extendPin=7;
int retractPin=6;
int recordArray[21];
int recordTime=20; // nilalagay dito kung ilan yung repetitions ng pagrecord
int i;
int acc=0;
int mode=0;
int feedbackVal;

void setup(){
  Serial.begin(9600);
  pinMode(extendPin, OUTPUT);
  pinMode(retractPin, OUTPUT);
  Serial.println("Enter Mode.");
  }
void loop(){
  while (mode==0){
 
  if (Serial.available()>0){
    mode=Serial.parseInt();
    delay(1);
    Serial.print("Mode:");
    Serial.println(mode);
    }
  }
  while (mode==1){
    if (acc<recordTime){     
      recordArray[acc]=analogRead(A0);  // dito naglalagay ng data ng resistance values sa recordArray[]
      
      acc=acc+1;
      Serial.println(acc);
      delay(500);    // Ito yung time interval ng pagrecord ng resistance values
      }
     if (acc==recordTime){ // Pagkatapos ng repetitions, back to mode selection
      Serial.println("Enter Mode.");
      mode=0;
      
      }
    }
  while (mode==2){  // Playback mode, dito yung pag actuate ng solenoid valve base sa PV (current reading ng resistance) vs SP (recorded value ng resistance sa recordArray[])
    
    if (i<21){
    feedbackVal=analogRead(A0);  
    Serial.print(analogRead(A0));
    Serial.print("   ");
    Serial.println(recordArray[i]);
    delay(1);
      if (feedbackVal<recordArray[i]){
       digitalWrite(retractPin, HIGH); 
       digitalWrite(extendPin, LOW);
      }
      if (feedbackVal>recordArray[i]){
        digitalWrite(extendPin, HIGH);
        digitalWrite(retractPin, LOW);
      }
      if (feedbackVal==recordArray[i]){
        i=i+1;
      }
   }
   if (i==21){
    Serial.println("Enter Mode.");
    mode=0;
    }
}
}
    

  

