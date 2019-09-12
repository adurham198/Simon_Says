//Anton Durham
//CIS-268
//Desc: This program is designed to emulate the game simon says
//4/18/2019
#include <LiquidCrystal.h>
int buttonpin[] = {A0, A1, A2, A3};
int ledpin[] = {6,7,8,9};
LiquidCrystal lcd(12,11,5,4,3,2);
int currscore = 0;
int highscore = 0;
int turn = 0;
int b1 = LOW;
int b2 = LOW;
int b3 = LOW;
int b4 = LOW;
int resetb = A4;
int buzzer = 10;
int reset = LOW;
bool gameover = false;
int seqarr[50]; 
int playerarrseq[50];

void setup() 
{

 Serial.begin(9600); 

 pinMode(ledpin[0], OUTPUT);
 pinMode(ledpin[1], OUTPUT);
 pinMode(ledpin[2], OUTPUT);
 pinMode(ledpin[3], OUTPUT);
 pinMode(b1, INPUT);
 pinMode(b2, INPUT);
 pinMode(b3, INPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(b4, INPUT);
 display();
 randomSeed(analogRead(0)); 
//used analogRead to seed the randomSeed function with the seqarr for simonturn() function
//randomSeed also uses a disconnected pin so the returned "random" number is relatively random


  }
  
void simonturn()
 { 
//function for making the pins light up at random
   
  for (int i=turn; i <= turn; i++){ 

   seqarr[i] = random(1, 5); // Find a random number in 1 and 5 range
   for (int j=0; j <= turn; j++){ 

     Serial.print(seqarr[j]);
      
     if (seqarr[j] == 1) { 
        
       digitalWrite(ledpin[0], HIGH);
       music(300,14000);
       delay(200);
       digitalWrite(ledpin[0], LOW);
       delay(200);
     }

     if (seqarr[j] == 2) {        
       digitalWrite(ledpin[1], HIGH);
       music(300,9000);
       delay(200);
       digitalWrite(ledpin[1], LOW);
       delay(200);
     }

     if (seqarr[j] == 3) {     
       digitalWrite(ledpin[2], HIGH);
        music(300,6000);
       delay(200);
       digitalWrite(ledpin[2], LOW);
       delay(200);
     }

     if (seqarr[j] == 4) {
       digitalWrite(ledpin[3], HIGH);
       music(300,3500);
       delay(200);
       digitalWrite(ledpin[3], LOW);
       delay(200);
     }
    }
   }
  }
 
 
 
void playerturn()
 { 
//Function for allowing user input and checking input against the generated array

 for (int j=0; j <= turn;){ 
 //Statement controlled by turn count
   b1 = digitalRead(buttonpin[0]);
   b2 = digitalRead(buttonpin[1]);
   b3 = digitalRead(buttonpin[2]);
   b4 = digitalRead(buttonpin[3]);
    reset = digitalRead(resetb);
   if (b1 == HIGH){ 
   //when a button is pressed
     digitalWrite(ledpin[0], HIGH);
      music(200, 9700);
     delay(200);
     digitalWrite(ledpin[0], LOW);
     playerarrseq[j] = 1;
     delay(50);
     
     if (playerarrseq[j] != seqarr[j]) { 
                      //Checks the player's button press
       flash();        //compared to the sequence array
     } 
                      //player loses if their button press did not match simon's sequence
      
     j++;
   }

   if (b2 == HIGH){
     digitalWrite(ledpin[1], HIGH);
      music(200,14000);
     delay(200);
     digitalWrite(ledpin[1], LOW);
     playerarrseq[j] = 2;
     delay(50);
     Serial.print(2);
     if (playerarrseq[j] != seqarr[j]) {
       flash();
     }
    
     j++;

   }

   if (b3 == HIGH){
     digitalWrite(ledpin[2], HIGH);
     music(200,8500);
     delay(200);
     digitalWrite(ledpin[2], LOW);
     playerarrseq[j] = 3;
     delay(50);
     Serial.print(3);
     if (playerarrseq[j] != seqarr[j]) {
       flash();
     }
     
     j++;
   }

   if (b4 == HIGH){
     digitalWrite(ledpin[3], HIGH);
     music(200,11000);
     delay(200);
     digitalWrite(ledpin[3], LOW);
     playerarrseq[j] = 4;
     delay(50);
     Serial.print(4);
     if (playerarrseq[j] != seqarr[j]) {
       flash();
     }
      
     j++;

   }
  }

 if(highscore == currscore)
 {
 highscore++;
 }
 currscore++;
 display();
 delay(500);
 turn++; 
 
}

void flash() 
{
//Flash when the player loses the game
  
 for (int j=0; j<=5; j++){ 
  digitalWrite(ledpin[0], HIGH);
  digitalWrite(ledpin[1], HIGH);
  digitalWrite(ledpin[2], HIGH);
  digitalWrite(ledpin[3], HIGH);
  delay(300);
  digitalWrite(ledpin[0], LOW);
  digitalWrite(ledpin[1], LOW);
  digitalWrite(ledpin[2], LOW);
  digitalWrite(ledpin[3], LOW);
  delay(300);
 }
 
 delay(500);
// highscore = (highscore - 1);
 currscore = -1;
  turn = -1;

}
void display()
{
 
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("High Score:");
  lcd.setCursor(11, 0);
  lcd.print(highscore);
  lcd.setCursor(0,1);
  lcd.print("Curr Score:");
  lcd.setCursor(11,1);
  lcd.print(currscore);
  
}
void music(int moana, int slength)
{
  tone(buzzer, slength);
  delay(moana);
  noTone(buzzer);
  delay(moana);

}
void loop() { 
  for(int i = 0; i <=1000; i++)
  {
    simonturn();
  Serial.println("looping");
  playerturn();
  }
}
