
#include <SPI.h>            
#include <Adafruit_GFX.h>    
#include <Adafruit_TFTLCD.h> 
#include <TouchScreen.h>

#define LCD_CS A3     // Chip Select goes to Analog 3
#define LCD_CD A2     // Command/Data goes to Analog 2
#define LCD_WR A1     // LCD Write goes to Analog 1
#define LCD_RD A0     // LCD Read goes to Analog 0
#define LCD_RESET A4  // Can alternately just connect to Arduino's reset pin

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;


// Define some TFT readable colour codes to human readable names
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

#define REDBAR_MINX 80
#define GREENBAR_MINX 130
#define BLUEBAR_MINX 180
#define BAR_MINY 30
#define BAR_HEIGHT 250
#define BAR_WIDTH 30

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

// from Kuman_SC3A
#define TS_MINX 85
#define TS_MAXX 925
#define TS_MINY 135
#define TS_MAXY 910

#define MINPRESSURE 10
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
boolean buttonEnabled = true;
int currentPage = 0;
// TO GET SET VALUE
char stCurrent[2]="";
int stCurrentLen=0;
char stLast[2]="";


#define PALETTEDEPTH   0  
// Sensor Temp
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 37
#define PWM_out 45
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
int PWM_ex = 0;
int value = 0;
// Function ramdom value
int random_value(int max_value, int min_value)
{
      value  = random(min_value,max_value);
      return value;
      delay(2000);
  }
// -----------------------------------SET-UP -------------------------------------------------------
void setup() {
 Serial.begin(9600);
 sensors.begin(); 
  Serial.print(F("Finding out the type of TFT LCD... ID is : "));
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print(identifier, HEX);
  tft.begin(identifier);
  Serial.print(". TFT size is : "); Serial.print(tft.width()); Serial.print(" x "); Serial.println(tft.height());
  tft.setRotation(1);
  //tft.invertDisplay(1);                           // UNCOMMENT THIS IF COLORS get inverted
  tft.fillScreen(BLACK);

  Serial.println("Drawing Init Screen...");
  drawInitScreen();
  delay(100);
  
  Serial.println("Drawing Home or Menu Screen...");
  drawHome();
  delay(100);
}

