void sendIr(decode_results &data) {
  if (data.decode_type == RC5) {
    DEB_DO_PRINTLN(INIT_IR_SEND_RC5);
    irsend.sendRC5(data.value,  data.bits) ;
  }
  if (data.decode_type == RC6) {
    DEB_DO_PRINTLN(INIT_IR_SEND_RC6);
    irsend.sendRC6(data.value,  data.bits) ;
  }
  if (data.decode_type == NEC) {
    DEB_DO_PRINTLN(INIT_IR_SEND_NEC);
    irsend.sendNEC(data.value,  data.bits) ;
  }
  if (data.decode_type == SONY) {
    DEB_DO_PRINTLN(INIT_IR_SEND_SONY);
    irsend.sendSony(data.value,  data.bits) ;
  }
  if (data.decode_type == PANASONIC) {
    DEB_DO_PRINTLN(INIT_IR_SEND_PANASONIC);
    irsend.sendPanasonic(data.address, data.value) ;
  }
  // JVC does NOT repeat by sending a separate code (like NEC does).
    // The JVC protocol repeats by skipping the header.
    // To send a JVC repeat signal, send the original code value
    //   and set 'repeat' to true
  if (data.decode_type == JVC) {
    DEB_DO_PRINTLN(INIT_IR_SEND_JVC);
    irsend.sendJVC(data.value,  data.bits, true) ;
  }
  if (data.decode_type == SAMSUNG) {
    DEB_DO_PRINTLN(INIT_IR_SEND_SAMSUNG);
    irsend.sendSAMSUNG(data.value,  data.bits) ;
  }
  if (data.decode_type == WHYNTER) {
    DEB_DO_PRINTLN(INIT_IR_SEND_WHYNTER);
    irsend.sendWhynter(data.value,  data.bits) ;
  }
  if (data.decode_type == AIWA_RC_T501) {
    DEB_DO_PRINTLN(INIT_IR_SEND_AIWA_RC_T501);
    //void  sendAiwaRCT501 (int code) ;
    //irsend.sendAiwaRCT501(data.value) ;
  }
  if (data.decode_type == LG) {
    DEB_DO_PRINTLN(INIT_IR_SEND_LG);
    irsend.sendLG(data.value,  data.bits) ;
  }
  if (data.decode_type == SANYO) {
    DEB_DO_PRINTLN(INIT_IR_SEND_SANYO);
    //irsend.sendSanyo() ;
  }
  if (data.decode_type == MITSUBISHI) {
    DEB_DO_PRINTLN(INIT_IR_SEND_MITSUBISHI);
    //irsend.sendMitsubishi() ;
  }
  if (data.decode_type == DISH) {
    DEB_DO_PRINTLN(INIT_IR_SEND_DISH);
    irsend.sendDISH(data.value,  data.bits) ;
  }
  if (data.decode_type == SHARP) {
    DEB_DO_PRINTLN(INIT_IR_SEND_SHARP);
    irsend.sendSharpRaw(data.value,  data.bits) ;
    //void  sendSharp      (unsigned int address,  unsigned int command) ;
    //irsend.sendSharpRaw(data.address,  data.bits) ;
  }
  if (data.decode_type == DENON) {
    DEB_DO_PRINTLN(INIT_IR_SEND_DENON);
    irsend.sendDenon(data.value,  data.bits) ;
  }
  if (data.decode_type == PRONTO) {
    DEB_DO_PRINTLN(INIT_IR_SEND_PRONTO);
    //void  sendPronto     (char* code,  bool repeat,  bool fallback) ;
  }
  if (data.decode_type == LEGO_PF) {
    DEB_DO_PRINTLN(INIT_IR_SEND_LEGO_PF);
    irsend.sendLegoPowerFunctions(data.value,  true) ;
  }
}
