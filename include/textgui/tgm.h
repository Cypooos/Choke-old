#ifndef __GENOS__TEXTGUI__TGM_H
#define __GENOS__TEXTGUI__TGM_H

#include <common/types.h>
#include <drivers/driver.h>
#include <common/includer.h>


namespace GenOS
{
  namespace textgui
  {
    class TextGraphicsManager
    {
    private:
      common::uint16_t* VideoMemory;

    public:
      TextGraphicsManager();
      ~TextGraphicsManager();

      void write(common::string text, common::uint8_t x, common::uint8_t y, int ink=0x0F00);
      void clearScreen();
      int getColor(common::string front, common::string back="black");
      void invert(common::uint8_t x, common::uint8_t y);
    };
  }
}
#endif
