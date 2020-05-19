
#ifndef __GENOS__DRIVERS__MOUSE_H
#define __GENOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace GenOS
{
  namespace drivers
  {

    class MouseEventHandler
    {
    public:
      MouseEventHandler();

      virtual void OnActivate();
      virtual void OnMouseDown(GenOS::common::uint8_t button);
      virtual void OnMouseUp(GenOS::common::uint8_t button);
      virtual void OnMouseMove(int x, int y);
    };


    class MouseDriver : public GenOS::hardwarecommunication::InterruptHandler, public Driver
    {
      GenOS::hardwarecommunication::Port8Bit dataport;
      GenOS::hardwarecommunication::Port8Bit commandport;
      GenOS::common::uint8_t buffer[3];
      GenOS::common::uint8_t offset;
      GenOS::common::uint8_t buttons;

      MouseEventHandler* handler;
    public:
      MouseDriver(GenOS::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
      ~MouseDriver();
      virtual GenOS::common::uint32_t HandleInterrupt(GenOS::common::uint32_t esp);
      virtual void Activate();
    };

  }
}

#endif
