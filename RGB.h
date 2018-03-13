#ifndef RGB_h
#define RGB_h

class RGB {
  private:
    int RPin;
    int GPin;
    int BPin;
    int ledInStrob; //what led is burns
    long timeToOneLed;
    long ledWasLightAt;



  public:
    RGB(int inRPin, int inGPin, int inBPin, int frequency) {

      RPin = inRPin;
      pinMode(RPin, OUTPUT);
      digitalWrite(RPin, LOW);

      GPin = inGPin;
      pinMode(GPin, OUTPUT);
      digitalWrite(GPin, LOW);

      BPin = inBPin;
      pinMode(BPin, OUTPUT);
      digitalWrite(BPin, LOW);

      ledInStrob = 0;
      timeToOneLed = 1000 / frequency;
      ledWasLightAt = 0;
    }

    void lightR(boolean state) {
      digitalWrite(RPin, state);
    }

    void lightG(boolean state) {
      digitalWrite(GPin, state);
    }

    void lightB(boolean state) {
      digitalWrite(BPin, state);
    }

    void strobEfect() {
      if (millis() - ledWasLightAt > timeToOneLed) {
        ledWasLightAt = millis();
        if (ledInStrob == 0) {
          digitalWrite(RPin, HIGH);
          digitalWrite(GPin, LOW);
          digitalWrite(BPin, LOW);
          ledInStrob++;
          return;
        }
        if (ledInStrob == 1) {
          digitalWrite(RPin, LOW);
          digitalWrite(GPin, HIGH);
          digitalWrite(BPin, LOW);
          ledInStrob++;
          return;
        }
        if (ledInStrob == 2) {
          digitalWrite(RPin, LOW);
          digitalWrite(GPin, LOW);
          digitalWrite(BPin, HIGH);
          ledInStrob = 0;
          return;
        }
      }
    }

    void colorSwitch() {
      if (ledInStrob == 0) {
        digitalWrite(RPin, HIGH);
        digitalWrite(GPin, LOW);
        digitalWrite(BPin, LOW);
        ledInStrob++;
        return;
      }
      if (ledInStrob == 1) {
        digitalWrite(RPin, LOW);
        digitalWrite(GPin, HIGH);
        digitalWrite(BPin, LOW);
        ledInStrob++;
        return;
      }
      if (ledInStrob == 2) {
        digitalWrite(RPin, LOW);
        digitalWrite(GPin, LOW);
        digitalWrite(BPin, HIGH);
        ledInStrob = 0;
        return;
      }
    }

    void redLedBlinc(long duration, int numberOfTimes) {
      long del = duration / numberOfTimes / 2;
      for (int i = 0; i < numberOfTimes; i++) {
        digitalWrite(RPin, HIGH);
        delay(del);
        digitalWrite(RPin, LOW);
        delay(del);
      }
    }
};

#endif
