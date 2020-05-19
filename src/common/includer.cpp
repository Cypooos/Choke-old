#include <common/includer.h>
using namespace GenOS;
using namespace GenOS::common;

void printf(char* str);
void printc(char c);
void foo();
void foo(char* c);

int Converter::strToHex(char* text)
{
  int end = 0;
  for(int i = 0; text[i] != '\0'; ++i)
  {
    end = end << 4;
    switch(text[i])
    {
      case '0':break;
      case '1':end++;break;
      case '2':end+=2;break;
      case '3':end+=3;break;
      case '4':end+=4;break;
      case '5':end+=5;break;
      case '6':end+=6;break;
      case '7':end+=7;break;
      case '8':end+=8;break;
      case '9':end+=9;break;
      case 'A':end+=10;break;
      case 'B':end+=11;break;
      case 'C':end+=12;break;
      case 'D':end+=13;break;
      case 'E':end+=14;break;
      case 'F':end+=15;break;
    }
  }
  return end ;
};


char* StrManager::splitallminlast(char* text,char finder)
{
  char* ret;
  int ret_count = 0;
  for(int x = sizeof(*text);x>1;x--)
  {
    printf("I__");
  }
  foo();// wtf you need to call a function to work ? wtf man
  return "ok";
}


char* StrManager::splitlast(char* text,char finder)
{
  char* ret;
  int ret_count = 0;
  for(int x =0;text[x] != '\0';x++)
  {
    if(text[x] == finder)
    {
      for (;ret_count!=0;ret_count--)
      {
        ret[ret_count] = 0;
      }
    }
    else {
      ret[ret_count] = text[x];
      ret_count++;
    }
  }
  ret[ret_count+1] = '\0';
  foo();// wtf you need to call a function to work ? wtf man
  return (ret);
}

char* StrManager::glue(char* textA, char* textB)
{
  char* ret = "";
  int ret_x = 0;
  printf(textA);
  for(int xt = 0; textA[xt] != '\0';xt++)  {
    ret[ret_x] = textA[xt];
    ret_x++;
  } // appending textA
  for(int xt = 0; textB[xt] != '\0';xt++)  {ret[ret_x] = textB[xt];ret_x++;} // appending textB
  ret[ret_x] = '\0'; // appending end

  foo();
  return ret;
}


bool StrManager::strCompare(char* textA, char* textB)
{
  int x;
  for (x = 0;textA[x] !='\0';x++)
  {
    if(textA[x] != textB[x]){return false;}
  }
    foo();
  return textA[x] == textB[x];
}
