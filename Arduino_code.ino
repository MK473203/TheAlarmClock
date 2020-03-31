//CODE FOR ARDUINO THAT IS RESPOSIBLE FOR MOVEMENT

#define trigPin 12
#define echoPin 11

char serial[10];

long duration;
int distance;

int enA = 9;
int in1 = 8;
int in2 = 7;

int enB = 3;
int in3 = 5;
int in4 = 4;

void setup() {
  	Serial.begin(9600);
  
  	if (Serial.readBytes(serial, 1) == 1) {
		pinMode(enA, OUTPUT);
		pinMode(enB, OUTPUT);
		pinMode(in1, OUTPUT);
		pinMode(in2, OUTPUT);
		pinMode(in3, OUTPUT);
		pinMode(in4, OUTPUT);
  
  		pinMode(trigPin, OUTPUT);
  		pinMode(echoPin, INPUT);
    }
}

void loop() {

  	analogWrite(enA, 180);
	analogWrite(enB, 180);

	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
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
  
  if (distance < 20) {
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
}
