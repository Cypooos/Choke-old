#ifndef __GENOS__GUI__WIDGET_H
#define __GENOS__GUI__WIDGET_H

#include <common/types.h>
#include <common/graphicscontext.h>
#include <drivers/keyboard.h>

namespace GenOS
{
  namespace gui
  {
    class Widget : public GenOS::drivers::KeyboardEventHandler
    {
    protected:
      Widget* parent;
      common::int32_t x;
      common::int32_t y;
      common::int32_t w;
      common::int32_t h;

      common::int32_t r;
      common::int32_t g;
      common::int32_t b;

      bool focussable;

    public:

      Widget(Widget* parent, common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h, common::int32_t r, common::int32_t g,common::int32_t b);
      ~Widget();



      virtual void GetFocus(Widget* widget);
      virtual void ModelToScreen(common::int32_t &x, common::int32_t &y);
      virtual bool CountainsCoordinate(common::int32_t x, common::int32_t y);

      virtual void Draw(common::GraphicsContext* gc);
      virtual void OnMouseDown(common::int32_t x,common::int32_t y, common::uint8_t button);
      virtual void OnMouseUp(common::int32_t x,common::int32_t y, common::uint8_t button);
      virtual void OnMouseMove(common::int32_t oldx,common::int32_t oldy,common::int32_t newx,common::int32_t newy);

      virtual void OnMouseEnter(common::int32_t oldx,common::int32_t oldy,common::int32_t newx,common::int32_t newy);
      virtual void OnMouseLeave(common::int32_t oldx,common::int32_t oldy,common::int32_t newx,common::int32_t newy);


    };

    class CompositeWidget : public Widget
    {
    private:
      Widget* children[100];
      int numChildren;
      Widget* focussedChild;

    public:

      CompositeWidget(Widget* parent, common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h, common::int32_t r, common::int32_t g,common::int32_t b);
      ~CompositeWidget();

      virtual void GetFocus(Widget* widget);
      virtual bool AddChild(Widget* child);

      virtual void Draw(common::GraphicsContext* gc);
      virtual void OnMouseDown(common::int32_t x, common::int32_t y, common::uint8_t button);
      virtual void OnMouseUp(common::int32_t x, common::int32_t y, common::uint8_t button);
      virtual void OnMouseMove(common::int32_t oldx, common::int32_t oldy, common::int32_t newx,common::int32_t newy);

      virtual void OnMouseEnter(common::int32_t oldx,common::int32_t oldy,common::int32_t newx,common::int32_t newy);
      virtual void OnMouseLeave(common::int32_t oldx,common::int32_t oldy,common::int32_t newx,common::int32_t newy);

      virtual void OnKeyDown(common::string);
      virtual void OnKeyUp(common::string);
    };

  }
}

#endif
