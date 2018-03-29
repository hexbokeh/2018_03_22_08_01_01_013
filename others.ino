// test function.
void blinky()
{
  if (millis()%100 == 0)
  {
    digitalWrite(ledPin, HIGH);
    //Serial.println("blinking");
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}
