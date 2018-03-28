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

int ledSignal = 34;

int buttons[2] = {14, 15};
bool buttonState[2];
bool lastButtonState[2];

int currentNote;

int btn = 35;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledSignal, OUTPUT);
  //digitalWrite(ledPin, HIGH);
  for (int i = 0; i < 2; i++)
  {
    pinMode(buttons[i], INPUT);
  }
  pinMode(btn, INPUT);
  midway = (darkValue + lightValue) / 2;
}

void loop()
{
  //  blinky();
  //  digitalWrite(ledPin, HIGH);
  checkBtn();
  Serial.print("read value = ");
  Serial.println(analogRead(photoPin));
  calibrateValues();
  checkCell();
  delay(10);
}

void checkCell()
{
  lastCellVal = cellVal;
  cellVal = analogRead(photoPin);

  currentNote = map(cellVal, darkValue, midway, 30, 60);

  if (cellVal < midway)
  {
    for (int i = 0; i < 128; i++)
    {
      usbMIDI.sendNoteOff(i, 0, 1);
    }
    //on = false;
    Serial.println("Off");
    digitalWrite(ledSignal, LOW);
  }

//  if (cellVal < midway && lastCellVal > midway && on == false)
//  else if ((cellVal > midway && lastCellVal < midway ) || (cellVal > midway && cellVal != lastCellVal))

  else if ((cellVal > midway && lastCellVal < midway ) || (cellVal > midway && (cellVal > lastCellVal+1 || cellVal<lastCellVal-1)))/// outside a tolerance range
  {
    usbMIDI.sendNoteOn(currentNote, 127, 1);
//    on = true;
    Serial.println("On");
    Serial.print("MIDI Note: ");
    Serial.println(currentNote);
    digitalWrite(ledSignal, HIGH);
  }
}

void checkBtn()
{
  if (digitalRead(btn))
  {
    digitalWrite(ledPin, HIGH);
  }
  else digitalWrite(ledPin, LOW);
}

