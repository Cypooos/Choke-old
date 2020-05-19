#ifndef __GENOS__COMMON__GRAPHICSCONTEXT_H
#define __GENOS__COMMON__GRAPHICSCONTEXT_H

#include <drivers/vga.h>
#include <textgui/tgm.h>


namespace GenOS
{
  namespace common
  {

    typedef GenOS::drivers::VideoGraphicsArray GraphicsContext;
    typedef GenOS::textgui::TextGraphicsManager TextGraphicsContext;

  }
}



#endif
