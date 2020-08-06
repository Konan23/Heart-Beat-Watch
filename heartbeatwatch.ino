#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <WiFiUdp.h>
#include <NTPClient.h>               // include NTPClient library
#include <TimeLib.h>                 // include Arduino time library
// Libraries for SSD1306 OLED display
#include <Wire.h>              // include wire library (for I2C devices such as SSD1306 display)
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_SSD1306.h>  // include Adafruit SSD1306 OLED display driver
//---
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
#define LED 2        //On board LED
#define OLED_RESET   1     // define SSD1306 OLED reset at ESP8266 (Wemos)
Adafruit_SSD1306 display(OLED_RESET);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.nist.gov", 28800, 60000);
Ticker flipper;
ESP8266WebServer server(80); //Server on port 80
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
Ticker sender;
const int maxAvgSample = 20;
volatile int rate[maxAvgSample];                    // used to hold last ten IBI values
boolean sendok = false;
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find the inter beat interval
volatile int P =512;                      // used to find peak in pulse wave
volatile int T = 512;                     // used to find trough in pulse wave
volatile int thresh = 512;                // used to find instant moment of heart beat
volatile int amp = 100;                   // used to hold amplitude of pulse waveform
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat = true;       // used to seed rate array so we startup with reasonable BPM
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;  

String apiKey = "DDRZKVCQVUC704D4";
const char* ssid = "HTC";
const char* password = "12345678";
const char* servers = "api.thingspeak.com";
WiFiClient client;
void handleADC() {
 String data = "{\"ADC\":\""+String(BPM)+"\", \"Temperature\":\""+ String(IBI) +"\", \"Humidity\":\""+ String(Signal) +"\"}";
 
 digitalWrite(LED,!digitalRead(LED)); //Toggle LED on data request ajax
 server.send(200, "text/plane", data); //Send ADC value, temperature and humidity JSON to client ajax request

 
 //Give enough time to handle client to avoid problems
  Serial.print(BPM, 1);

}
void setup() {
  Serial.begin(115200);
  delay(10);
  Wire.begin(4, 5); // set I2C pins [SDA = GPIO4 (D2), SCL = GPIO5 (D1)]
  Wire.setClock(400000L);   // set I2C clock to 400kHz
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128×64)
  display.clearDisplay();  // clear the display buffer.
  display.setTextColor(WHITE, BLACK);
  draw_text(2, 0, "BPM =", BPM);
  draw_text(15, 0, "IBI =", IBI);
  display.display();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("connecting to ");
 // Serial.println(host);

  //client.print("255");
  delay(10);
    
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/readADC", handleADC); //This page is called by java Script AJAX
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
    Serial.println();
  Serial.println("end Setup");
  flipper.attach_ms(2, Test);
  sender.attach(2, senderfunc);
   timeClient.begin();
}

void senderfunc()
{
  sendok=true;
}

char Time[] = "  :  :  ";
char Date[] = "  -  -20  ";
byte last_second, second_, minute_, hour_, wday, day_, month_, year_;

void loop() 
{ 
   timeClient.update();
  unsigned long unix_epoch = timeClient.getEpochTime();   // get UNIX Epoch time
  second_ = second(unix_epoch);        // get seconds from the UNIX Epoch time
  if (last_second != second_)
  {
    minute_ = minute(unix_epoch);      // get minutes (0 – 59)
    hour_   = hour(unix_epoch);        // get hours   (0 – 23)
    wday    = weekday(unix_epoch);     // get minutes (1 – 7 with Sunday is day 1)
    day_    = day(unix_epoch);         // get month day (1 – 31, depends on month)
    month_  = month(unix_epoch);       // get month (1 – 12 with Jan is month 1)
    year_   = year(unix_epoch) - 2000; // get year with 4 digits – 2000 results 2 digits year (ex: 2018 –> 18)
    Time[7] = second_ % 10 + '0';
    Time[6] = second_ / 10 + '0';
    Time[4] = minute_ % 10 + '0';
    Time[3] = minute_ / 10 + '0';
    Time[1] = hour_   % 10 + '0';
    Time[0] = hour_   / 10 + '0';
    Date[9] = year_   % 10 + '0';
    Date[8] = year_   / 10 + '0';
    Date[4] = month_  % 10 + '0';
    Date[3] = month_  / 10 + '0';
    Date[1] = day_    % 10 + '0';
    Date[0] = day_    / 10 + '0';
    display_wday();
    draw_text(4,  29, Date, 2);        // display date (format: dd-mm-yyyy)
    draw_text(16, 50, Time, 2);        // display time (format: hh:mm:ss)
    display.display();
    last_second = second_;
  }
  delay(200);
  
     if(sendok)
     {
        delay(100);
            
              server.handleClient();
              //Serial.print("Requesting URL: ");
              
              // This will send the request to the server
          //    client.print(BPM);
              Serial.println(BPM);
              delay(10);
              sendok =false;
              flipper.attach_ms(2, Test);
     }

     if (client.connect(servers, 80)) { //server thingspeak là “184.106.153.149” hoặc api.thingspeak.com
// Gửi dữ liệu lên thingspeak ở field1 và field2
String postStr = apiKey;
postStr += "&field1=";
postStr += String(BPM);
postStr += "&field2=";
postStr += String(IBI);
postStr += "&field3=";
postStr += String(Signal);
postStr += "\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);

}
client.stop();
// Đợi 20s rồi gửi tiếp dữ liệu
delay(200);

}

