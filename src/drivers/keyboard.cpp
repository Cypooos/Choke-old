
#include <drivers/keyboard.h>

using namespace GenOS::common;
using namespace GenOS::drivers;
using namespace GenOS::hardwarecommunication;

void printf(char*);
void printfHex(uint8_t);
KeyboardEventHandler::KeyboardEventHandler()
{
}

void KeyboardEventHandler::OnKeyDown(common::string)
{
}

void KeyboardEventHandler::OnKeyUp(common::string)
{
}





KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler)
: InterruptHandler(manager, 0x21),
dataport(0x60),
commandport(0x64)
{
  this->handler = handler;
}

KeyboardDriver::~KeyboardDriver()
{
}

//void printf(char*);
//void printfHex(uint8_t);

void KeyboardDriver::Activate()
{
  while(commandport.Read() & 0x1)
    dataport.Read();
  commandport.Write(0xae); // activate interrupts
  commandport.Write(0x20); // command 0x20 = read controller command byte
  uint8_t status = (dataport.Read() | 1) & ~0x10;
  commandport.Write(0x60); // command 0x60 = set controller command byte
  dataport.Write(status);
  dataport.Write(0xf4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
  uint8_t key = dataport.Read();

  if(handler == 0)
    return esp;

  if(key < 0x80)
  {
    switch(key)
    {
      // If you want to adapt to your language, please don't change this section.
      // Instead, go to the handler and change whitch input do what. -> game.cpp
      // The desktop hendler should be universal (it use only the arrow and enter / space)
      case 0x29: handler->OnKeyDown("POWER"); break;
      case 0x02: handler->OnKeyDown("1"); break;
      case 0x03: handler->OnKeyDown("2"); break;
      case 0x04: handler->OnKeyDown("3"); break;
      case 0x05: handler->OnKeyDown("4"); break;
      case 0x06: handler->OnKeyDown("5"); break;
      case 0x07: handler->OnKeyDown("6"); break;
      case 0x08: handler->OnKeyDown("7"); break;
      case 0x09: handler->OnKeyDown("8"); break;
      case 0x0A: handler->OnKeyDown("9"); break;
      case 0x0B: handler->OnKeyDown("0"); break;
      case 0x0C: handler->OnKeyDown("DEGREE"); break;
      case 0x0D: handler->OnKeyDown("PLUS"); break;
      case 0x0E: handler->OnKeyDown("SUPR"); break;

      case 0x0F: handler->OnKeyDown("TAB"); break;
      case 0x10: handler->OnKeyDown("A"); break;
      case 0x11: handler->OnKeyDown("Z"); break;
      case 0x12: handler->OnKeyDown("E"); break;
      case 0x13: handler->OnKeyDown("R"); break;
      case 0x14: handler->OnKeyDown("T"); break;
      case 0x15: handler->OnKeyDown("Y"); break;
      case 0x16: handler->OnKeyDown("U"); break;
      case 0x17: handler->OnKeyDown("I"); break;
      case 0x18: handler->OnKeyDown("O"); break;
      case 0x19: handler->OnKeyDown("P"); break;
      case 0x1A: handler->OnKeyDown("POWER"); break;
      case 0x1B: handler->OnKeyDown("DOLLARS"); break;

      case 0x1C: handler->OnKeyDown("RETURN"); break;

      case 0x1E: handler->OnKeyDown("Q"); break;
      case 0x1F: handler->OnKeyDown("S"); break;
      case 0x20: handler->OnKeyDown("D"); break;
      case 0x21: handler->OnKeyDown("F"); break;
      case 0x22: handler->OnKeyDown("G"); break;
      case 0x23: handler->OnKeyDown("H"); break;
      case 0x24: handler->OnKeyDown("J"); break;
      case 0x25: handler->OnKeyDown("K"); break;
      case 0x26: handler->OnKeyDown("L"); break;
      case 0x27: handler->OnKeyDown("M"); break;
      case 0x28: handler->OnKeyDown("POURCENT"); break;

      case 0x2A: handler->OnKeyDown("LFTSHIFT"); break;
      case 0x2B: handler->OnKeyDown("CODE"); break;
      case 0x2C: handler->OnKeyDown("W"); break;
      case 0x2D: handler->OnKeyDown("X"); break;
      case 0x2E: handler->OnKeyDown("C"); break;
      case 0x2F: handler->OnKeyDown("V"); break;
      case 0x30: handler->OnKeyDown("B"); break;
      case 0x31: handler->OnKeyDown("N"); break;
      case 0x32: handler->OnKeyDown("QUESTION"); break;
      case 0x33: handler->OnKeyDown("POINT"); break;
      case 0x34: handler->OnKeyDown("SLASH"); break;
      case 0x35: handler->OnKeyDown("EXCLAM"); break;
      case 0x36: handler->OnKeyDown("RGTSHIFT"); break;

      case 0x1D: handler->OnKeyDown("CTRL"); break;
      case 0x5B: handler->OnKeyDown("LFTWIN"); break;
      case 0x38: handler->OnKeyDown("ALT"); break;
      case 0x39: handler->OnKeyDown("SPACE"); break;
      case 0x5C: handler->OnKeyDown("RGTWIN"); break;

      case 0x4B: handler->OnKeyDown("LEFT"); break;
      case 0x4D: handler->OnKeyDown("RIGTH"); break;
      case 0x48: handler->OnKeyDown("UP"); break;
      case 0x50: handler->OnKeyDown("DOWN"); break;

      case 0x3B: handler->OnKeyDown("F1"); break;
      case 0x3C: handler->OnKeyDown("F2"); break;
      case 0x3D: handler->OnKeyDown("F3"); break;
      case 0x3E: handler->OnKeyDown("F4"); break;
      case 0x3F: handler->OnKeyDown("F5"); break;
      case 0x40: handler->OnKeyDown("F6"); break;
      case 0x41: handler->OnKeyDown("F7"); break;
      case 0x42: handler->OnKeyDown("F8"); break;
      case 0x43: handler->OnKeyDown("F9"); break;
      case 0x44: handler->OnKeyDown("F10"); break;
      case 0x57: handler->OnKeyDown("F11"); break;
      case 0x58: handler->OnKeyDown("F12"); break;


      case 0x47: handler->OnKeyDown("NUM7"); break;
      //case 0x48: handler->OnKeyDown("NUM8"); break;
      case 0x49: handler->OnKeyDown("NUM9"); break;
      //case 0x4B: handler->OnKeyDown("NUM4"); break;
      case 0x4C: handler->OnKeyDown("NUM5"); break;
      //case 0x4D: handler->OnKeyDown("NUM6"); break;
      case 0x4F: handler->OnKeyDown("NUM1"); break;
      //case 0x50: handler->OnKeyDown("NUM2"); break;
      case 0x51: handler->OnKeyDown("NUM3"); break;
      case 0x52: handler->OnKeyDown("NUM0"); break;

      default:
      {
        //printf("KEYBOARD 0x");
        //printfHex(key);
        break;
      }
    }
  }
  return esp;
}
