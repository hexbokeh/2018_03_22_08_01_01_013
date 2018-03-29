void calibrateValues()
{
  if (digitalRead(buttons[0]) == HIGH)
  {
    lightValue = analogRead(photoPin);
    setMidway();
    Serial.print("new light value =  ");
    Serial.println(lightValue);
  }

  if (digitalRead(buttons[1]) == HIGH)
  {
    darkValue = analogRead(photoPin);
    setMidway();
    Serial.print("new dark value =  ");
    Serial.println(darkValue);
  }
}

// bonus: use just one button to establish light and dark extremes.
// it will be the user's job to adjust the light values accordingly.
void newCalibrate()
{
  // either button from before can be used; now they're performing the same function.
  while (digitalRead(buttons[0]) || digitalRead(buttons[1])) // perhaps this could be an if statement instead.
  {
    int temp = analogRead(photoPin);
    // light yields a higher analog value; darkness yields a lower analog value.
    if (temp > lightValue)
    {
      lightValue = temp;
      setMidway();
    }
    if (temp < darkValue)
    {
      darkValue = temp;
      setMidway();
    }
  }
}

// just to clear things up in the other functions.
void setMidway()
{
  midway = (darkValue + lightValue) / 2;
}

