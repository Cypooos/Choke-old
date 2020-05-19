#include <textgui/tgm.h>
using namespace GenOS;
using namespace GenOS::common;
using namespace GenOS::textgui;



TextGraphicsManager::TextGraphicsManager()
{
  if (VideoMemory == (uint16_t*)0xb8000){TextGraphicsManager::write("Alert Second TGM instance :(",0,0);}
  VideoMemory = (uint16_t*)0xb8000;
}
TextGraphicsManager::~TextGraphicsManager()
{}

void TextGraphicsManager::clearScreen()
{
  for(uint8_t y = 0; y < 25; y++)
    for(uint8_t x = 0; x < 80; x++)
      VideoMemory[80*y+x] = (0x0F00) | ' ';
}

void TextGraphicsManager::write(string text, uint8_t startx, uint8_t starty, int ink)
{
  int color = ink;
  uint8_t x = startx;
  uint8_t y = starty;
  for(int i = 0; text[i] != '\0'; ++i)
  {
    switch(text[i])
    {
      case '$':
        {
          if(text[i+1]=='$') {VideoMemory[80*y+x] = color | text[i];i++;break;} // if not double
          if (text[i+1]=='\0' || text[i+2]=='\0') {VideoMemory[80*y+x] = color | text[i];break;} // if not error
          if(text[i+1]=='!') {color = ink;i--;} // if not reset
          else {
            char* foo = "00";
            foo[0] = text[i+1];
            foo[1] = text[i+2];
            color = Converter::strToHex(foo);
            color = color << 8; // 0xFF00 => 0xABCD .A => Background B => forground
          }
          i+=2;x--;
          break;
        }

      case '\n':
        x = startx-1; y++;break;
      default:
        VideoMemory[80*y+x] = color | text[i];
        break;
    }

    x++;
    if(x >= 80){x = startx;y++;}
    if(y >= 25) {return;}
  }
}


int TextGraphicsManager::getColor(common::string front, common::string back)
{
  //switch (front) {
  //  case "":
  //}\*
  return 0x0F;
}

void TextGraphicsManager::invert(uint8_t x, uint8_t y)
{
  VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
            | (VideoMemory[80*y+x] & 0xF000) >> 4
            | (VideoMemory[80*y+x] & 0x00FF);
}
