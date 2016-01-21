/* Sketch to collect and process ultrasonic reads from HC-SR04.
*  Author: jmckiernan
*  Last modified: 16 November 2015
*  Last modified by: jmckiernan, plertvilai
*/

const int trigPin=4;
const int echoPin=5;

void setup(){
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); //a pin is INPUT by default, so this line is actually unnecesary
}

// Two Helper Functions 

/* sends an ultrasonic pulse out, measures how long the pulse travels, calculates the 
* distance the pulse traveled, and returns the distance.
* Code mostly taken from usonicTest_29OCT2015.
*/

float getOneVal(){
  
  float duration;
  float distance;
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2.0)/29.1;
  return distance;
}

/* Gets five reads in the expected range and returns the average value
*/ 
float getStableRead()
{
  float sum=0;
  float tempVal;
  int cond;
   for(int i=0;i<5;i++)
  {
    cond=1;
    while(cond){
      tempVal = getOneVal();
      //Serial.println(tempVal); // for debugging
      if(2<tempVal && tempVal<400) cond = 0; 
      delay(1); //wait 1 ms before getting the next data point
    } 
    Serial.println(tempVal);
    //Serial.println(" < good val"); // also for debugging
    sum+=tempVal;
  } 
  return sum/5.0; //return the average of 5 values
}



void loop(){

  float stableRead = getStableRead();
  Serial.print(stableRead);
  Serial.println(" cm");
  delay(2000); //waiting for 2 seconds so it's a little easier to record 
  }

// Possible benchmarks: 
//how long does it take to get a stable read? 
//How accurate is the stable read?
// how variable in time is the stable read? (i.e. is it better right after device is turned on?

