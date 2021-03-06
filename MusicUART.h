#ifndef MusicUART_h
#define MusicUART_h

static int8_t Send_buf[8] = {0} ;

#define CMD_PLAY_W_INDEX 0X03
#define CMD_SET_VOLUME 0X06
#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_SINGLE_CYCLE 0X19
#define SINGLE_CYCLE_ON 0X00
#define SINGLE_CYCLE_OFF 0X01
#define CMD_PLAY_W_VOL 0X22
#define CMD_STOP_PLAY 0X16

class MusicUART {

  private:

    void sendCommand(int8_t command, int16_t dat)
    {
      delay(20);
      Send_buf[0] = 0x7e; //starting byte
      Send_buf[1] = 0xff; //version
      Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
      Send_buf[3] = command; //
      Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
      Send_buf[5] = (int8_t)(dat >> 8);//datah
      Send_buf[6] = (int8_t)(dat); //datal
      Send_buf[7] = 0xef; //ending byte
      for (uint8_t i = 0; i < 8; i++) //
      {
        Serial.write(Send_buf[i]) ;
      }
    }

  public:
    MusicUART() {
      delay(500);//Wait chip initialization is complete
      sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card
      delay(200);//wait for 200ms
    }

    void setVolume(int16_t newVolume) { //30 - max (in HEX)
      sendCommand(CMD_SET_VOLUME, newVolume);
    }

    void startDirectoryOne() {
      sendCommand(0X17, 0X0102);
    }

    void startDirectoryTwo() {
      sendCommand(0X17, 0X0202);
    }

    void startDirectoryThree() {
      sendCommand(0X17, 0X0302);
    }

    void startDirectoryFour() {
      sendCommand(0X17, 0X0402);
    }

    void startDirectoryFive() {
      sendCommand(0X17, 0X0502);
    }

    void startAudio1() {
      sendCommand(0X08, 0X0001);
    }

    void startAudio2() {
      sendCommand(0X08, 0X0002);
    }

    void startAudio3() {
      sendCommand(0X08, 0X0003);
    }

    void stopMusic() {
      sendCommand(CMD_STOP_PLAY,0);
    }
};

#endif
