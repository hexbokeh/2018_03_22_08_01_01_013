#include <MIDI.h>

int ledPin = 33;
int photoPin = A13;

//int lightValue = 160;
//int darkValue = 550;

int lightValue = 1007;
int darkValue = 800;

int lastCellVal;
int cellVal;

int midway;  // threshold value.

bool on;

int ledSignal = A17; //34;

int buttons[2] = {14, 15};
bool buttonState[2];
bool lastButtonState[2];

int currentNote;

int btn = 35;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  //  pinMode(ledSignal, OUTPUT); // I'm going to do this via an analog write.
  //digitalWrite(ledPin, HIGH);
  for (int i = 0; i < 2; i++)
  {
    pinMode(buttons[i], INPUT);
  }
  pinMode(btn, INPUT);
  setMidway();
}

void loop()
{
  //  blinky();
  //  digitalWrite(ledPin, HIGH);
  checkBtn();
  Serial.print("read value = ");
  Serial.println(analogRead(photoPin));
  // calibrateValues();
  newCalibrate();
  checkCell();
//  delay(80);
  delay(10);
}

void checkCell()
{
  lastCellVal = cellVal;
  cellVal = analogRead(photoPin);

  currentNote = map(cellVal, 0, 1023, 30, 60);

  if (cellVal > midway)
  {
    for (int i = 0; i < 128; i++)
    {
      usbMIDI.sendNoteOff(i, 0, 1);
    }
    //on = false;
    Serial.println("Off");
    //digitalWrite(ledSignal, LOW);
    analogWrite(ledSignal, 0);
  }

  //  if (cellVal < midway && lastCellVal > midway && on == false)
  //  else if ((cellVal > midway && lastCellVal < midway ) || (cellVal > midway && cellVal != lastCellVal))

  else if ((cellVal < midway && lastCellVal > midway ) || (cellVal < midway && (cellVal > lastCellVal + 1 || cellVal < lastCellVal - 1))) /// outside a tolerance range
  {
    usbMIDI.sendNoteOn(currentNote, 127, 1);
    //    on = true;
    Serial.println("On");
    Serial.print("MIDI Note: ");
    Serial.println(currentNote);
    //digitalWrite(ledSignal, HIGH);
    analogWrite(ledSignal, map(cellVal, 0, 1023, 50, 0));

    //analogWrite(ledSignal, 2);


    // debug
    Serial.print("analog output: ");
    Serial.println(map(cellVal, 0, 1023, 25, 0));
  }
}

// my test light
void checkBtn()
{
  if (digitalRead(btn))
  {
    digitalWrite(ledPin, LOW); // darkness should increase likelihood of triggering note
  }
  else digitalWrite(ledPin, HIGH); // light should likely turn note off.
}

