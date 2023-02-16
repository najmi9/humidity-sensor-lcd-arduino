#include <U8g2lib.h>
#include <U8x8lib.h>

U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);

int output_value ;

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_helvB10_tf);
  u8g2.setColorIndex(1);
  Serial.println("Reading From the Sensor ...");
  delay(2000);
}

void loop() {
  const int sensorValue = analogRead(A0);

  output_value = map(sensorValue, 10, 550, 0, 100);

  char humidityPercentageToString[2];

  itoa(output_value, humidityPercentageToString, 10);

  delay(10);

  u8g2.firstPage();

  do {
    draw(humidityPercentageToString);
  } while( u8g2.nextPage());
}

void draw(String humidityPercentageToString){
  u8g2.drawFrame(0,0,128,31);
  u8g2.drawFrame(0,33,128,31);
  humidityPercentageToString = humidityPercentageToString + "%";

  u8g2.drawStr(20, 20, "Air Humidity: ");

  char buffer[4];
  humidityPercentageToString.toCharArray(buffer, 4);
  u8g2.drawStr(50, 50, buffer);
}
