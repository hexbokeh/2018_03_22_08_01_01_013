void calibrateValues()
{
  if (digitalRead(buttons[0]) == HIGH)
  {
    lightValue = analogRead(photoPin);
    midway = (darkValue + lightValue) / 2;
    Serial.print("new light value =  ");
    Serial.println(lightValue);
  }

  if (digitalRead(buttons[1]) == HIGH)
  {
    darkValue = analogRead(photoPin);
    midway = (darkValue + lightValue) / 2;
    Serial.print("new dark value =  ");
    Serial.println(darkValue);
  }
}
