#ifndef Button_h
#define Button_h

#include "RGB.h"

class Button {
  private:
    int inPin;  //button pin
    int outPin; //led pin
    Music *music;
    int pressSound;  //number of track
    int lossSound;
    long timeToPress; //in mili seconds
    int clockSound;
    long delayForClockSound;
    boolean strobIsActive;
    RGB *rgb;
    static int buttonCount;



  public:
    Button(int inInPin, int inOutPin, Music *inMusic, int inPressSound, int inLossSound, int inClockSound,long inDelayForClockSound, RGB *inRgb) {
      inPin = inInPin;
      pinMode(inPin, INPUT);

      outPin = inOutPin;
      pinMode(outPin, OUTPUT);
      digitalWrite(outPin, LOW);

      music = inMusic;
      pressSound = inPressSound;
      lossSound = inLossSound;
      clockSound = inClockSound;
      delayForClockSound = inDelayForClockSound;
      strobIsActive = false;
      rgb = inRgb;
    }

    void setTimeToPress(long inTimeToPress) {
      timeToPress = inTimeToPress;
    }

    void start() {
      digitalWrite(outPin, HIGH);
      double Time = millis();
      boolean clockSoundWasStat = false;
      while (millis() - Time < timeToPress) {
        if (!digitalRead(inPin)) { //work on LOW
          digitalWrite(outPin, LOW);
          music->stopMusic();
          music->play(pressSound);
          Serial.print(inPin);
          Serial.println(" - was pressed");
          buttonCount++;
          return;
        }
        if(millis() - Time > delayForClockSound && !clockSoundWasStat) {
          music->stopMusic();
          music->play(clockSound);
          clockSoundWasStat = true;
        }
        if(strobIsActive) {
          rgb->strobEfect();
        }
      }
      digitalWrite(outPin, LOW);
      music->stopMusic();
      music->play(lossSound);
    }

    void start(long delayForClockSound) {
      digitalWrite(outPin, HIGH);
      double Time = millis();
      boolean clockSoundWasStat = false;
      while (millis() - Time < timeToPress) {
        if (!digitalRead(inPin)) { //work on LOW
          digitalWrite(outPin, LOW);
          music->stopMusic();
          music->play(pressSound);
          Serial.print(inPin);
          Serial.println(" - was pressed");
          buttonCount++;
          return;
        }
        if(millis() - Time > delayForClockSound && !clockSoundWasStat) {
          music->stopMusic();
          music->play(clockSound);
          clockSoundWasStat = true;
        }
        if(strobIsActive) {
          rgb->strobEfect();
        }
      }
      digitalWrite(outPin, LOW);
      music->stopMusic();
      music->play(lossSound);
    }
    
    void start(boolean isClockSound) {
      digitalWrite(outPin, HIGH);
      double Time = millis();
      boolean clockSoundWasStat = false;
      while (millis() - Time < timeToPress) {
        if (!digitalRead(inPin)) { //work on LOW
          digitalWrite(outPin, LOW);
          music->stopMusic();
          music->play(pressSound);
          Serial.print(inPin);
          Serial.println(" - was pressed");
          buttonCount++;
          return;
        }
        if(millis() - Time > delayForClockSound && !clockSoundWasStat && isClockSound) {
          music->stopMusic();
          music->play(clockSound);
          clockSoundWasStat = true;
        }
        if(strobIsActive) {
          rgb->strobEfect();
        }
      }
      digitalWrite(outPin, LOW);
      music->stopMusic();
      music->play(lossSound);
    }

    boolean getState() {
      return !digitalRead(inPin);
    }

    void ledBlinc(long duration, int numberOfBlinc) {
      long del = duration / (numberOfBlinc * 2);
      for(int i = 0; i < numberOfBlinc; i++) {
        digitalWrite(outPin, HIGH);
        delay(del);
        digitalWrite(outPin, LOW);
        delay(del);
      }
    }

    void setLedState(boolean newState) {
      digitalWrite(outPin, newState);
    }

    void setStrobIsActive(boolean state) {
      strobIsActive = state;
    }

    static void setButtonCount(int number) {
      buttonCount = number;
    }

    static int getButtonCount() {
      return buttonCount;
    }

};

#endif
