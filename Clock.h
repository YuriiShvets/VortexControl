#ifndef Clock_h
#define Clock_h

#include <DS1307RTC.h>
#include <Time.h>

class Clock {

  private:
    SdFile file;


    void SetTime() {               //������� ��� �� ����� ���'�� ��� �� �����

      tmElements_t tm;
      if (file.open("time.txt")) { //���� � ����
        char SYear[4];
        char SMonth[2];
        char SDay[2];
        char SHour[2];
        char SMin[2];
        char SSec[2];

        //������ ��� �� �����
        SYear[0] = file.read();
        SYear[1] = file.read();
        SYear[2] = file.read();
        SYear[3] = file.read();
        file.read();
        SMonth[0] = file.read();
        SMonth[1] = file.read();
        file.read();
        SDay[0] = file.read();
        SDay[1] = file.read();
        file.read();
        SHour[0] = file.read();
        SHour[1] = file.read();
        file.read();
        SMin[0] = file.read();
        SMin[1] = file.read();
        file.read();
        SSec[0] = file.read();
        SSec[1] = file.read();

        //�������� ���� � ������
        tm.Year = CalendarYrToTm((((SYear[0] - 48) * 10 + SYear[1] - 48) * 10 + SYear[2]
                                  - 48) * 10 + SYear[3] - 48);
        tm.Month = (SMonth[0] - 48) * 10 + (SMonth[1] - 48);
        tm.Day = (SDay[0] - 48) * 10 + (SDay[1] - 48);
        tm.Hour = (SHour[0] - 48) * 10 + (SHour[1] - 48);
        tm.Minute = (SMin[0] - 48) * 10 + (SMin[1] - 48);
        tm.Second = (SSec[0] - 48) * 10 + (SSec[1] - 48);
        RTC.write(tm);                                                                                                  //���������� �����
      }
      file.close();
      sd.remove("time.txt");
    }


  public:
    Clock() {
      SetTime();
      
      tmElements_t tm;
      RTC.read(tm);
      
      Serial.print(1970 + tm.Year);   //���� ��������� �� 1970
      Serial.print(".");
      Serial.print(tm.Month);
      Serial.print(".");
      Serial.print(tm.Day);
      Serial.print(" ");
      //      Serial.print(tm.Hour);
      Serial.print(getHour());
      Serial.print(":");
      Serial.print(tm.Minute);
      Serial.print(":");
      Serial.println(tm.Second);
    }


    void getDateFileName(char *fileName) {                                                                                             //������ ����� ����� �� ���
      
      tmElements_t tm;
      RTC.read(tm);

      fileName[0] = tm.Day / 10 + 48;
      fileName[1] = tm.Day % 10 + 48;
      fileName[2] = '_';
      fileName[3] = tm.Month / 10 + 48;
      fileName[4] = tm.Month % 10 + 48;
      fileName[5] = '_';
      fileName[6] = (((tm.Year + 1970) % 1000) % 100) / 10 + 48;
      fileName[7] = (((tm.Year % 1000 + 1970)) % 100) % 10 + 48;
      fileName[8] = '.';
      fileName[9] = 'c';
      fileName[10] = 's';
      fileName[11] = 'v';
    }

    int getHour() {
      
      tmElements_t tm;
      RTC.read(tm);           //���������� ��������
      
      Serial.print("tm.Hour = ");
      Serial.println(tm.Hour);
      return tm.Hour;
    }

    int getMinute() {
      
      tmElements_t tm;
      RTC.read(tm);

      return tm.Minute;
    }

    int getSecond() {
      
      tmElements_t tm;
      RTC.read(tm);

      return tm.Second;
    }

    int getYear() {

      tmElements_t tm;
      RTC.read(tm);
      
      return tm.Year + 1970;
    }

    int getMonth() {
      
      tmElements_t tm;
      RTC.read(tm);

      return tm.Month;
    }

    int getDay() {
      
      tmElements_t tm;
      RTC.read(tm);

      return tm.Day;
    }
};

#endif
