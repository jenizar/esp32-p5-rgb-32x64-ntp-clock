//=================================Source Code================================
#include "WiFi.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h> 
//MatrixPanel_I2S_DMA dma_display;
MatrixPanel_I2S_DMA *dma_display = nullptr;
#include "Adafruit_GFX.h"
//#include "Fonts/Font5x7.h"
#include "Fonts/FreeSerif9pt7b.h"
//#include "Fonts/Tiny3x3a2pt7b.h"

#define PANEL_RES_X 64      // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32     // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 2      // Total number of panels chained one to another

//RGB64x32MatrixPanel_I2S_DMA dmd;

char ssid[] = "al-husna_EXT"; // Nama Wifi Anda
char pass[] = "sekolahdasar"; // Password Wifi Anda
#define TZ (+7*60*60) //Timezone

void setup(){
  Serial.begin(115200);

  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  configTime(TZ, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp"); 

 // Module configuration
  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X,   // module width
    PANEL_RES_Y,   // module height
    PANEL_CHAIN    // Chain length
  );

  mxconfig.gpio.e = 18;
  mxconfig.clkphase = false;
  mxconfig.driver = HUB75_I2S_CFG::FM6126A;

  // Display Setup
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness8(90); //0-255
  dma_display->clearScreen();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
    ESP.restart();

  time_t t;
  static time_t last_t;
  struct tm *tm;
  static const char* const wd[7] = {"Minggu","Senin","Selasa","Rabu","Kamis","Jum'at","Sabtu"};

  t = time(NULL);
  if (last_t == t) return;
  last_t = t;
  tm = localtime(&t);
  dma_display->clearScreen();
  int jam,menit,detik;
  jam = ("%02d", tm->tm_hour);
  menit = ("%02d", tm->tm_min);
  detik = ("%02d", tm->tm_sec);
  
  dma_display->setTextSize(2);    
  dma_display->setTextWrap(false);

  dma_display->setTextColor(dma_display->color444(0,15,15));
  dma_display->setCursor(0, 0);
  if(jam < 10) {
    String jam_str = String(jam);
    String jam_str1 = "0" + jam_str;
    String jam_str2 = jam_str1;
      dma_display->print(jam_str2); 
  }  
  else {
      dma_display->print(jam);   
  }  
  
//  dmd.setTextColor(dmd.color444(0,15,15));
//  dmd.setCursor(0, 0);
//  dmd.print(jam);

  dma_display->setTextColor(dma_display->color444(15,0,0));
  dma_display->setCursor(20, 0);
  dma_display->print(":"); 
  
//  dmd.setTextColor(dmd.color444(15,0,0));
//  dmd.setCursor(20, 0);
//  dmd.print(":");

  dma_display->setTextColor(dma_display->color444(0,15,15));
  dma_display->setCursor(28, 0);
  if(menit < 10) {
    String menit_str = String(menit);
    String menit_str1 = "0" + menit_str;
    String menit_str2 = menit_str1;
      dma_display->print(menit_str2); 
  }  
  else {
      dma_display->print(menit);   
  }  

//  dmd.setTextColor(dmd.color444(0,15,15));
//  dmd.setCursor(28, 0);
//  dmd.print(menit);

  dma_display->setTextColor(dma_display->color444(15,0,0));
  dma_display->setCursor(48, 0);
  dma_display->print(":"); 
  
//  dmd.setTextColor(dmd.color444(15,0,0));
//  dmd.setCursor(48, 0);
//  dmd.print(":");

  dma_display->setTextColor(dma_display->color444(0,15,15));
  dma_display->setCursor(56, 0);
  if(detik < 10) {
    String detik_str = String(detik);
    String detik_str1 = "0" + detik_str;
    String detik_str2 = detik_str1;
      dma_display->print(detik_str2); 
  }  
  else {
      dma_display->print(detik);   
  }
  //dma_display->setFont();
//  dmd.setTextColor(dmd.color444(0,15,15));
//  dmd.setCursor(56, 0);
//  dmd.print(detik);

  dma_display->setTextSize(1);   
  dma_display->setCursor(89, 0);
  dma_display->setTextColor(dma_display->color444(15,15,0));
  dma_display->print("ESP32");
  dma_display->setCursor(76, 21);
  dma_display->setTextColor(dma_display->color444(0,15,0));
  dma_display->print("John E.N");
  
//  dmd.setTextSize(1);    
//  dmd.setCursor(82, 0);
//  dmd.setTextColor(dmd.color444(15,15,0));
//  dmd.print("DOT MATRIX + ESP32");
//  dmd.setCursor(87, 8);
//  dmd.setTextColor(dmd.color444(0,15,0));
//  dmd.print("John E Nizar");

  dma_display->setTextSize(2);
  dma_display->setCursor(2, 18);
  dma_display->setTextColor(dma_display->color444(15,4,15));
  dma_display->print("P5");
  
//  dmd.setTextSize(2);    
//  dmd.setCursor(18, 18);
//  dmd.setTextColor(dmd.color444(15,4,15));
//  dmd.print("P5");

  dma_display->setCursor(33, 18);
  dma_display->setTextColor(dma_display->color444(15,0,0));
  dma_display->print("R");
  
//  dmd.setCursor(54, 18);
//  dmd.setTextColor(dmd.color444(15,0,0));
//  dmd.print("R");

  dma_display->setCursor(45, 18);
  dma_display->setTextColor(dma_display->color444(0,15,0));
  dma_display->print("G");

//  dmd.setCursor(66, 18);
//  dmd.setTextColor(dmd.color444(0,15,0));
//  dmd.print("G");

  dma_display->setCursor(57, 18);
  dma_display->setTextColor(dma_display->color444(0,0,15));
  dma_display->print("B");

//  dmd.setCursor(78, 18);
//  dmd.setTextColor(dmd.color444(0,0,15));
//  dmd.print("B");

  dma_display->setTextSize(1);   
  dma_display->setCursor(82, 8);
  dma_display->setTextColor(dma_display->color444(15,0,0));
  dma_display->print("3");

//  dmd.setCursor(102, 18);
//  dmd.setTextColor(dmd.color444(15,0,0));
//  dmd.print("3");

  dma_display->setCursor(88, 8);
  dma_display->setTextColor(dma_display->color444(15,10,4));
  dma_display->print("2");
  
//  dmd.setCursor(114, 18);
//  dmd.setTextColor(dmd.color444(15,10,4));
//  dmd.print("2");

  dma_display->setCursor(97, 8);
  dma_display->setTextColor(dma_display->color444(15,15,0));
  dma_display->print("x");
  
//  dmd.setCursor(126, 18);
//  dmd.setTextColor(dmd.color444(15,15,0));
//  dmd.print("x");

  dma_display->setCursor(106, 8);
  dma_display->setTextColor(dma_display->color444(0,15,0));
  dma_display->print("1");
    
//  dmd.setCursor(136, 18);
//  dmd.setTextColor(dmd.color444(0,15,0));
//  dmd.print("1");

  dma_display->setCursor(112, 8);
  dma_display->setTextColor(dma_display->color444(0,15,10));
  dma_display->print("2");
  
//  dmd.setCursor(148, 18);
//  dmd.setTextColor(dmd.color444(0,15,10));
//  dmd.print("9");

  dma_display->setCursor(118, 8);
  dma_display->setTextColor(dma_display->color444(0,15,15));
  dma_display->print("8");
  
//  dmd.setCursor(160, 18);
//  dmd.setTextColor(dmd.color444(0,15,15));
//  dmd.print("2");
//  dmd.showDMABuffer();   

}
