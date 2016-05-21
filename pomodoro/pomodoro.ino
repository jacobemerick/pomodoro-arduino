/*
 * Pomodoro, with Arduino
 */

// array of pins that control pomodoro progression
int pomodoroPins[] = {3, 4, 5, 6, 7};

// pin that controls single 'break' pin
int breakPin = 10;

// delay between each interval LED of pomodoro (in seconds)
// note: 5 pins * 5 mins = 25 minute total pomodoro
int pomodoroIntervalTime = 300;

// delay between blink (in seconds)
int pomodoroBlinkTime = 1;

// length of the break (in seconds)
int breakTime = 300;

// pin that controls the buzzer
int buzzPin = 12;

// pomodoro start tune
int pomodoroTune[] = {2637, 2637, 0, 2637, 0, 2093, 2637, 0, 3136, 0, 0, 0, 1568};
int pomodoroTuneLength = 13;
int pomodoroTuneTempo = 12;

// pomodoro complete noise
int breakTune[] = {262, 523, 220, 440, 233, 466};
int breakTuneLength = 6;
int breakTuneTempo = 12;

// break complete noise
int breakEndTune[] = {247, 349, 0, 349, 349, 330, 294, 262, 165, 0, 165, 131};
int breakEndTuneLength = 12;
int breakEndTuneTempo = 10;

// acknowledge button pin
int ackButton = 13;

// sets up pins that are defined above
void setup()
{
  int index;
  for(index = 0; index <= 5; index++)
  {
    pinMode(pomodoroPins[index], OUTPUT);
  }
  pinMode(breakPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(ackButton, INPUT);
}

// loops through pomodoro progression and updates LEDs
void loop()
{
  // play intro at beginning of pomodoro
  playTune(pomodoroTune, pomodoroTuneLength, pomodoroTuneTempo);

  // walk through pomodoro interval indicators
  int index;
  for(index = 0; index < 5; index++)
  {
    blinkLight(pomodoroPins[index], pomodoroBlinkTime, pomodoroIntervalTime);
    digitalWrite(pomodoroPins[index], HIGH);
  }

  // play tune at end of pomodoro, then wait for acknowledgement
  playTune(breakTune, breakTuneLength, breakTuneTempo);
  while(digitalRead(ackButton) != LOW) {}

  // break time
  blinkLight(breakPin, pomodoroBlinkTime, breakTime);
  digitalWrite(breakPin, HIGH);

  // play tune at end of break, then wait for acknowledgement
  playTune(breakEndTune, breakEndTuneLength, breakEndTuneTempo);
  while(digitalRead(ackButton) != LOW) {}

  // clear everything
  digitalWrite(breakPin, LOW);
  for(index = 0; index < 5; index++)
  {
    digitalWrite(pomodoroPins[index], LOW);
  }
}

// convenience function to handle a blink of a passed in LED
void blinkLight(int pin, int blinkLength, int totalBlinkLength) {
  int blinkTimer;
  for (
    blinkTimer = 0;
    blinkTimer < totalBlinkLength;
    blinkTimer += (blinkLength * 2)
  )
  {
    digitalWrite(pin, HIGH);
    delay(blinkLength * 1000);
    digitalWrite(pin, LOW);
    delay(blinkLength * 1000);
  }
}

// convenience function to play a little tune
void playTune(int tune[], int length, int tempo)
{
  int tunePosition;
  int tuneDuration = 1000 / tempo;

  for (
    tunePosition = 0;
    tunePosition < length;
    tunePosition++
  )
  {
    tone(buzzPin, tune[tunePosition], tuneDuration);
    delay(tuneDuration);
    delay(tuneDuration * .6);
  }
}

