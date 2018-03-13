#ifndef Statistics_h
#define Statistics_h

#include "Clock.h"

class Statistics {

  private:
    SdFile file;
    char fileName[9];
    Clock *Time;

    void print2digits(int number) {
      //if (number >= 0 && number < 10) {
      //  file.print('0');
      //}
      file.print((char)(number / 10 + 48));
      file.print((char)(number % 10 + 48));
      Serial.println(number);
      Serial.print((char)(number / 10 + 48));
      Serial.println((char)(number % 10 + 48));
    }

  public:
    Statistics() {
      Time = new Clock();
      Time -> getDateFileName(fileName);
      if (!file.open(fileName)) {
        file.close();
        file.open(fileName, O_RDWR | O_CREAT | O_AT_END);
        file.print(";;Action;;Time");
        file.close();
      }
      else
        file.close();
      file.open(fileName, O_RDWR | O_CREAT | O_AT_END);
      file.println();
      file.print(";;Start;;");
      print2digits(Time -> getHour());
      file.print(':');
      print2digits(Time -> getMinute());
      file.print(':');
      print2digits(Time -> getSecond());
      file.close();
    }

    void handControl() {
      file.open(fileName, O_RDWR | O_CREAT | O_AT_END);
      file.println();
      file.print(";;Hand control;;");
      print2digits(Time -> getHour());
      file.print(':');
      print2digits(Time -> getMinute());
      file.print(':');
      print2digits(Time -> getSecond());
      file.close();
  }

  void bolum(int n) {
    int kkCounter = 0;
    int namber = 0;
    int buf;
    file.open(fileName);
    while (file.available()) {
      if (kkCounter != 3) {
        if (file.read() == ';')
          kkCounter++;
        else
          kkCounter = 0;
        if (kkCounter == 3)
          namber = 0;
      }
      else {
        buf = file.read();
        if (buf == '0' || buf == '1' || buf == '2' || buf == '3' || buf == '4'
          || buf == '5' || buf == '6' || buf == '7' || buf == '8' || buf == '9'
          || buf == 13 || buf == 10) {
          if (buf != 13 && buf != 10)
             namber = namber * 10 + (buf - 48);
        }
        else if (buf == ';')
           kkCounter = 1;
        }
      }
      file.close();
      namber++;
      file.open(fileName, O_RDWR | O_CREAT | O_AT_END);
      file.println(";;;");
      file.print(namber);
      file.print(";;baloon ");
      file.print(n);
      file.print(";;");
      print2digits(Time -> getHour());
      file.print(':');
      print2digits(Time -> getMinute());
      file.print(':');
      print2digits(Time ->getSecond());
      file.close();
    }

    Clock* getClock() {
      return Time;
    }
};

#endif
