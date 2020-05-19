#ifndef __GENOS__GDT_H
#define __GENOS__GDT_H

#include <common/types.h>

namespace GenOS
{

  class GlobalDescriptorTable
  {
    public:

      class SegmentDescriptor
      {
        private:
          GenOS::common::uint16_t limit_lo;
          GenOS::common::uint16_t base_lo;
          GenOS::common::uint8_t base_hi;
          GenOS::common::uint8_t type;
          GenOS::common::uint8_t limit_hi;
          GenOS::common::uint8_t base_vhi;

        public:
          SegmentDescriptor(GenOS::common::uint32_t base, GenOS::common::uint32_t limit, GenOS::common::uint8_t type);
          GenOS::common::uint32_t Base();
          GenOS::common::uint32_t Limit();
      } __attribute__((packed));

    private:
      SegmentDescriptor nullSegmentSelector;
      SegmentDescriptor unusedSegmentSelector;
      SegmentDescriptor codeSegmentSelector;
      SegmentDescriptor dataSegmentSelector;

    public:

      GlobalDescriptorTable();
      ~GlobalDescriptorTable();

      GenOS::common::uint16_t CodeSegmentSelector();
      GenOS::common::uint16_t DataSegmentSelector();
  };

}

#endif
