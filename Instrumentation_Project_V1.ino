#include <dht.h>

dht DHT;


const int DHT11_signal = 2;

const int sr04_1_trig = 3;
const int sr04_1_echo = 4;

const int sr04_2_trig = 5;
const int sr04_2_echo = 6;

const int LDR_1 = A0;
const int LDR_2 = A3;

const int Buzzer = 7;
const int Fan = 8;

int* DHT_Function ( const int DHT_pin )
{
  static int DHT_output[2];
  
  int chk = DHT.read11(DHT_pin);
  DHT_output[0] = DHT.humidity;
  DHT_output[1] = DHT.temperature;
  Serial.print("Temperature = ");
  Serial.println(DHT_output[1]);
  Serial.print("Humidity = ");
  Serial.println(DHT_output[0]);
  return DHT_output;
 
}

float sr04_Function(int trigPin, int echoPin){
  static float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  // if(distance < 401)
  // {
    Serial.print("Distance: ");
    Serial.println(distance);
  // }
  return distance;
}

void LDR_Function(int LDR_pin)
{
  if(analogRead(LDR_pin)<512){
    Serial.println("LED OFF");
    // return false;
  }
  else
  {
    Serial.println("LED ON");
    // return true;
  }
}

void setup(){

  pinMode(sr04_1_trig,OUTPUT);
  pinMode(sr04_1_echo,INPUT);
  pinMode(sr04_2_trig,OUTPUT);
  pinMode(sr04_2_echo,INPUT);
  pinMode(Buzzer,OUTPUT);
  pinMode(Fan,OUTPUT);
  
  Serial.begin(9600);
  
}

void loop(){

  float sonic1_out = 0;
  float sonic2_out = 0;
  int dht_out = 0;

  dht_out = DHT_Function(DHT11_signal);
  delay (1000);
  if(dht_out > 20)
  {
    digitalWrite(Fan, HIGH);
  }
  else
  {
    digitalWrite(Fan, LOW);
  }

  Serial.println("first sonic");
  sonic1_out = sr04_Function(sr04_1_trig,sr04_1_echo);
  delay (100);
  Serial.println("second sonic");
  sonic2_out = sr04_Function(sr04_2_trig,sr04_2_echo);
  delay(100);
  if(sonic1_out <= 15 || sonic2_out <= 15)
  {
    digitalWrite(Buzzer, HIGH);
  }
  else
  {
    digitalWrite(Buzzer, LOW);
  }

  Serial.println("First LDR: ");
  LDR_Function(LDR_1);
  delay(100);
  Serial.println("Second LDR: ");
  LDR_Function(LDR_2);
  delay(100);
  
}
