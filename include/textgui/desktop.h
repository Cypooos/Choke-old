#ifndef __GENOS__TEXTGUI__DESKTOP_H
#define __GENOS__TEXTGUI__DESKTOP_H

#include <drivers/mouse.h>
#include <drivers/keyboard.h>
#include <common/types.h>
#include <common/graphicscontext.h>
#include <common/includer.h>

namespace GenOS
{
  namespace textgui
  {

    struct ReadFile {
      char* path;
      char* name;
      char* content;
    };

    struct Folder
    {
      char* path;
      char* elementspaths[100];
    };

    class TextDesktop : public GenOS::drivers::MouseEventHandler, public GenOS::drivers::KeyboardEventHandler
    {
    private:
      // mouse argsn
      common::uint32_t mouseX;
      common::uint32_t mouseY;
      common::uint8_t sensivity;

      // desktop args
      common::uint32_t menuCursor;
      char* path;
      char* fileselect;

      // draw args
      common::TextGraphicsContext* gc;
      common::string debugInterrupt; // what called draw
      char* printLeft;


      void reloadPath();

    public:
      Folder folders[100];
      ReadFile readFiles[100];

      Folder activeFolder;

      common::uint8_t scroll;

      TextDesktop(common::TextGraphicsContext* graphicscontext);
      ~TextDesktop();

      void Draw();

      void Select(GenOS::common::uint8_t element);

      void OnMouseDown(GenOS::common::uint8_t button);
      void OnMouseUp(GenOS::common::uint8_t button);
      void OnMouseMove(int x, int y);

      void OnKeyDown(common::string key);

    };

  }
}
#endif
