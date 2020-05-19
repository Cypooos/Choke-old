
#ifndef __GENOS__DRIVERS__KEYBOARD_H
#define __GENOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace GenOS
{
  namespace drivers
  {

    class KeyboardEventHandler
    {
    public:
      KeyboardEventHandler();

      virtual void OnKeyDown(GenOS::common::string);
      virtual void OnKeyUp(GenOS::common::string);
    };

    class KeyboardDriver : public GenOS::hardwarecommunication::InterruptHandler, public Driver
    {
      GenOS::hardwarecommunication::Port8Bit dataport;
      GenOS::hardwarecommunication::Port8Bit commandport;

      KeyboardEventHandler* handler;
    public:
      KeyboardDriver(GenOS::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
      ~KeyboardDriver();
      virtual GenOS::common::uint32_t HandleInterrupt(GenOS::common::uint32_t esp);
      virtual void Activate();
    };

  }
}

#endif
