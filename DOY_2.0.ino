int a1 = 5 , a2 = 6  , b1 = 9 , b2 = 10 ;
int bdir = 1;
int mode = 0 ;
int button = 0, k, flag = 0;
long duration , distance ;
int trigPin = 13;
int echoPin = 12;

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 2;      // select the pin for the LED
int sensorValue = 0;
void setup() {
  // put your setup code here, to run once
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin , INPUT);
  pinMode(button , INPUT);

}
int j = 1;
void loop() {
  joy();

  /*  switch (mode) {
      case 0 : basic() ;
        break;
      case 1 : explore();
        break;
      case 2 : scared();
        break;
      case 3 : joy();
        break;
    }
    // explore();
    sensorValue = analogRead(sensorPin);
    if (sensorValue > 900)
      mode = 2;
    else
      mode = 1;*/
  //joy();
}
void basic() {
  int maxd = 20 ;

  while (measureDistance() < maxd) {
    spin(500, bdir);
    delay(50);
  }
  forward(255, 255);
  bdir = (int) random(0, 2);
}


void explore() {
  int maxd = 10 ;

  if (measureDistance() < 10) {
    for (int k = 0 ; k < 4; k++) {
      spin(500, 1) ;
      int tempd = measureDistance();
      delay(50);
      if (tempd > maxd) maxd = tempd ;
    }
  }
  while (measureDistance() <= (maxd - 30)) spin(200, 1);
  forward(255, 255);
}

void scared() {
  int k ;
  int spd = (int) random(0, 200) ;
  k = (int) random(0, 2) ;

  if (measureDistance() < 15) {
    spin(1000, 1) ;
  }
  switch (k) {
    case 0 : for (int i = 0; i < 3; i++)
      { spin(spd, 1);
        spin(spd, 0) ;
      }
      break;
    case 1 : forward(255, 255);
      delay(500);
      break;
  }

}
void joy() {
  int dir = (int) random(0, 2) ;

  if (measureDistance() > 15) {
    int i , j ;
    if(dir == 0) {i =255 ; j= 0;}
    if (dir == 1) { i = 0 ; j = 255;}
    forward(i,j) ;
    delay(500);

  }
  else {
    spin(500 , dir);

  }

}
void spin(int s, int dir) {
  if (dir == 1) {
    digitalWrite(a1, HIGH);
    digitalWrite(a2, LOW);
    digitalWrite(b1, HIGH);
    digitalWrite(b2, LOW);
    delay(s);
    stopme();
  }
  if (dir == 0) {
    digitalWrite(a1, LOW);
    digitalWrite(a2, HIGH);
    digitalWrite(b1, LOW);
    digitalWrite(b2, HIGH);
    delay(s);
    stopme();
  }



}
void forward(int j1 , int j2) {
  analogWrite(a1, LOW);
  digitalWrite(a2, j1);
  digitalWrite(b1, j2);
  analogWrite(b2, LOW);
}
void backward() {
  digitalWrite(a2, HIGH);
  digitalWrite(a1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(b1, HIGH);
}
void stopme() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
}
int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance ;
}




