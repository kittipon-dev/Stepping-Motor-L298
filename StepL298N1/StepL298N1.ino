#include <LiquidCrystal.h>

#define sw A0
int const enM[] = {12,13,17};
int const stepPin[] = {8,9,10,11};
int const stepData[] = {0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};
int pointM[] = {0,0,0};

String str[]= {"  Set X","  Set Y","  Set Z","  Run  "};
char iStr=0,X=0,Y=0,Z=0;
char index=0;

LiquidCrystal lcd(2,3,4,5,6,7); 

void singleMove(int enPin,int point){
  digitalWrite(enM[enPin],HIGH); 
  digitalWrite(stepPin[0],(stepData[point] & 1)? 1:0);
  digitalWrite(stepPin[1],(stepData[point] & 2)? 1:0);
  digitalWrite(stepPin[2],(stepData[point] & 4)? 1:0);
  digitalWrite(stepPin[3],(stepData[point] & 8)? 1:0);
  delay(100);
  digitalWrite(enM[enPin],LOW);
  delay(100);
}

void moveStep(int m,int value,int dir){
  int i,j,k;
  i = value / 8;
  j = value % 8;
  for(k=i;k>0;k--){
    for(value = 0; value < 8; value++){
      if(dir > 0){
        pointM[m]++;
        if(pointM[m] > 7) pointM[m] = 0;
      }else{
        pointM[m]--;
        if(pointM[m] < 0) pointM[m] = 7;
      }
      singleMove(m,pointM[m]);
    }
  }
  for(k=j;k>0;k--){
    if(dir > 0){
      pointM[m]++;
      if(pointM[m] > 7) pointM[m] = 0;
    }else{
      pointM[m]--;
      if(pointM[m] < 0) pointM[m] = 7;
    }
    singleMove(m,pointM[m]);
  }
}

void setup()
{
  int i;
  lcd.begin(16,2);                      
  for(i=0;i<3;i++){
    pinMode(enM[i],OUTPUT);
    digitalWrite(enM[i],LOW);
  }
  for(i=0;i<4;i++){
    pinMode(stepPin[i],OUTPUT);
  }
  pinMode(sw,INPUT);
  moveStep(0,pointM[0],1);
  moveStep(1,pointM[1],1);
  moveStep(2,pointM[2],1);
  showDisplay();
}
int adc,buf;

void showDisplay(){
char i=0;
lcd.clear();
if(index<2){
  for(i=0;i<2;i++){
  lcd.setCursor(0,i);
  lcd.print(str[i]);
  }
}
else{
  for(i=0;i<2;i++){
  lcd.setCursor(0,i);
  lcd.print(str[i+2]);
  }
}
if(index<2){
  lcd.setCursor(0,index);
  lcd.print("->");
}
else{
  lcd.setCursor(0,index-2);
  lcd.print("->");
  }
}
void fntSetX(){
   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set More X is...");
  lcd.setCursor(0,2);
  lcd.print(X,DEC);
  lcd.print(" mm    ");
  while(1){
    adc = analogRead(sw);
    if(adc != buf){
      if(adc ==236){
        X++;
        if(X>10){X=1;}
        lcd.setCursor(0,2);
        lcd.print("     ");
        lcd.setCursor(0,2);
        lcd.print(X,DEC);
        lcd.print(" mm ");
        
      }else if (adc == 293){
        X--;
        if(X<-10){X=1;}
        lcd.setCursor(0,2);
        lcd.print("         ");
        lcd.setCursor(0,2);
        lcd.print(X,DEC);
        lcd.print("  mm");
    }else if (adc == 171){

      break;
    }
    buf = adc;
}
delay(50);
}
showDisplay();
}
void fntSetY(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set More Y is...");
  lcd.setCursor(0,2);
  lcd.print(Y,DEC);
  lcd.print(" mm    ");
  while(1){
    adc = analogRead(sw);
    if(adc != buf){
      if(adc ==236){
        Y++;
        if(Z>10){Z=1;}
        lcd.setCursor(0,2);
        lcd.print("     ");
        lcd.setCursor(0,2);
        lcd.print(Y,DEC);
        lcd.print(" mm ");
        
      }else if (adc == 293){
        Y--;
        if(Y<-10){Y=1;}
        lcd.setCursor(0,2);
        lcd.print("         ");
        lcd.setCursor(0,2);
        lcd.print(Y,DEC);
        lcd.print("  mm");
    }else if (adc == 171){

      break;
    }
    buf = adc;
}
delay(50);
}
showDisplay();
}
void fntSetZ(){
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set More Z is...");
  lcd.setCursor(0,2);
  lcd.print(Z,DEC);
  lcd.print(" mm    ");
  while(1){
    adc = analogRead(sw);
    if(adc != buf){
      if(adc ==236){
        Z++;
        if(Z>10){Z=1;}
        lcd.setCursor(0,2);
        lcd.print("     ");
        lcd.setCursor(0,2);
        lcd.print(Z,DEC);
        lcd.print(" mm ");
        
      }else if (adc == 293){
        Z--;
        if(Z<-10){Z=1;}
        lcd.setCursor(0,2);
        lcd.print("         ");
        lcd.setCursor(0,2);
        lcd.print(Z,DEC);
        lcd.print("  mm");
    }else if (adc == 171){

      break;
    }
    buf = adc;
}
delay(50);
}
showDisplay();
}
void Run(){
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   RUN X ....   ");
  if(X>0){
    for(int i=1;i<=X;i++){
    lcd.setCursor(0,1);
    lcd.print("   mm ");
    lcd.print(i);
    moveStep(0,10,1);  
  }
  }
  if(X<0){
    for(int i=-1;i>=X;i--){
    lcd.setCursor(0,1);
    lcd.print("   mm ");
    lcd.print(i);
    moveStep(0,10,0);  
  }
  }
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Complete X   ");



  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   RUN Y ....   ");
  if(Y>0){
    for(int i=1;i<=Y;i++){
    lcd.setCursor(0,1);
    lcd.print("   mm ");
    lcd.print(i);
    moveStep(1,10,1);  
  }
  }
  if(Y<0){
    for(int i=-1;i>=Y;i--){
    lcd.setCursor(0,1);
    lcd.print("   mm ");
    lcd.print(i);
    moveStep(1,10,0);  
  }
  }
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Complete Y   ");


  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   RUN Z ....   ");
  if(Z>0){
    for(int i=1;i<=Z;i++){
    lcd.setCursor(0,1);
    lcd.print("   mm ");
    lcd.print(i);
    moveStep(2,10,1);  
  }
  }
  if(Z<0){
    for(int i=-1;i>=Z;i--){
    lcd.setCursor(0,1);
    lcd.print("   mm ");
    lcd.print(i);
    moveStep(2,10,0);  
  }
  } 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Complete Z   ");
  delay(500);

  
showDisplay();
  
}

// en 93  back 171 up236 dow 293
void loop()
{
adc = analogRead(sw);
if(adc != buf){

    if(adc == 293){
    index++;
    
    if(index > 3)index = 3;
    showDisplay();
   }else if(adc == 236){
    index--;
    if(index < 0)index = 0;
    showDisplay();
   }
    else if(adc == 93){
  switch(index){
    case 0 : fntSetX();
             break;
    case 1 : fntSetY();
             break;
    case 2 : fntSetZ();
             break;
    case 3 : Run();
             break;
  }
  }

  
 buf = adc;
}
   delay(100);
}
