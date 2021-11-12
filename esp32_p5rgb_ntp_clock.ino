// REQUIRES the following Arduino libraries:
// - Adafruit RGB matrix Panel Library: https://github.com/adafruit/RGB-matrix-Panel
// - Adafruit_GFX Library: https://github.com/adafruit/Adafruit-GFX-Library
// - Adafruit_BusIO Library: https://github.com/adafruit/Adafruit_BusIO
// - package_esp32_index.json found at https://dl.espressif.com/dl/package_esp32_index.json
// Find All "Great Projects" Videos : https://www.youtube.com/channel/UCCC8DuqicBtP3A_aC53HYDQ/videos

#include <WiFi.h>
#include <Adafruit_GFX.h>
//#include <RGBmatrixPanel.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h> 
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/kongtext4pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/Tiny3x3a2pt7b.h>

//#define TZ 1
//#define CLK  15  
//#define OE   33
//#define LAT 32
//#define A   12
//#define B   16
//#define C   17
//#define D   18
//RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

MatrixPanel_I2S_DMA *dma_display = nullptr;
#define PANEL_RES_X 64      // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32     // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1      // Total number of panels chained one to another

char ssid[] = "al-husna_EXT"; // Nama Wifi Anda
char pass[] = "sekolahdasar"; // Password Wifi Anda
#define TZ (+7*60*60) //Timezone

bool flasher = false;
uint8_t r = 0, g = 0, b = 0;
int h, m, s, d, yr;
uint8_t month, dow;
String text;
unsigned int NewRTCh = 24;
unsigned int NewRTCm = 60;
unsigned int NewRTCs = 10;
time_t t;

const char* wd[7] = {"Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday"};
const char* months []= {"Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

// standard colors
uint16_t myRED = dma_display->color333(7,0,0);
uint16_t myGREEN = dma_display->color333(0,7,0);
uint16_t myBLUE = dma_display->color333(0,0,7);
uint16_t myWHITE = dma_display->color333(7, 7,7);
uint16_t myYELLOW = dma_display->color333(7,7,0);
uint16_t myCYAN = dma_display->color333(0,7,7);
uint16_t myMAGENTA = dma_display->color333(7,0,7);
uint16_t myShadow = dma_display->color333(4,0,7);
uint16_t myROSE = dma_display->color333(7,0,4);
uint16_t myBLACK = dma_display->color333(0,0,0);
uint16_t myCOLORS[9] = {myRED, myGREEN, myWHITE, myMAGENTA, myBLUE, myYELLOW, myCYAN, myShadow, myROSE};
void getTim()
{
  if (flasher)
  {
    dma_display->fillRect(54, 10, 10, 6, myBLACK);
    dma_display->setCursor(19, 8);
    dma_display->setTextSize(2);
    dma_display->setTextColor(myCOLORS[g]);
    dma_display->print(":");
    b = random(0,8);
  }else
  {                       
    dma_display->fillRect(24, 12, 2, 6, myBLACK);
    dma_display->setCursor(54, 10);
    dma_display->setTextSize(1);
    dma_display->setFont(&kongtext4pt7b);
    dma_display->setTextColor(myCOLORS[b]);
    dma_display->print("*");
    dma_display->setFont();
    g = random(0,8);
  } 
  if (NewRTCs != s / 10)
  {      
    dma_display->fillRect(51, 17, 13, 6, myBLACK);
    NewRTCs = s / 10;
    dofw_text();
  } else
  {       
    dma_display->fillRect(58, 17, 6, 6, myBLACK);
  }
    dma_display->setCursor(51, 16);
    dma_display->setTextSize(1);
    dma_display->setTextColor(myCOLORS[r]);
    dma_display->setFont(&kongtext4pt7b);
    dma_display->printf("%02d", s);
    dma_display->setFont();
    if (NewRTCm != m)
      {
  dma_display->setCursor(26, 14);
  dma_display->setFont(&FreeMonoBold9pt7b);
  dma_display->setTextColor(myMAGENTA);
  dma_display->fillRect(26, 8, 25, 15, myBLACK);
  dma_display->printf("%02d", m);
  dma_display->setFont();
  NewRTCm = m;
      }
  if (NewRTCh != h)
      {
  dma_display->setCursor(0, 14);
  dma_display->setFont(&FreeMonoBold9pt7b);
  dma_display->setTextColor(myMAGENTA);
  dma_display->fillRect(0, 8, 24, 15, myBLACK);
  dma_display->printf("%02d", h);
  dma_display->setFont();
  NewRTCh = h;
      }
}
void Date_text()
{
  dma_display->setCursor(1, 23);
  dma_display->fillRect(0, 23, 64, 8, myBLACK);
  dma_display->setFont(&kongtext4pt7b);
  dma_display->setTextColor(myRED);
  dma_display->printf("%02d", d);
  dma_display->setTextColor(myGREEN);
  dma_display->printf("%s", months[month]);
  dma_display->setTextColor(myRED);
  dma_display->printf("%04d", yr);
  dma_display->setFont();
}
void dofw_text()
{
  text = wd[dow];
  uint16_t text_length = text.length();
  int xpo = (64 - text_length * 7) / 2;
  dma_display->setCursor(xpo, 0);
  dma_display->fillRect(0, 0, 64, 8, myBLACK);
  dma_display->setTextSize(1); 
  dma_display->setFont(&kongtext4pt7b);
  for (int y = 0; y < 9; y++) {
    r = random(0,8);
    dma_display->setTextColor(myCOLORS[r]);
    dma_display->print(text[y]);
  }
  dma_display->setFont();
}
  
void setup() {
  Serial.begin(115200);

  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid);                   // print the network name (SSID);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  //configTime(TZ*3600, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp"); // enable NTP
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
  
//  matrix.begin();                           // setup the LED matrix
//  matrix.fillScreen(0);
}

void loop() 
{

  if (WiFi.status() != WL_CONNECTED)
    ESP.restart();
      
  static time_t last_t;
  t = time(NULL);
  if (last_t != t) 
    {
      updateTime();
      getTim();
      flasher = !flasher;
      last_t = t;
    }
}

void updateTime()
{
  struct tm *tm;
  tm = localtime(&t);
  h = tm->tm_hour;
  m = tm->tm_min;
  s = tm->tm_sec;
  if (d != tm->tm_mday || month != tm->tm_mon || yr != tm->tm_year + 1900) 
    {
  d = tm->tm_mday;
  dow = tm->tm_wday;
  month = tm->tm_mon;
  yr = tm->tm_year + 1900;
  Date_text();
    }
}
