//CODE OF THE ARDUINO RESPOSIBLE FOR CLOCK FUNCTIONALITY

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int plusButton = 10;
const int modeButton = 9;
const int minusButton = 8;
int plusButtonState = 0;
int modeButtonState = 0;
int minusButtonState = 0;

int mode = 0;	// 0 for normal clock,
				// 1 for changing hours, 
				// 2 for minutes,
				// 3 for enabling/disabling alarm,
				// 4 for setting alarm time.

const int timeScale = 180; 	// for testing purposes, 
				// this controls the speed of how fast time is moving.
				// set it to 1 for real time time.

//intialize time etc. when powered up
int minutesSinceStart = 0;
int hoursSinceStart = 0;

int startMinutes = 0;
int startHours = 0;

int alarmMinutes = 00;
int alarmHours = 8;

bool useAlarm = false;

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
  
  //if plusButton is pressed, depending of the mode of the clock either nothing happens or hours/minutes/alarm time is advanced
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
      	useAlarm = true;
      	mode = 4;
      	break;
      case 4:
      	alarmMinutes = alarmMinutes + 1;
      	if(alarmMinutes >= 60) {
        	alarmHours = (alarmHours + 1) % 24;
        	alarmMinutes = 0;
      	}
      	break;
    }
  }
  
  //if modeButton (midlle one) is pressed, mode of the clock changes see meanings of different values 0-5 above
  if(modeButtonState == HIGH) {
    mode = min(mode + 1, 4) % 4;
  }
  
  //if minusButton is pressed, depending of the mode of the clock either nothing happens or hours/minutes/alarm time is decreased
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
      	useAlarm = false;
      	mode = 0;
      	break;
      case 4:
      	alarmMinutes = alarmMinutes - 1;
      	if(alarmMinutes < 0) {
      		alarmHours = alarmHours - 1;
      		if(alarmHours < 0) alarmHours = 23;
        	alarmMinutes = 59;
      	}
      	break;
    }
  }
  
  //Text to be printed on screen for different modes
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
      	lcd.print("   Use alarm?   ");
      	lcd.setCursor(0,1);
      	lcd.print("No           Yes");
      	break;
    case 4:
      	lcd.setCursor(0,0);
      	lcd.print("Set alarm       ");
      	break;
    }
  
  //count passed time since powering up
  minutesSinceStart = millis() * timeScale / 60000;
  hoursSinceStart = (startMinutes + minutesSinceStart) / 60;
  
  if(useAlarm) {
  	//if alarm triggers, send signal to other arduino
    if((startHours+hoursSinceStart) % 24 == alarmHours && (startMinutes+minutesSinceStart) % 60 == alarmMinutes && isAlarming == false) {
      digitalWrite(13, HIGH);
      isAlarming = true;
    }
  	//if alarm is disabled by pressing any button, make other arduino stop what it's doing
    if(plusButtonState == HIGH || modeButtonState == HIGH || minusButtonState == HIGH) {
      digitalWrite(13, LOW);
      isAlarming = false;
    }
    
  }
  
  //Values to be printed on screen in different modes
  lcd.setCursor(0, 1);
  
  if(mode <= 2) {
  	sprintf(timeText, "%02d:%02d           ", 
           (startHours+hoursSinceStart) % 24,
           (startMinutes+minutesSinceStart) % 60);
  	lcd.print(timeText);
  } else if (mode == 4) {
  	sprintf(timeText, "%02d:%02d           ", 
            alarmHours,
            alarmMinutes);
  	lcd.print(timeText);
  }
  
  delay(50);
}
