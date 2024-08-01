#include <Adafruit_PCD8544.h>
#include <Adafruit_GFX.h>
#include <Servo.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(12, 11, 10, 9, 8);
Servo motor;
int aci = 0;
#define buton 4
boolean durum = false; // Initialize durum as false

void setup()
{
  motor.write(0);
  display.begin();
  display.setContrast(57);
  display.clearDisplay();
  Serial.begin(9600);
  pinMode(buton, INPUT);
  motor.attach(3);
}

void drawCustomDegreeSymbol(int x, int y)
{
  // Manually draw a custom degree symbol (angle symbol)
  display.drawLine(x, y , x , y + 2, BLACK);
  display.drawLine(x , y , x + 2, y , BLACK);
  display.drawLine(x + 2, y, x + 2, y + 2, BLACK);
  display.drawLine(x, y + 2, x + 2, y + 2, BLACK);
}

void loop()
{
  if (digitalRead(buton) == LOW) // Check if the button is pressed
  {
    if (!durum) // Check if the measurement is not in progress
    {
      // Start angle measurement
      durum = true;
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(10, 15);
      display.println("Hesaplaniyor...");
      display.display();
    }

    // Increment the servo angle
    for (int i = 0; i < 180; i++)
    {
      motor.write(i);
      delay(100);
      if (digitalRead(buton) == HIGH) // Check if the button is released
      {
        aci = i; // Store the angle value
        break; // Exit the loop
      }
    }

    // Display the measured angle with the custom degree symbol
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(10, 0);
    display.println("Olculen Aci:");
    display.display();
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(10, 15);
    display.print(aci);

    // Calculate the position of the degree symbol based on the number width
    int numberWidth = display.getCursorX();
    int degreeSymbolX = 40 + numberWidth - 4; // Adjust the 4 for spacing
    drawCustomDegreeSymbol(degreeSymbolX, 0); // Draw the custom degree symbol
    display.display();

    Serial.print("Açı değeri : ");
    Serial.print(aci);
    Serial.println(" derecedir.");
    delay(1000);
    display.clearDisplay();
    delay(200);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(10, 15);
    display.println("Aci Olcer");
    display.display();
    delay(100);
    aci = 0;
    motor.write(0);
    durum = false; // Reset the measurement state
  }
}
