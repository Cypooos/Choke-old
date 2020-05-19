#ifndef __GENOS__GUI__DESKTOP_H
#define __GENOS__GUI__DESKTOP_H

#include <gui/widget.h>
#include <drivers/mouse.h>


namespace GenOS
{
  namespace gui
  {
    class Desktop : public CompositeWidget,public GenOS::drivers::MouseEventHandler
    {
    protected:
      common::uint32_t MouseX;
      common::uint32_t MouseY;

    public:
      Desktop(common::int32_t w, common::int32_t h,
        common::uint8_t r, common::uint8_t g,  common::uint8_t b);
      ~Desktop();

      void Draw(common::GraphicsContext* gc);

      void OnMouseDown(GenOS::common::uint8_t button);
      void OnMouseUp(GenOS::common::uint8_t button);
      void OnMouseMove(int x, int y);
    };

  }
}
#endif
