#ifndef Vortix
#define Vortix

#include <SdFat.h>
#include <SdFatUtil.h>

SdFat sd;

#include "FileWorkerFat.h"
#include "Music.h"
#include "Button.h"
#include "Statistics.h"
#include "Sekyurotron.h"
#include "Motor.h"
#include "MusicUART.h"

void(* resetFunc) (void) = 0;

boolean endSpeechWasStarted = false;
int Button::buttonCount;

void setup() {

  long delayForClockSound = 3000; //delay before closk sound started
  int startButton = 30;
  long timeToPress = 10000;
  long timeToInstruction1Sound = 12000;
  long timeToInstruction2Sound = 7000;
  long timeToInstruction3Sound = 9000;
  long timeToInstruction4Sound = 15000;
  long timeForLooseSound = 5000;
  long ledBlincTime = 2000;
  int strobFrequency = 20;  //blincs per seconds
  int speed1 = 76;
  int speed2 = 153;
  int speed3 = 255;
  int16_t standartUARTMusicVolume = 0X1E;
  int16_t quietUARTMusicVolume = 0X0F;
  long TimeForEndSpeech = 7000;
  long durationOfEndOfEndSpeech = 4000;
  long timeForEndEndSpeesh = 7000;

  Serial.begin(9600); //9600 - bod per seconds

  if (!sd.begin(9, SPI_HALF_SPEED)) { //9 - CS
    Serial.println("SD ERROR");
    resetFunc();
  }
  Serial.println("SD OK");

  FileWorkerFat *fileWorker = new FileWorkerFat();

  long gameTime = 180000;
  if (fileWorker->openFileForRead("config.txt")) {
    Serial.println("File \"config.txt\" was open");
    gameTime = fileWorker->getNextNumber();
  } else {
    Serial.println("File \"config.txt\" was not open - ERROR!!!");
  }
  fileWorker->closeFile();

  Serial.print("gameTime = ");
  Serial.println(gameTime);

  Statistics *statistic = new Statistics();

  Music *music = new Music();
  music -> setVolume(1);  //max volume

  pinMode(startButton, INPUT);

  Sekyurotron *sekyurotron = new Sekyurotron();

  RGB *rgb = new RGB(23, 25, 27, strobFrequency);

  Button *button1 = new Button(46, 47, music, 1, 4, 2, delayForClockSound, rgb);
  Button *button2 = new Button(44, 45, music, 1, 4, 2, delayForClockSound, rgb);
  Button *button3 = new Button(42, 43, music, 1, 4, 2, delayForClockSound, rgb);
  Button *button4 = new Button(40, 41, music, 1, 4, 2, delayForClockSound, rgb);
  Button *button5 = new Button(38, 39, music, 1, 4, 2, delayForClockSound, rgb);
  Button *button6 = new Button(36, 37, music, 1, 4, 2, delayForClockSound, rgb);
  Button *button7 = new Button(34, 35, music, 1, 4, 2, delayForClockSound, rgb);
  Button *button8 = new Button(32, 33, music, 1, 4, 2, delayForClockSound, rgb);

  Serial.print("button1 = ");
  Serial.println(button1 -> getState());
  Serial.print("button2 = ");
  Serial.println(button2 -> getState());
  Serial.print("button3 = ");
  Serial.println(button3 -> getState());
  Serial.print("button4 = ");
  Serial.println(button4 -> getState());
  Serial.print("button5 = ");
  Serial.println(button5 -> getState());
  Serial.print("button6 = ");
  Serial.println(button6 -> getState());
  Serial.print("button7 = ");
  Serial.println(button7 -> getState());
  Serial.print("button8 = ");
  Serial.println(button8 -> getState());

  int numberOfButtons = 8;

  Button **buttons = new Button *[numberOfButtons + 1]; //ібо ТЗ міняється із швидкістю світла

  Motor *motor1 = new Motor(A8, A9, 10, A10, 20, true);
  Motor *motor2 = new Motor(A11, A12, 10, A13, 20, true);

  Clock *Time = statistic->getClock();
  Serial.print("Month - ");
  Serial.println(Time->getMonth());

  int instruction1Sound = 3;
  int instruction2Sound = 5;
  int instruction3Sound = 6;
  int instruction4Sound = 7;
  int instruction5Sound = 8;

  Serial.println("UART music initialisation");
  MusicUART *musicUART = new MusicUART();
  Serial.println("while (true)");

  while (true) {

    music -> stopMusic();

    Serial.println("RGB - all LOW");
    rgb->lightR(false);
    rgb->lightG(false);
    rgb->lightB(false);

    motor1->stopMotor();
    motor2->stopMotor();

    motor1->setMotorSpeed(0);
    motor2->setMotorSpeed(0);

    button1->setStrobIsActive(false);
    button2->setStrobIsActive(false);
    button3->setStrobIsActive(false);
    button4->setStrobIsActive(false);
    button5->setStrobIsActive(false);
    button6->setStrobIsActive(false);
    button7->setStrobIsActive(false);
    button8->setStrobIsActive(false);

    Serial.println("while (digitalRead(startButton));");
    while (digitalRead(startButton));
    Serial.println("Start button was pressed");
    //не пізніше березня
    if ((sekyurotron -> getTimerState() || sekyurotron -> getFileIndexState()) && (sekyurotron -> getFileIndexState() || Time->getMonth() <= 3)) {

      long startTime = millis();

      musicUART->stopMusic();

      sekyurotron -> decrementTimer();

      statistic -> handControl();

      motor1->setMotorSpeed(speed1);
      motor2->setMotorSpeed(speed1);

      Button::setButtonCount(0);
      checkEndCount(startTime, gameTime - TimeForEndSpeech, musicUART);
      if (millis() - startTime < gameTime) {
        motor1->startMotor();
        motor2->startMotor();

        rgb->lightB(true);

        music -> play(instruction1Sound); //play instruction 1

        buttons[0] = button1;
        buttons[1] = button2;
        buttons[2] = button3;
        buttons[3] = button4;
        buttons[4] = button5;
        buttons[5] = button6;
        buttons[6] = button7;
        buttons[7] = button8;

        ledsBlinc(ledBlincTime, buttons, numberOfButtons, 2);
        musicUART->setVolume(standartUARTMusicVolume);
        musicUART->startDirectoryOne();

        for (int i = 0; i < numberOfButtons; i++) {
          buttons[i]->setLedState(true);
        }
      }

      Serial.println("first level");
      //------------------------------ first level

      for (int i = 0; i < numberOfButtons; i++) {
        checkEndCount(startTime, gameTime - TimeForEndSpeech, musicUART);
        if (millis() - startTime < gameTime) {
          Serial.print("Button #");
          Serial.print(i);
          Serial.println(" is activated");
          buttons[i] -> setTimeToPress(timeToPress);
          buttons[i] -> start(false);
        }
      }

      Serial.println("Oposit direction");
      //-------------------------------------- Oposit direction

      music -> stopMusic();
      checkEndCount(startTime, gameTime - TimeForEndSpeech, musicUART);
      if (millis() - startTime < gameTime) {

        musicUART->setVolume(quietUARTMusicVolume);

        music -> play(instruction2Sound); //play instruction 2

        motor1->setMotorSpeed(speed2);
        motor2->setMotorSpeed(speed2);

        rgb->lightB(false);
        rgb->lightR(true);

        buttons[0] = button7;
        buttons[1] = button6;
        buttons[2] = button5;
        buttons[3] = button4;
        buttons[4] = button3;
        buttons[5] = button2;
        buttons[6] = button1;

        ledsBlinc(ledBlincTime, buttons, numberOfButtons - 1, 2);

        musicUART->setVolume(standartUARTMusicVolume);

        for (int i = 0; i < numberOfButtons - 1; i++) {
          buttons[i]->setLedState(true);
        }
      }

      for (int i = 1; i < numberOfButtons - 1; i++) {
        checkEndCount(startTime, gameTime - TimeForEndSpeech, musicUART);
        if (millis() - startTime < gameTime) {
          Serial.print("Button #");
          Serial.print(i);
          Serial.println(" is activated");
          buttons[i] -> setTimeToPress(timeToPress);
          buttons[i] -> start(false);
          if (i == (numberOfButtons - 2) / 2) {
            rgb->lightR(false);
            rgb->lightG(true);
          }
        }
      }

      Serial.println("Second level");
      //--------------------------------- second level
      checkEndCount(startTime, gameTime - TimeForEndSpeech, musicUART);
      if (millis() - startTime < gameTime) {
        musicUART->setVolume(quietUARTMusicVolume);
        music -> play(instruction3Sound); //play instruction 3
        rgb->lightG(false);
        rgb->lightB(true);
        delay(timeToInstruction3Sound);
        musicUART->setVolume(standartUARTMusicVolume);
      }

      buttons[0] = button4;
      buttons[1] = button8;
      buttons[2] = button3;
      buttons[3] = button1;
      buttons[4] = button5;
      buttons[5] = button7;

      for (int i = 0; i < numberOfButtons - 2; i++) {
        checkEndCount(startTime, gameTime - TimeForEndSpeech, musicUART);
        if (millis() - startTime < gameTime) {
          Serial.print("Button #");
          Serial.print(i);
          Serial.println(" is activated");
          buttons[i] -> setTimeToPress(timeToPress / 3 * 2);
          buttons[i] -> start();
          rgb->colorSwitch();
          if (i == numberOfButtons - 5) {
            motor1->stopMotor();
            motor2->stopMotor();
          }
        }
      }

      Serial.println("third level");
      //--------------------------------- third level

      motor1->setMotorSpeed(speed3);
      motor2->setMotorSpeed(speed3);
      motor1->invertDirection();
      checkEndCount(startTime, gameTime - TimeForEndSpeech, musicUART);
      if (millis() - startTime < gameTime) {
        musicUART->setVolume(quietUARTMusicVolume);
        musicUART->startDirectoryTwo();
        music -> play(instruction4Sound); //play instruction 4
        motor1->startMotor();
        motor2->startMotor();

        rgb->lightR(false);
        rgb->lightG(false);
        rgb->lightB(false);
        rgb->redLedBlinc(timeToInstruction4Sound, 30);
        musicUART->setVolume(standartUARTMusicVolume);
      }

      buttons[0] = button2;
      buttons[1] = button8;
      buttons[2] = button5;
      buttons[3] = button8;
      buttons[4] = button1;
      buttons[5] = button4;
      buttons[6] = button1;
      buttons[7] = button2;
      buttons[8] = button7;

      while (millis() - startTime < gameTime) {
        for (int i = 0; i < numberOfButtons; i++) {
          checkEndCount(startTime, gameTime - TimeForEndSpeech, musicUART);
          if (millis() - startTime < gameTime) {
            Serial.print("Button #");
            Serial.print(i);
            Serial.println(" is activated");
            buttons[i]->setStrobIsActive(true);
            buttons[i] -> setTimeToPress(timeToPress / 3);
            buttons[i] -> start();
          }
        }
      }
      motor2->invertDirection();
      motor1->stopMotor();
      motor2->stopMotor();
      delay(durationOfEndOfEndSpeech);
      music -> play(instruction5Sound);
      delay(timeForEndEndSpeesh);
    }
  }
}

void ledsBlinc(long duration, Button **buttons, int numberOfLeds, int numberOfBlinc) {
  long del = duration / (numberOfLeds * numberOfBlinc);
  for (int i = 0; i < numberOfBlinc; i++) {
    for (int j = 0; j < numberOfLeds; j++) {
      buttons[j]->setLedState(true);
      delay(del);
      buttons[j]->setLedState(false);
    }
  }
}

void checkEndCount(long startTime, long duration, MusicUART *musicUART) {
  if (!endSpeechWasStarted) {
    if (millis() - startTime >= duration) {
      if (Button::getButtonCount() < 30) {
        musicUART->startAudio1();
        endSpeechWasStarted = true;
        return;
      }
      if (Button::getButtonCount() < 50) {
        musicUART->startAudio2();
        endSpeechWasStarted = true;
        return;
      }
      musicUART->startAudio3();
      endSpeechWasStarted = true;
      return;
    }
  }
}

void loop() {

}

#endif
