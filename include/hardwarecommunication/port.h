
#ifndef __GENOS__HARDWARECOMMUNICATION__PORT_H
#define __GENOS__HARDWARECOMMUNICATION__PORT_H

#include <common/types.h>

namespace GenOS
{
  namespace hardwarecommunication
  {

    class Port
    {
      protected:
        Port(GenOS::common::uint16_t portnumber);
        // FIXME: Must be virtual (currently isnt because the kernel has no memory management yet)
        ~Port();
        GenOS::common::uint16_t portnumber;
    };


    class Port8Bit : public Port
    {
      public:
        Port8Bit(GenOS::common::uint16_t portnumber);
        ~Port8Bit();

        virtual GenOS::common::uint8_t Read();
        virtual void Write(GenOS::common::uint8_t data);

      protected:
        static inline GenOS::common::uint8_t Read8(GenOS::common::uint16_t _port)
        {
          GenOS::common::uint8_t result;
          __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
          return result;
        }

        static inline void Write8(GenOS::common::uint16_t _port, GenOS::common::uint8_t _data)
          {
            __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
          }
    };



    class Port8BitSlow : public Port8Bit
    {
      public:
        Port8BitSlow(GenOS::common::uint16_t portnumber);
        ~Port8BitSlow();

        virtual void Write(GenOS::common::uint8_t data);
      protected:
        static inline void Write8Slow(GenOS::common::uint16_t _port, GenOS::common::uint8_t _data)
        {
          __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
        }
    };



    class Port16Bit : public Port
    {
      public:
        Port16Bit(GenOS::common::uint16_t portnumber);
        ~Port16Bit();

        virtual GenOS::common::uint16_t Read();
        virtual void Write(GenOS::common::uint16_t data);

      protected:
        static inline GenOS::common::uint16_t Read16(GenOS::common::uint16_t _port)
        {
          GenOS::common::uint16_t result;
          __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
          return result;
        }

        static inline void Write16(GenOS::common::uint16_t _port, GenOS::common::uint16_t _data)
        {
          __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
        }
    };



    class Port32Bit : public Port
      {
        public:
          Port32Bit(GenOS::common::uint16_t portnumber);
          ~Port32Bit();

          virtual GenOS::common::uint32_t Read();
          virtual void Write(GenOS::common::uint32_t data);

        protected:
          static inline GenOS::common::uint32_t Read32(GenOS::common::uint16_t _port)
          {
            GenOS::common::uint32_t result;
            __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
            return result;
          }

          static inline void Write32(GenOS::common::uint16_t _port, GenOS::common::uint32_t _data)
          {
            __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
          }
      };

  }
}


#endif
