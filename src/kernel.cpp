#include <common/types.h>
#include <common/includer.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <textgui/tgm.h>
#include <textgui/desktop.h>
#include <multitasking.h>
#include <memorymanagement.h>

using namespace GenOS;
using namespace GenOS::common;
using namespace GenOS::drivers;
using namespace GenOS::hardwarecommunication;
using namespace GenOS::gui;
using namespace GenOS::textgui;

static int strToHex(char* text);


void printf(char* str)
{
  static uint16_t* VideoMemory = (uint16_t*)0xb8000;

  static uint8_t x=0,y=0;

  for(int i = 0; str[i] != '\0'; ++i)
  {
    switch(str[i])
    {
      case '\n':
        x = 0;
        y++;
        break;
      default:
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
        x++;
        break;
    }

    if(x >= 80)
    {
      x = 0;
      y++;
    }

    if(y >= 25)
    {
      for(y = 0; y < 25; y++)
        for(x = 0; x < 80; x++)
          VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
      x = 0;
      y = 0;
    }
  }
}

void printc(char c)
{
  char* foo = "0";
  foo[0] = c;
  printf(foo);
}


void foo(char c){}
void foo(){}
void foo(char* c){}

void printfHex(uint8_t key)
{
  char* foo = "00";
  char* hex = "0123456789ABCDEF";
  foo[0] = hex[(key >> 4) & 0xF];
  foo[1] = hex[key & 0xF];
  printf(foo);
}




class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
  void OnKeyDown(char c)
  {
    char* foo = " ";
    foo[0] = c;
    printf(foo);
  }
};

class MouseToConsole : public MouseEventHandler
{
  int8_t x, y;
public:

  MouseToConsole()
  {
    uint16_t* VideoMemory = (uint16_t*)0xb8000;
    x = 40;
    y = 12;
    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
              | (VideoMemory[80*y+x] & 0xF000) >> 4
              | (VideoMemory[80*y+x] & 0x00FF);
  }

  virtual void OnMouseMove(int xoffset, int yoffset)
  {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
              | (VideoMemory[80*y+x] & 0xF000) >> 4
              | (VideoMemory[80*y+x] & 0x00FF);

    x += xoffset;
    if(x >= 80) x = 79;
    if(x < 0) x = 0;
    y += yoffset;
    if(y >= 25) y = 24;
    if(y < 0) y = 0;

    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
              | (VideoMemory[80*y+x] & 0xF000) >> 4
              | (VideoMemory[80*y+x] & 0x00FF);
  }

};



void taskA()
{
  while(true)
    printf("AAAAAAAAAAAA");
}


void taskB()
{
  while(true)
    printf("B");
}






typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
  for(constructor* i = &start_ctors; i != &end_ctors; i++)
    (*i)();
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
  printf("GenOS have boot.\n");

  GlobalDescriptorTable gdt;

  uint32_t* memupper = (uint32_t*)(((size_t)multiboot_structure)+8);
  size_t heap = 10*1024*1024; // 10MegaByte in case GRUB load stuff behind our os
  MemoryManager memoryManager(heap,(*memupper)*1024 - heap - 10*1024);

  printf("Heap: 0x");
  printfHex((heap >> 24) & 0xFF);
  printfHex((heap >> 16) & 0xFF);
  printfHex((heap >> 8) & 0xFF);
  printfHex((heap) & 0xFF);
  printf("\n");

  void* allocated = memoryManager.malloc(1024);

  printf("Allocated: 0x");
  printfHex(((size_t)allocated >> 24) & 0xFF);
  printfHex(((size_t)allocated >> 16) & 0xFF);
  printfHex(((size_t)allocated >> 8) & 0xFF);
  printfHex(((size_t)allocated) & 0xFF);


  TaskManager taskManager;
  /*Task task1(&gdt, taskA);
  Task task2(&gdt, taskB);
  taskManager.AddTask(&task1);
  taskManager.AddTask(&task2);*/

  InterruptManager interrupts(0x20, &gdt, &taskManager);

  printf("[GenOS] >> Setting up drivers\n");

  TextGraphicsManager tgm;


  TextDesktop desktop(&tgm);

  // Desktop desktop(320,200,0x00,0x00,0xA8);

  DriverManager drvManager;

    //MouseToConsole mousehandler;
    MouseDriver mouse(&interrupts, &desktop); // Mouse is set to desktop, because he is the higest wigdet
    drvManager.AddDriver(&mouse);

    //PrintfKeyboardEventHandler kbhandler;
    //KeyboardDriver keyboard(&interrupts, &kbhandler);
    KeyboardDriver keyboard(&interrupts, &desktop);
    drvManager.AddDriver(&keyboard);

    PeripheralComponentInterconnectController PCIController;
    PCIController.SelectDrivers(&drvManager, &interrupts);

    // VideoGraphicsArray vga;

  printf("[GenOS] >> Activating drivers\n");
  drvManager.ActivateAll();

  printf("[GenOS] >> Setting graphics mode\n");

  //tgm.write("> Kernel tgm loaded.",0,0);


  // vga.SetMode(320,200,8);

  //Window win1(&desktop, 10,10,50,50,0xA8,0x00,0x00);
  //desktop.AddChild(&win1);
  //Window win2(&desktop, 40,100,100,100,0x00,0xA8,0x00);
  //desktop.AddChild(&win2);

  interrupts.Activate();

  //tgm.clearScreen();

  //desktop.Draw();

  while(1)
  {
    //desktop.Draw(&vga);
  };
}
