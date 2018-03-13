#ifndef Motor_h
#define Motor_h

class Motor {
  private:
    int runPin;
    int reversePin;
    int stopPin;
    long delayForControl;  //час який потрібний щоб частотний перетворювач відреагував
    boolean rotationDirection;
    int speedPin;

    void directDirection() {
      digitalWrite(stopPin, LOW);
      digitalWrite(reversePin, LOW);
      
      digitalWrite(runPin, HIGH);
      delay(delayForControl);
      digitalWrite(runPin, LOW);
    }

    void reversDirection() {
      digitalWrite(runPin, LOW);
      digitalWrite(stopPin, LOW);
      
      digitalWrite(reversePin, HIGH);
      delay(delayForControl);
      digitalWrite(reversePin, LOW);
    }


  public:
    Motor(int inRunPin, int inReversePin, int inSpeedPin, int inStopPin, long inDelayForControl, boolean inRotationDirection) {
      
      runPin = inRunPin;
      pinMode(runPin, OUTPUT);
      digitalWrite(runPin, LOW);

      reversePin = inReversePin;
      pinMode(reversePin, OUTPUT);
      digitalWrite(reversePin, LOW);

      speedPin = inSpeedPin;
      pinMode(speedPin, OUTPUT);
      digitalWrite(speedPin, LOW);

      stopPin = inStopPin;
      pinMode(stopPin, OUTPUT);
      digitalWrite(stopPin, LOW);

      delayForControl = inDelayForControl;
      rotationDirection = inRotationDirection;
    }

    void startMotor() {
      if(rotationDirection) {
        directDirection();
      }
      else {
        reversDirection();
      }
    }

    void invertDirection() {
      rotationDirection = !rotationDirection;
    }

    void stopMotor() {
      digitalWrite(runPin, LOW);
      digitalWrite(reversePin, LOW);
      
      digitalWrite(stopPin, HIGH);
      delay(delayForControl);
      digitalWrite(stopPin, LOW);
    }

    void setMotorSpeed(int newSpeed) {
      analogWrite(speedPin, newSpeed);
      Serial.print("speed pin = ");
      Serial.println(speedPin);
      Serial.print("new motor speed = ");
      Serial.println(newSpeed);
    }

};

#endif
