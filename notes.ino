//// hard-coded midppoint
//
//int mid = 570;
//
//int photoState;
//int lastPhotoState;
//
//int led = 2;
//
//void setup()
//{
//  Serial.begin(9600);
//  pinMode(led, OUTPUT);
//  
//}
//
//void loop()
//{
//  checkNote();
//}
//
//void checkNote()
//{
//  lastPhotoState = photoState;
//  photoState = analogRead(photocell);
//
//  // if I press a button and previously, I was not pressing a button……
//  // we are looking for a change in states.
//
//  if (photoState < mid && lastPhotoState > mid)
//  {
//    usbMIDI.sendNoteOn(60, 127, 1);
//    digitalWrite(led, HIGH);
//  }
//
//  if (photoState > mid && lastPhotoState < mid)
//  {
//    usbMIDI.sendNoteOff(60, 0, 1);
//    digitalWrite(led, LOW);
//  }
//  
//}

