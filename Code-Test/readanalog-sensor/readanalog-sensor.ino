#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 37
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
void setup(void) 
{ 
 Serial.begin(9600); 
 // Start up the library 
 sensors.begin(); 
} 
void loop(void) 
{ 
 Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures();
// Serial.println("DONE"); 
// Serial.print("Temperature is: "); 
// Serial.print(sensors.getTempCByIndex(0));
 float temp = sensors.getTempCByIndex(0);
 delay(300); 
 Serial.println("Nhiệt độ hiện tại là : " + String(temp));
// Serial.println(temp);  
}
