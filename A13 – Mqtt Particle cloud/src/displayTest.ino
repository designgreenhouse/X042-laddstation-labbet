/* JHJ testing the Adafruit_SSD1306 display 
*/

#include <Adafruit_SSD1306.h>
#include "MQTT.h"
#include "PollingTimer.h"

// Can do debounce too
//https://github.com/DonGar/PollingTimer

// use hardware SPI
#define OLED_DC D3
#define OLED_CS D4
#define OLED_RESET D5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

void callback(char *topic, byte *payload, unsigned int length);
MQTT client("skinny.skycharts.net", 1883, callback);

char msgStr[100] = "Nothing received yet";
volatile int x, minX, maxX;
volatile int msgChanges = 0;
volatile int dir = -1;
PollingTimer msgTimer(5);

#define buzzerPin D0
PollingTimer buzzerTimer(70);
volatile int buzzerState = 0;

void setMessage(char *str)
{
  msgChanges = 1;

  // So not entirely sure why 3 and -40 works..
  strcpy(msgStr, str);
  maxX = strlen(msgStr) * 3;
  minX = strlen(msgStr) * -40;
  x = strlen(msgStr) * 3;
  dir = -1;

  Serial.print("New message with ");
  Serial.print(maxX);
  Serial.print(" ");
  Serial.println(minX);

  msgChanges = 0;
  buzzerState = 1;
}

// recieve message
void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;

  Serial.print("MQTT rx:");
  Serial.println(p);
  setMessage(p);
}

void setup()
{
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT); 
  digitalWrite(buzzerPin, 0);

  display.begin(SSD1306_SWITCHCAPVCC);

  display.setTextSize(7);      // text size
  display.setTextColor(WHITE); // text color
  display.setTextWrap(false);  // turn off text wrapping so we can do scrolling

  setMessage((char *)"");

  // connect to the server(unique id by Time.now())
  client.connect("sparkclient_" + String(Time.now()));

  // publish/subscribe
  if (client.isConnected())
  {
    client.subscribe("debug");
    client.publish("debug", "MQTT works");
  }

  buzzerTimer.start();
  msgTimer.start();
}

void loop()
{

  if (client.isConnected()) {
    client.loop();
  }

  if (msgTimer.interval() && !msgChanges) {
    display.clearDisplay();
    display.setCursor(x, 7);
    display.print(msgStr);
    display.display();

    x += dir;

    if (x < minX || x >= maxX) {
      dir *= -1;
      //Serial.print("reversing at ");
      //Serial.println(x);
    }
  }

  if (buzzerTimer.interval() && buzzerState) {
    digitalWrite(buzzerPin, buzzerState&1);
    // Has to be even number so buzzer stays off
    if (++buzzerState >= 5) {
      buzzerState = 0;
    }
    
  }
  
}