void display_wday()
{
  switch(wday){
    case 1:  draw_text(40, 15, " SUNDAY  ", 1); break;
    case 2:  draw_text(40, 15, " MONDAY  ", 1); break;
    case 3:  draw_text(40, 15, " TUESDAY ", 1); break;
    case 4:  draw_text(40, 15, "WEDNESDAY", 1); break;
    case 5:  draw_text(40, 15, "THURSDAY ", 1); break;
    case 6:  draw_text(40, 15, " FRIDAY  ", 1); break;
    default: draw_text(40, 15, "SATURDAY ", 1);
  }
}
void draw_text(byte x_pos, byte y_pos, char *text, byte text_size)
{
  display.setCursor(x_pos, y_pos);
  display.setTextSize(text_size);
  display.print(text);
}

int count = 0;
void Test()
{
  count++;
  if(count ==1000)
  {
    flipper.detach();
    count =0;
    sendok=true;  
  }
  
      Signal = analogRead(A0);              // read the Pulse Sensor 
        sampleCounter += 2;                         // keep track of the time in mS with this variable
    int N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise

      if(Signal < thresh && N > (IBI/5)*3){       // avoid dichrotic noise by waiting 3/5 of last IBI
        if (Signal < T){                        // T is the trough
            T = Signal;                         // keep track of lowest point in pulse wave 
         }
       }
      
    if(Signal > thresh && Signal > P){          // thresh condition helps avoid noise
        P = Signal;                             // P is the peak
       }                                        // keep track of highest point in pulse wave
    
  //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
  // signal surges up in value every time there is a pulse
if (N > 250){                                   // avoid high frequency noise
  if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){        
    Pulse = true;                               // set the Pulse flag when we think there is a pulse
    //digitalWrite(blinkPin,HIGH);                // turn on pin 13 LED
    IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
    lastBeatTime = sampleCounter;               // keep track of time for next pulse
         
         if(firstBeat){                         // if it's the first time we found a beat, if firstBeat == TRUE
             firstBeat = false;                 // clear firstBeat flag
             return;                            // IBI value is unreliable so discard it
            }   
         if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
            secondBeat = false;                 // clear secondBeat flag
               for(int i=0; i<=maxAvgSample-1; i++){         // seed the running total to get a realisitic BPM at startup
                    rate[i] = IBI;                      
                    }
            }
          
    // keep a running total of the last 10 IBI values
    word runningTotal = 0;                   // clear the runningTotal variable    

    for(int i=0; i<=(maxAvgSample-2); i++){                // shift data in the rate array
          rate[i] = rate[i+1];              // and drop the oldest IBI value 
          runningTotal += rate[i];          // add up the 9 oldest IBI values
        }
        
    rate[maxAvgSample-1] = IBI;                          // add the latest IBI to the rate array
    runningTotal += rate[maxAvgSample-1];                // add the latest IBI to runningTotal
    runningTotal /= maxAvgSample;                     // average the last 10 IBI values 
    BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
    QS = true;                              // set Quantified Self flag 
    // QS FLAG IS NOT CLEARED INSIDE THIS ISR
    }                       
}

  if (Signal < thresh && Pulse == true){     // when the values are going down, the beat is over
      //digitalWrite(blinkPin,LOW);            // turn off pin 13 LED
      Pulse = false;                         // reset the Pulse flag so we can do it again
      amp = P - T;                           // get amplitude of the pulse wave
      thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
      P = thresh;                            // reset these for next time
      T = thresh;
     }
  
  if (N > 2500){                             // if 2.5 seconds go by without a beat
      thresh = 512;                          // set thresh default
      P = 512;                               // set P default
      T = 512;                               // set T default
      lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date        
      firstBeat = true;                      // set these to avoid noise
      secondBeat = true;                     // when we get the heartbeat back
     }
  
  //sei();                                     // enable interrupts when youre done!
}// end isr
