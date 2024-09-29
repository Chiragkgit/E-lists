/**
 *  @filename   :   epd2in9_V2-demo.ino
 *  @brief      :   2.9inch e-paper V2 display demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     Nov 09 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <SPI.h>
#include "epd2in9_V2.h"
#include "epdpaint.h"

#define COLORED     0
#define UNCOLORED   1

/**
  * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
  * In this case, a smaller image buffer is allocated and you have to 
  * update a partial display several times.
  * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
  */
unsigned char image[1024];
Paint paint(image, 0, 0);    // width should be the multiple of 8 
Epd epd;
unsigned long time_start_ms;
unsigned long time_now_s;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("e-Paper Demo Starting");
  if (epd.Init() != 0) {
      Serial.print("e-Paper init failed");
      return;
  }
  
  Serial.println("e-Paper Demo Clearing memory");

  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  Serial.println("e-Paper Demo Displaying frame");
  epd.DisplayFrame();
  
  paint.SetRotate(ROTATE_0);
  paint.SetWidth(128);
  paint.SetHeight(20);

  /* For simplicity, the arguments are explicit numerical coordinates */
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(7, 4, "Bank1: x", &Font12, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 1, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(7, 4, "Bank2: x", &Font12, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 20 , paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(7, 4, "Bank3:x", &Font12, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 39 , paint.GetWidth(), paint.GetHeight());
  
  paint.SetWidth(16);
  paint.SetHeight(75);
  paint.SetRotate(ROTATE_90);

  paint.Clear(COLORED);
  paint.DrawStringAt(2, 4, "To Do List", &Font12, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 105, 65, paint.GetWidth(), paint.GetHeight());

  paint.SetWidth(20);
  paint.SetHeight(240);
  
  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 1, 9, 9, COLORED);
  paint.DrawStringAt(12, 2, "Finish Regional Talent Engines", &Font12, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 75, 65, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 1, 9, 9, COLORED);
  paint.DrawStringAt(12, 2, "Push Code", &Font12, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 60, 65, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 1, 9, 9, COLORED);
  paint.DrawStringAt(12, 2, "Remake the homepage", &Font12, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 45, 65, paint.GetWidth(), paint.GetHeight());
  
  epd.DisplayFrame();
  delay(3000);

  if (epd.Init() != 0) {
      Serial.print("e-Paper init failed ");
      return;
  }

  epd.DisplayFrame();


}

void loop() {

}
