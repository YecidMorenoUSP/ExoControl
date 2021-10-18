//#define DEBUG_COM
#include <Utils_COM_esp32.h>

// [I] IMPORTANTE

    typedef struct {
      float S1;
      float S2;
    } ToSend;
    
    typedef struct {
      char Type [8];
    } ToRec;
    
    ToSend * toSend;
    ToRec  * toRecv;
    COM::COM_Object comData;

// [F] IMPORTANTE


int _T0 = 0;
int SENDING = 0;
bool isRUNNING = false;


#include <TFT_eSPI.h>
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();
const int ledPin = 4;
const int freq = 5000;
const int ledChannel = 2;
const int resolution = 8;

void setup() {

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
  ledcWrite(ledChannel, 100);
  setBrightness(100);

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK, TFT_GREEN);
  
  
  
  // [I] IMPORTANTE
  
      comData.baudRate = 1000000;
      comData.buffRec_SIZE  = sizeof(ToRec);
      comData.buffSend_SIZE = sizeof(ToSend);

      //toSend  =  (ToSend*) &comData.buffSend;
      //toRecv  =  (ToRec*)  &comData.buffRec;
      
      memmove(&toSend , &comData.buffSend ,  sizeof(ToSend));
      memmove(&toRecv , &comData.buffRec  ,  sizeof(ToRec ));
    
      COM::initCOM(&comData);

      COM_DEBUG_LOG("\n size of ToSend %d",sizeof(ToSend));
      COM_DEBUG_LOG("\n size of ToRec %d",sizeof(ToRec));


  // [F] IMPORTANTE

  _T0 = millis();
  
}

void loop() {
  // [I] IMPORTANTE
        COM::Update();
  // [F] IMPORTANTE

  if ((SENDING--) > 0 && isRUNNING) {

    toSend->S1   = (float)  1.0f * sin(2.0f*PI*1.0f*((millis() - _T0)/1000.0f));
    toSend->S2   = (float) -2.0f * sin(2.0f*PI*2.0f*((millis() - _T0)/1000.0f));
    Serial.write(comData.buffSend, sizeof(ToSend));
    
    delay(3);

  }

}

void COM_Callback(){
  
   if (isCommand(toRecv->Type, COM_BEGIN_TX)) {
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0, 0, 2);
      tft.println("Utils_COM.h");
      COM_DEBUG_LOG("\nHola Wuapo");
      SENDING = 100;
      isRUNNING = true;
      _T0 = millis();
    } else if (isCommand(toRecv->Type, COM_END_TX)) {
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0, 0, 2);
      COM_DEBUG_LOG("\nChao Wuapo");
      SENDING = 0;
      isRUNNING = false;
      Serial.flush();
      delay(200);
    } else if (isCommand(toRecv->Type, COM_ALIVE_TX)) {
      tft.printf("%s %dms\n",COM_ALIVE_TX,millis()-_T0);
      SENDING = 100;
      COM_DEBUG_LOG("\nAqui estoy Wuapo");
    } else {
      COM_DEBUG_LOG("\nQue quiere loca ????   :    ");
      COM_DEBUG_LOG("%s",toRecv->Type);
      tft.printf("Undefined %s\n",toRecv->Type);
      //COM::ReadBytesSync(&toRec2,sizeof(ToRec));   
      //Serial.printf("\n REC2 %c %c %c %c %d",toRec2.rest[0],toRec2.rest[1],toRec2.rest[2],toRec2.rest[3],toRec2.Type[0]);
    }
}



void setBrightness(int aux){
  ledcWrite(ledChannel, aux);
}
