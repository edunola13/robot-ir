#include <SPI.h>
//#include <MemoryFree.h>
//Serial.println(freeMemory());

// Uncomment to enable printing out nice debug messages.
#define DOMO_DEBUG
//#define DOMO_SPEED 9600
//#define USE_WDT 
//#define WDT_TIME WDTO_8S
#include "vendor/igniteit/arduino-general-use/common_initial.h"
#include "messages.h"

#include "vendor/igniteit/arduino-basic-oo/JsonHelper.cpp"
#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.cpp"

#include <SoftwareSerial.h>
#include "vendor/igniteit/arduino-general-use/serial/StreamCom.h"
#include "vendor/igniteit/arduino-general-use/serial/StreamCom.cpp"

StreamCom streamCom;
SoftwareSerial stream(2, 3); // RX | TX

#include <IRremote.h>
int RECV_PIN = 11; 
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;
#include "ir_helper.h"

void setup() {
  //BASIC
  initialGeneric();
  //SERIAL
  DEB_DO_PRINTLN(INIT_SERIAL);
  stream.begin(57600);//O Serial.begin(57600)
  streamCom.init(&stream);

  DEB_DO_PRINTLN(INIT_IR_REC);
  irrecv.enableIRIn(); // Empezamos la recepción  por IR
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.decode_type == UNKNOWN) {
      DEB_DO_PRINTLN(INIT_IR_REC_ERROR);
    } else {
      DEB_DO_PRINTLN(INIT_IR_REC_OK);
      String data = String("#dt=") + String(results.decode_type) 
                  + String("|ad=") + String(results.address)
                  + String("|va=") + String(results.value)
                  + String("|bi=") + String(results.bits)
                  + String("|rl=") + String(results.rawlen);
      streamCom.sendMessage(data, '*');
    }
    irrecv.resume(); // empezamos una nueva recepción
  }
  
  if (streamCom.isMessage()) {
    DEB_DO_PRINTLN(NEW_MSG);
    //Los mensajes deben empezar con '*' y terminar con '#'
    String data = streamCom.readMessageUp('*');
    if (data != "**" && data.charAt(0) == '#') {
      DEB_DO_PRINTLN(MSG_OK);
      data = data.substring(1);
      //
      //SI HAY MAS ACCIONES VER ACA
      sendGenericIr(data);

      //String msg = "#OK";
      //streamCom.sendMessage(msg, '*');
    } else {
      DEB_DO_PRINTLN(MSG_ERROR);
      //String msg = "#ERROR";
      //streamCom.sendMessage(msg, '*');
    }
  }
}

void sendGenericIr(String data) {
  decode_results dataResults;
  dataResults.decode_type = parsePropertyTy2(&data, "dt", 4).toInt();
  dataResults.address = parsePropertyTy2(&data, "ad", 5).toInt();
  dataResults.value = parsePropertyTy2(&data, "va", 32).toInt();
  dataResults.bits = parsePropertyTy2(&data, "bi", 4).toInt();
  dataResults.rawlen = parsePropertyTy2(&data, "rl", 4).toInt();

  sendIr(dataResults);
}

