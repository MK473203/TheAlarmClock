//CODE OF THE ARDUINO RESPOSIBLE FOR CLOCK FUNCTIONALITY

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins and intialize all other necessary pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int plusButton = 10;
const int modeButton = 9;
const int minusButton = 8;
int plusButtonState = 0;
int modeButtonState = 0;
int minusButtonState = 0;

int mode = 0;			// 0 for normal clock,
				// 1 for changing hours, 
				// 2 for minutes,
				// 3 for setting alarm time,
				// 4 for enabling/disabling alarm.

const int timeScale = 100; // for testing purposes, this controls the speed of 

int minutesSinceStart = 0;
int hoursSinceStart = 0;

int startMinutes = 55;
int startHours = 23;

int alarmMinutes = 0;
int alarmHours = 0;

bool useAlarm = true;

bool isAlarming = false;

char timeText[10];

void setup() {
	  Serial.begin(9600);
  
  	pinMode(plusButton, INPUT);
  	pinMode(modeButton, INPUT);
  	pinMode(minusButton, INPUT);
  	pinMode(13, OUTPUT);
  	lcd.begin(16, 2);
  	lcd.print("Time:");
}

void loop() {
  
  	plusButtonState = digitalRead(plusButton);
  	modeButtonState = digitalRead(modeButton);
  	minusButtonState = digitalRead(minusButton);
  
	

  	if(plusButtonState == HIGH) {
    		switch (mode) {
      		case 0:
      			break;
      		case 1:
      			startHours = (startHours + 1) % 24;
      			break;
      		case 2:
      			startMinutes = (startMinutes + 1) % 60;
      			break;
      		case 3:
      			alarmMinutes = alarmMinutes + 1;
      			if(alarmMinutes >= 60) {
        		alarmHours = (alarmHours + 1) % 24;
        		alarmMinutes = 0;
      			}
      			break;
      		case 4:
      			useAlarm = true;
      			mode = 0;
      			break;
    		}
  	}
  
	if(modeButtonState == HIGH) {
    		mode = (mode + 1) % 5;
  	}
	
  	if(minusButtonState == HIGH) {
    		switch (mode) {
      		case 0:
      			break;
      		case 1:
      			startHours = startHours - 1;
      			if(startHours < 0) startHours = 23;
      			break;
      		case 2:
      			startMinutes = startMinutes - 1;
      			if(startMinutes < 0) startMinutes = 59;
      			break;
      		case 3:
      			alarmMinutes = alarmMinutes - 1;
      			if(alarmMinutes < 0) {
      			alarmHours = alarmHours - 1;
      			if(alarmHours < 0) alarmHours = 23;
        		alarmMinutes = 59;
      			}
      			break;
      		case 4:
      			useAlarm = false;
      			mode = 0;
      			break;
    		}	
 	}
  
	switch (mode) {
  		case 0:
  			lcd.setCursor(0,0);
      			lcd.print("Time:           ");
      			break;
    		case 1:
      			lcd.setCursor(0,0);
      			lcd.print("Set hours       ");
      			break;
    		case 2:
      			lcd.setCursor(0,0);
      			lcd.print("Set minutes     ");
      			break;
    		case 3:
      			lcd.setCursor(0,0);
      			lcd.print("Set alarm       ");
      			break;
    		case 4:
      			lcd.setCursor(0,0);
      			lcd.print("   Use alarm?   ");
      			lcd.setCursor(0,1);
      			lcd.print("No           Yes");
      			break;
    	}
  
  
  	minutesSinceStart = millis() * timeScale / 60000;
  	hoursSinceStart = (startMinutes + minutesSinceStart) / 60;
  
  	if(useAlarm) {
  
    		if((startHours+hoursSinceStart) % 24 == alarmHours && (startMinutes+minutesSinceStart) % 60 == alarmMinutes && isAlarming == false) {
      		digitalWrite(13, HIGH);
      		isAlarming = true;
    	}
  
    	if(plusButtonState == HIGH || modeButtonState == HIGH || minusButtonState == HIGH) {
      		digitalWrite(13, LOW);
      		isAlarming = false;
    	}	
    
  	}
  
  	lcd.setCursor(0, 1);
  
  	if(mode <= 2) {
  		sprintf(timeText, "%02d:%02d           ", 
           	(startHours+hoursSinceStart) % 24,
           	(startMinutes+minutesSinceStart) % 60);
  		lcd.print(timeText);
  		} 
	else if (mode == 3) {
  		sprintf(timeText, "%02d:%02d           ", 
            	alarmHours,
            	alarmMinutes);
  		lcd.print(timeText);
  	}
  
  	delay(50);
}