void drawInitScreen()
{
  tft.fillScreen(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(YELLOW);
  tft.setCursor(50, 100);
  tft.println(" KHOA CONG NGHE DIEN");
  tft.println("          WELCOME");
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(185, 180);
  tft.print("Loading...");

  for ( int i = 1; i < 400; i++)
  {
      tft.fillRect(30, 200, i, 15, YELLOW);
      delay(1);
  }
}

void updateStr( int val)
{
  if (stCurrentLen<3)
 {
   stCurrent[stCurrentLen]=val;
   stCurrent[stCurrentLen+1]='\0';
   stCurrentLen++;
 }
  
  }
void drawHome()
{
  // ------------------------------------------HEADING TEXT -----------------------------------
tft.fillScreen(BLACK);
tft.drawRoundRect(0, 0, 479, 319, 8, RED); // page border

//tft.fillRect(7,10,460,35,YELLOW);
tft.fillRoundRect(7,10,460,70,8,YELLOW);
tft.drawRoundRect(7,10,460,70,8,WHITE); 
tft.setCursor(130,15);
tft.setTextSize(1.5);
tft.setTextColor(RED);
tft.println(" TRUONG CAO DANG CONG NGHE CAO DONG AN");
tft.println("  ");
tft.println("                              KHOA CONG NGHE DIEN");

//tft.fillRect(7,45,460,35,YELLOW);
tft.setCursor(65,50);
tft.setTextSize(2);
tft.setTextColor(RED);
tft.println("MO HINH HE THONG LANH TRUNG TAM");
tft.println("            ------------------");


// ---------------------------------------SET VALUE------------------------------
 
tft.fillRoundRect(7,180,180,120,8,ILI9341_OLIVE);
tft.drawRoundRect(7,180,180,120,8,WHITE); 
tft.setCursor(15,190);
tft.setTextSize(2);
tft.setTextColor(RED);
tft.println(" NHIET DO DAT");

  // ------------------------------------ DRAW NUMBER --------------------------------------
          //tft.fillRoundRect(200, 100, 270, 200, 8, WHITE);
          tft.drawRoundRect(200, 100, 270, 200, 8, WHITE); 
          
          tft.fillRoundRect(205, 105, 80, 42, 8, RED);
          tft.drawRoundRect(205, 105, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(240, 115);
          tft.print("0");
          
          tft.fillRoundRect(295, 105, 80, 42, 8, RED);
          tft.drawRoundRect(295, 105, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(323, 115);
          tft.print("1");
          
          tft.fillRoundRect(385, 105, 80, 42, 8, RED);
          tft.drawRoundRect(385, 105, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(422, 115);
          tft.print("2");
          
          tft.fillRoundRect(205, 152, 80, 42, 8, RED);
          tft.drawRoundRect(205, 152, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(240, 168);
          tft.print("3");
          
          tft.fillRoundRect(295, 152, 80, 42, 8, RED);
          tft.drawRoundRect(295, 152, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(323, 168);
          tft.print("4");
          
          tft.fillRoundRect(385, 152, 80, 42, 8, RED);
          tft.drawRoundRect(385, 152, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(422, 168);
          tft.print("5");
          
          tft.fillRoundRect(205, 199, 80, 42, 8, RED);
          tft.drawRoundRect(205, 199, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(240, 212);
          tft.print("6");
          
          tft.fillRoundRect(295, 199, 80, 42, 8, RED);
          tft.drawRoundRect(295, 199, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(323, 212);
          tft.print("7");
          
          tft.fillRoundRect(385, 199, 80, 42, 8, RED);
          tft.drawRoundRect(385, 199, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(422, 212);
          tft.print("8");
          
          
          tft.fillRoundRect(205, 246, 80, 42, 8, RED);
          tft.drawRoundRect(205, 246, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(230, 258);
          tft.print("CLR");
          
          tft.fillRoundRect(295, 246, 80, 42, 8, RED);
          tft.drawRoundRect(295, 246, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(308, 258);
          tft.print("ENTER");
          
          tft.fillRoundRect(385, 246, 80, 42, 8, RED);
          tft.drawRoundRect(385, 246, 80, 42, 8, WHITE); 
          tft.setTextSize(2);
          tft.setTextColor(WHITE);  
          tft.setCursor(422, 258);
          tft.print("9");

// ----------------------------------------SHOW TEMP CURRENT--------------------------------------
//tft.fillRect(7,100,180,70,8,BLUE);
tft.fillRoundRect(7,100,180,70,8,BLUE);
tft.drawRoundRect(7,100,180,70,8, WHITE);
 
tft.setCursor(15,110);
tft.setTextSize(2);
tft.setTextColor(YELLOW);
tft.println("NHIET DO PHONG");
}


void loop(void) {  
  
//  while(1){
//  sensors.requestTemperatures();
//  tft.setCursor(70,130);
//  tft.setTextSize(2);
//  tft.setTextColor(YELLOW,BLUE);
//  float temp = sensors.getTempCByIndex(0);
//  delay(100);
//  tft.println(" ");
//  tft.setCursor(60,130);
//  tft.setTextSize(3);
//  tft.println(String(temp));
//  }; 
// While to show value sensor
  
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  
  buttonEnabled = true;
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
if (currentPage  == 0){
   
  
 if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
               
          //map(value, fromLow, fromHigh, toLow, toHigh)
          p.x = map( p.x, TS_MINX, TS_MAXX,0,  480 );
          p.y = map( p.y, TS_MINY, TS_MAXY, 0, 320 );
      
// Button number 0
          if( p.x>205 && p.x<285 && p.y>105 && p.y<147 )
          {
             delay(500);
             updateStr('0');
             Serial.println("0");
            } 
// Button number 1
          if( p.x>295 && p.x<375 && p.y>105 && p.y<147 )
          {
              delay(500);
              updateStr('1');
             Serial.println("1");
            } 
// Button number 2
          if( p.x>385 && p.x<465 && p.y>105 && p.y<147 )
          {
             delay(500);
             updateStr('2');
             Serial.println("2");
            }        
// Button number 3
          if(  p.x>205 && p.x<285 && p.y>152 && p.y< 194)
          {
             delay(500);
             updateStr('3');
             Serial.println("3");
            }   
// Button number 4
          if( p.x>295 && p.x<375 && p.y>152 && p.y< 194 )
          {
              delay(500);
              updateStr('4');
             Serial.println("4");
            }
// Button number 5 
          if( p.x>385 && p.x<465 && p.y>152 && p.y< 194 )
          {
              delay(500);
              updateStr('5');
             Serial.println("5");
            }       
// Button number 6
          if(  p.x>205 && p.x<285 && p.y>199 && p.y< 241)
          {
             delay(500);
             updateStr('6');
             Serial.println("6");
            }  

// Button number 7
          if( p.x>295 && p.x<375 && p.y>199 && p.y< 241)
          {
              delay(500);
              updateStr('7');
             Serial.println("7");
            } 

// Button number 8 
          if( p.x>385 && p.x<465 && p.y>199 && p.y< 241 )
          {
              delay(500);
              updateStr('8');
             Serial.println("8");
            } 
 // Button number 9 
          if( p.x>385 && p.x<465 && p.y>246 && p.y<288 )
          {
              delay(500);
              updateStr('9');
             Serial.println("9");
            }       

 // Button number Clear 
          if(  p.x>205 && p.x<285 && p.y>246 && p.y<288 )
          {
              stCurrent[0]='\0';
              stCurrentLen=0;
              Serial.println(" Clear value.. Please select again !! ");
              tft.setCursor(70,230);
              tft.setTextSize(4);
              tft.setTextColor(RED,ILI9341_OLIVE);
              tft.println("  ");
            }       

          
// Button Enter
          if (p.x>295 && p.x<375 && p.y>246 && p.y<288)
          {
                    if (stCurrentLen>0)
                 {
                   for (int x=0; x<stCurrentLen+1; x++)
                   {
                     stLast[x]=stCurrent[x];
                   }
                   stCurrent[0]='\0';
                   stCurrentLen=0;
                    }
                    tft.setCursor(70,230);
                    tft.setTextSize(4);
                    tft.setTextColor(RED,ILI9341_OLIVE);
                    tft.println(stLast);
                    
                    String number_set = String(stLast);
                    int send_data = number_set.toInt();
                    sensors.requestTemperatures();
                    int real_temp = sensors.getTempCByIndex(0);
                    int e_var = send_data - real_temp;
                    if (e_var <= 0 )
                    {
                      // limit bot
                      analogWrite(PWM_out,0);
                      
                      }
                     if ( e_var > 15)
                     {
                      // limit top
                      analogWrite(PWM_out,255);
                      }
                     if (e_var > 0 && e_var <=15)
                     {
                      int PWM_ex = map(send_data, 0, 15, 0, 255);
                      analogWrite(PWM_out,PWM_ex);
                      }
                    Serial.println("Nhiệt độ đặt là:" + String(send_data));
                    Serial.println("Xung PWM xuất là:" + String(PWM_ex));
                    
                    
                    
                    
                    
          
  }

          }// if biggest 
}// currentPage

//tft.setCursor(70,130);
//tft.setTextSize(2);

//tft.println(" ");
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0);
delay(300);
tft.setCursor(60,130);
tft.setTextSize(3);
tft.setTextColor(YELLOW,BLUE);
tft.println(String(temp));
}// end loop
