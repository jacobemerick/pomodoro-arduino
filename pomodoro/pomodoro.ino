/*
 * Pomodoro, with Arduino
 */

// array of pins that control pomodoro progression
int pomodoroPins[] = {3, 4, 5, 6, 7};

// pin that controls single 'break' pin
int breakPin = 10;

// delay between each interval LED of pomodoro (in microseconds)
// note: 5 pins * 5 mins = 25 minute total pomodoro
int pomodoroPinDelayTime = 5000;

// delay between blink
int pomodoroPinBlinkTime = 500;

// pin that controls the buzzer
int buzzPin = 12;

// temp var - may want to customize per tune
int tuneDuration = 100;

// pomodoro complete tune
int pomodoroTune[] = {2637, 2637, 0, 2637, 0, 2093, 2637, 0, 3136, 0, 0, 0, 1568};
int pomodoroTuneLength = 13;
int pomodoroTuneTempo = 12;

// rest complete noise
int breakTune[] = {262, 523, 220, 440, 233, 466};
int breakTuneLength = 6;
int breakTuneTempo = 12;

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
}

// loops through pomodoro progression and updates LEDs
void loop()
{
  // walk through pomodoro interval indicators
  int index;
  for(index = 0; index < 5; index++)
  {
    blinkLight(pomodoroPins[index], pomodoroPinBlinkTime, pomodoroPinDelayTime);
    digitalWrite(pomodoroPins[index], HIGH);
  }

  playTune(pomodoroTune, pomodoroTuneLength, pomodoroTuneTempo);

  // todo wait for acknowledgement

  // break time
  blinkLight(breakPin, pomodoroPinBlinkTime, pomodoroPinDelayTime);
  digitalWrite(breakPin, HIGH);

  playTune(breakTune, breakTuneLength, breakTuneTempo);

  // todo wait for acknowledgement

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
    delay(blinkLength);
    digitalWrite(pin, LOW);
    delay(blinkLength);
  }
}

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

