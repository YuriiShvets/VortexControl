#ifndef Sekyurotron_h
#define Sekyurotron_h

class Sekyurotron {

  private:
    float keys[8];                  //�����
    SdFile file;
    float key;                    //�������� ����
    int keyIndex;                 //������ ����� ��������� �� ������ (�� ���������� �����)
    int fileIndex;                //������ �������� �� ������ (�������� �� ����� �������)
    int timer;                    //������� ����������, �� ���������

  public:
    Sekyurotron() {
      //Serial.println("Sekyurotron");
      keys[0] = 89117788;
      keys[1] = 28599027;
      keys[2] = 79314302;
      keys[3] = 64614121;
      keys[4] = 16179962;
      keys[5] = 94733783;
      keys[6] = 30318080;
      keys[7] = 55944530;
      key = 0;                      //��������� ����� ���� ������� �������� �����
      keyIndex = -1;                //��������� �� ������� ������ ��������� �����
      //��������� ������ �� ������� (�� ����������, �������� ��������� ��� ������)
      fileIndex = 10;               

      //--------------- ������ ���� ------------------

      if(file.open("key.txt"))
        //Serial.println("key.txt was open");
        for(int i = 0; i < 8; i++){
          key *= 10;
          key += (file.read() - 48);
        }
      file.close();
      Serial.print("Key = ");
      Serial.println(key);

      //------------- �������� ������, ��������� �������� ���� ----------------

      for(int i = 0; i < 8; i++)
      //���� ��������������� ����� ��� ��������� ����� �������� ����� ������������� 
      //����� �� ��������� ����� (������� ������� ���� �������������)
        if(abs((int)(keys[i] - key)) < 20) { 
          keyIndex = i;
          break;
        }

      //------------ �������� ��������� �������� ����, �������� ��������� ������ 
      //-------------������ � ������� �������������� ������������� -------------------
      file.close();
      if(file.open("key2.txt")) {
          fileIndex = file.read();
          timer = file.read();
      }
      Serial.print("timer = ");
      Serial.println(timer);

      //------------- �������� ���������� ������� � ������� ����������, ������ 
      //--------------�������������� �������� ������� ���������� � ������ ����--------
  
      if(keyIndex > fileIndex) {
        fileIndex = keyIndex;
        timer = 250;
        if(file.open("key2.txt", O_RDWR)) {
          file.print((char)fileIndex);
          file.print((char)timer);
        }
        file.close();
        Serial.print("newKey: ");
        Serial.println(fileIndex);
        Serial.print("newTimer: ");
        Serial.println(timer);
      }
      Serial.print("KeyIndex = ");
      Serial.println(fileIndex);

      //------------ �������� ������������� �������� ���, �������� ������ �������� 
      //------------ ������� ���������� � ������ ����-----------------

    }

    void decrementTimer() {
      delay(10);
      if(timer > 0)
        timer--;
        
      //------------ �������� ������������ ���� -------------------

      if(file.open("key2.txt", O_RDWR)){
        file.print((char)fileIndex);
        file.print((char)timer);
      }
      file.close();
      //------------ �������� ������������ ���� ---------------------
    }

    boolean getTimerState() {
      if(timer > 0)
        return true;
      return false;
    }

    boolean getFileIndexState() {       //�������� �� �� �� �������� "������" ����
      if(fileIndex == 7)
        return true;
      return false;
    }
};

#endif
