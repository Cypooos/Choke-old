#ifndef __GENOS__COMMON__INCLUDER_H
#define __GENOS__COMMON__INCLUDER_H

#include <common/types.h>

namespace GenOS
{
  namespace common
  {
    class Converter {
    public:
      static int strToHex(char* text);

    private:
     // Disallow creating an instance of this object
     Converter(){}
     ~Converter(){}
   };

   class StrManager {
   public:
     static char* splitlast(char* text,char finder);
     static char* glue(char* textA, char* textB);
     static bool strCompare(char* textA, char* textB);
     static char* splitallminlast(char* text,char finder);


   private:
    // Disallow creating an instance of this object
    StrManager(){}
    ~StrManager(){}
  };
  }
}
#endif
