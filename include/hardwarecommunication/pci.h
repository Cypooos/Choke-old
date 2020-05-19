#ifndef __GENOS__HARDWARECOMMUNICATION__PCI_H
#define __GENOS__HARDWARECOMMUNICATION__PCI_H

#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>

#include <memorymanagement.h>

namespace GenOS
{
  namespace hardwarecommunication
  {

    enum BaseAddressRegisterType
    {
      MemoryMapping = 0,
      InputOutput =1
    };

    class BaseAddressRegister
    {
    public:
      bool prefetchable;
      GenOS::common::uint8_t* address;
      GenOS::common::uint32_t size;
      BaseAddressRegisterType type;
    };

    class PeripheralComponentInterconnectDeviceDescriptor
    {
      public:
        GenOS::common::uint32_t portBase;
        GenOS::common::uint32_t interrupt;

        GenOS::common::uint16_t bus;
        GenOS::common::uint16_t device;
        GenOS::common::uint16_t function;

        GenOS::common::uint16_t vendor_id;
        GenOS::common::uint16_t device_id;

        GenOS::common::uint8_t class_id;
        GenOS::common::uint8_t subclass_id;
        GenOS::common::uint8_t interface_id;

        GenOS::common::uint8_t revision;

        PeripheralComponentInterconnectDeviceDescriptor();
        ~PeripheralComponentInterconnectDeviceDescriptor();

      };


      class PeripheralComponentInterconnectController
      {
        Port32Bit dataPort;
        Port32Bit commandPort;

      public:
        PeripheralComponentInterconnectController();
        ~PeripheralComponentInterconnectController();

        GenOS::common::uint32_t Read(GenOS::common::uint16_t bus, GenOS::common::uint16_t device, GenOS::common::uint16_t function, GenOS::common::uint32_t registeroffset);
        void Write(GenOS::common::uint16_t bus, GenOS::common::uint16_t device, GenOS::common::uint16_t function, GenOS::common::uint32_t registeroffset, GenOS::common::uint32_t value);
        bool DeviceHasFunctions(GenOS::common::uint16_t bus, GenOS::common::uint16_t device);


        void SelectDrivers(GenOS::drivers::DriverManager* driverManager,GenOS::hardwarecommunication::InterruptManager* interrupts);
        GenOS::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, GenOS::hardwarecommunication::InterruptManager* interrupts);
        PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(GenOS::common::uint16_t bus, GenOS::common::uint16_t device, GenOS::common::uint16_t function);
        BaseAddressRegister GetBaseAddressRegister(GenOS::common::uint16_t bus, GenOS::common::uint16_t device, GenOS::common::uint16_t function, GenOS::common::uint16_t bar);

    };

  }
}

#endif
