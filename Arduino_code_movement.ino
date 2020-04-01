//CODE FOR ARDUINO THAT IS RESPOSIBLE FOR MOVEMENT
#define trigPin 12
#define echoPin 11

char serial[1];

long duration;
int distance;
int halytys = 0;

int enA = 8;
int in1 = 2;
int in2 = 3;

int enB = 9;
int in3 = 5;
int in4 = 4;

void setup() {
  	Serial.begin(9600);
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
  	pinMode(10, OUTPUT);
    pinMode(13, INPUT);
  
	pinMode(trigPin, OUTPUT);
  	pinMode(echoPin, INPUT);
}

void loop() {
  
  if(digitalRead(13) == HIGH && halytys == 0) {
  	halytys = 1;
    Serial.println("Alarm on");
  }
  if(digitalRead(13) == LOW && halytys == 1) {
  	halytys = 0;
    Serial.println("Alarm off");
  }
   
  if (halytys == 1){
  	analogWrite(enA, 180);
	analogWrite(enB, 180);

	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  
  	digitalWrite(trigPin, LOW);
  	delayMicroseconds(5);
  
  	digitalWrite(trigPin, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(trigPin, LOW);
  	duration = pulseIn(echoPin, HIGH);
  	distance= duration*0.034/2;
  	Serial.print("Distance = ");
  	Serial.print(distance);
  	Serial.println(" cm");
  
  	delay(50);
    
    tone(10, 330);
  
  	if (distance < 50) {
    digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
    
    delay(500);
    
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	delay(500);
    }
  } else if(halytys == 0) {
    digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  }
}
