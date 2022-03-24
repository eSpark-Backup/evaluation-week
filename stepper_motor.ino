/* Author Kamran Asif
 * Date: 25/3/22
 * Description: Controlling Stepper Motor
 */

// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 2000;
int stepDelay=3000;

void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop()
{
  //Motor spiining in clockwise
  digitalWrite(dirPin, HIGH);
  
  // Motor Spinning Loop
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  delay(2000); // Wait 2 seconds
  
  //counterclockwise
  digitalWrite(dirPin, LOW);
  
  // Motor Spinning Loop
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  
  delay(2000); // Wait 2 seconds
}
