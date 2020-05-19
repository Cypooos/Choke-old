#include <textgui/desktop.h>
using namespace GenOS::common;
using namespace GenOS::textgui;
using namespace GenOS;

void printf(char* str);
void printfHex(uint8_t);


TextDesktop::TextDesktop(common::TextGraphicsContext* graphicscontext)
{
  fileselect = ":logo.txt";
  path = "C:";

  Folder root;
  root.path = "C:";
  root.elementspaths[0] = "/CHOKE";
  root.elementspaths[1] = "/SMS";
  root.elementspaths[2] = ":logo.txt";
  folders[0] = root;

  ReadFile flogo;
  flogo.path = "C:";
  flogo.name = ":logo.txt";
  flogo.content = "$08----------------------------------------------------------------$!\n$0B       .d8888b.                     $0C.d88888b.   $0E.d8888b.  \n$0B      d88P  Y88b                   $0Cd88P\" \"Y88b $0Ed88P  Y88b \n$03      888    888                   $0C888     888 $0EY88b.      \n$03      888         .d88b.  88888b.  $0C888     888  $0E\"Y888b.   \n$03      888  88888 d8P  Y8b 888 \"88b $0C888     888     $0E\"Y88b. \n$02      888    888 88888888 888  888 $0C888     888       $0E\"888 \n$02      Y88b  d88P Y8b.     888  888 $0CY88b. .d88P $0EY88b  d88P \n$0A       \"Y8888P88  \"Y8888  888  888  $0C\"Y88888P\"   $0E\"Y8888P\"\n$08----------------------------------------------------------------$!\n\n      $30Gen$C0O$E0S$!: $30Gen$03erative$!\n                $C0O$0Cperating$!\n                 $E0S$0Eystem$!\n\n\n        $09By <discursif/> since 2020.$!\n\nMade by a 2-year old.";
  readFiles[0] = flogo;

  Folder choke;
  choke.path = "C:/CHOKE";
  choke.elementspaths[0] = "RETURN";
  choke.elementspaths[1] = " ";
  choke.elementspaths[2] = "/OPTIONS";
  choke.elementspaths[3] = "/ABOUT";
  choke.elementspaths[4] = "/LEVELS";
  choke.elementspaths[5] = " ";
  choke.elementspaths[6] = ":logo.txt";
  choke.elementspaths[7] = " ";
  choke.elementspaths[8] = ">PLAY.EXE";
  folders[1] = choke;

  ReadFile fchoke_logo;
  fchoke_logo.path = "C:/CHOKE";
  fchoke_logo.name = ":logo.txt";
  fchoke_logo.content = "             _____\n            /     \\\n           / [] [] \\\n           \\   ^   /\n            ( ||| )\n             \\|||/\n\n   CHOKE.  \nThe game that sound like a 'you' problem.";
  readFiles[1] = fchoke_logo;



  Folder sms;
  sms.path = "C:/SMS";
  sms.elementspaths[0] = "RETURN";
  sms.elementspaths[1] = " ";
  sms.elementspaths[2] = "/LOGS";
  sms.elementspaths[3] = ">SMS.EXE";
  folders[2] = sms;

  Folder sms_logs;
  sms_logs.path = "C:/SMS/LOGS";
  sms_logs.elementspaths[0] = "RETURN";
  sms_logs.elementspaths[1] = " ";
  sms_logs.elementspaths[2] = "NO LOGS YET";
  folders[3] = sms_logs;

  Folder choke_options;
  choke_options.path = "C:/CHOKE/OPTIONS";
  choke_options.elementspaths[0] = "RETURN";
  choke_options.elementspaths[1] = " ";
  choke_options.elementspaths[2] = "-SENSIBILITY";
  choke_options.elementspaths[3] = "-TRANSITIONS";
  choke_options.elementspaths[4] = "-HARDMODE";
  choke_options.elementspaths[5] = "-SOMETHING";
  choke_options.elementspaths[6] = "-SOMETHING2";
  folders[4] = choke_options;

  Folder choke_about;
  choke_about.path = "C:/CHOKE/ABOUT";
  choke_about.elementspaths[0] = "RETURN";
  choke_about.elementspaths[1] = " ";
  choke_about.elementspaths[2] = ":CREATORS";
  choke_about.elementspaths[3] = ":WARNINGS";
  choke_about.elementspaths[4] = ":LISCENCE";
  choke_about.elementspaths[5] = ":CREDITS";
  choke_about.elementspaths[6] = " ";
  choke_about.elementspaths[7] = "BY DISCURSIF";
  folders[5] = choke_about;

  Folder choke_levels;
  choke_levels.path = "C:/CHOKE/LEVELS";
  choke_levels.elementspaths[0] = "RETURN";
  choke_levels.elementspaths[1] = " ";
  choke_levels.elementspaths[2] = ">LVL1.EXE";
  choke_levels.elementspaths[3] = "LOCKED";
  choke_levels.elementspaths[4] = "LOCKED";
  choke_levels.elementspaths[5] = "LOCKED";
  choke_levels.elementspaths[6] = "LOCKED";
  folders[6] = choke_levels;

  menuCursor = 2;

  // GETIING FOLDER
  for (int x = 0;x < 100;x++){
    if(folders[x].path == path)
    {
      activeFolder=folders[x];
      break;
    }
  }

  // GETIING PRINTLEFT FILE CONTENT IF EXIST
  for (int x = 0;x < 100;x++){
    if(readFiles[x].path == path && readFiles[x].name == fileselect)
    {
      printLeft=readFiles[x].content;
      break;
    }
  }

  uint16_t* VideoMemory = (uint16_t*)0xb8000;
  gc = graphicscontext;
  gc->invert(mouseX,mouseY);
  debugInterrupt = "FIRSTCALL";
  sensivity = 12; // higer = less movement
  mouseX = 40*sensivity;
  mouseY = 12*sensivity;
  scroll = 0;
  //Draw();
}

TextDesktop::~TextDesktop(){}

void TextDesktop::Draw()
{

  // BASIC TEMPLATE
  gc->clearScreen();
  gc->write("$3FChoke | By $35<discursif/>$3F                        GenOS created by Cyprien Bourotte",0,0);
  gc->write("--------------------------------------------------------------------------------",0,1);
  gc->write("|",58,2);//gc->write("|",79,2);
  gc->write("--------------------------------------------------------------------------------",0,3);
  for (int x = 4;x <25;x++)
  {gc->write("|",15,x);gc->write("|",0,x);}

  // DOWN SECTION
  gc->write("$50GenOS dev0.2b",68,24);
  gc->write("$50int:",0,24);
  gc->write(debugInterrupt,4,24,0x5000);

  // PRINT PATH
  gc->write(path,1,2,0x0700);

  if(fileselect == "RETURN"){gc->write("Go back to C:",60,2,0x0700);}
  else{
    gc->write(fileselect,67,2,0x0700);
    if(fileselect[0] == '/'){gc->write("Go to: ",60,2,0x0700);}
    else if(fileselect[0] == '>'){gc->write("launch: ",60,2,0x0700);}
    else if(fileselect[0] == ':'){gc->write("open:   ",60,2,0x0700);}
    else if(fileselect[0] == '-'){gc->write("change: ",60,2,0x0700);}
  }

  for (int x = scroll; x < scroll+20;x++)
  {
    if(activeFolder.elementspaths[x]){
      int inked = 0x0F00;
      if (activeFolder.elementspaths[x] == " "){continue;}
      switch (activeFolder.elementspaths[x][0])
      {
        case '/':
          inked = 0x0300;break;
        case '-':
          inked = 0x0400;break;
        case '>':
          inked = 0x0500;break;
        default:
          if(activeFolder.elementspaths[x]== "RETURN")
            {inked = 0x0200;break;}
      }
      gc->write("            ",2,x-scroll+4,inked);
      gc->write(activeFolder.elementspaths[x],2,x-scroll+4,inked);
      if (menuCursor == x-scroll){
        for (int y = 2;y < 14;y++){gc->invert(y,x-scroll+4);}
      }
    }
    else{break;}
  }

  gc->write(printLeft,16,4);

  gc->invert(mouseX/sensivity,mouseY/sensivity);// mouse, last
}

void TextDesktop::OnKeyDown(common::string key)
{
  debugInterrupt = "KEYDOWN";
  bool action = false;
  int tmpmenu_cursor = menuCursor;
  if(StrManager::strCompare((char*)key,"RETURN") || StrManager::strCompare((char*)key,"SPACE")) { Select(menuCursor); }
  else if(StrManager::strCompare((char*)key,"UP")) {
    int x;
    for (x = tmpmenu_cursor-1;activeFolder.elementspaths[x] == " ";x--){}
    tmpmenu_cursor = x;
    action = true;
  }
  else if(StrManager::strCompare((char*)key,"DOWN")) {
    int x;
    for (x = tmpmenu_cursor+1;activeFolder.elementspaths[x] == " ";x++){}
    tmpmenu_cursor = x;
    action = true;
  }
  if(action)
  {
    if(tmpmenu_cursor <0){
      int x;
      for (x = 0;activeFolder.elementspaths[x];x++){}
      tmpmenu_cursor = x-1;
    }
    else if(!activeFolder.elementspaths[tmpmenu_cursor]){tmpmenu_cursor = 0;}
    Select(tmpmenu_cursor);
  }
  Draw();
}

void TextDesktop::OnMouseDown(GenOS::common::uint8_t button)
{
  debugInterrupt = "MOUSEDOWN";
  Select(scroll+mouseY/sensivity-4);
  Draw();
}

void TextDesktop::Select(GenOS::common::uint8_t element)
{
  fileselect = "";
  if(activeFolder.elementspaths[element] && activeFolder.elementspaths[element] != " ")
  {
    fileselect = activeFolder.elementspaths[element];
    // reload printLeft
    for (int x = 0;x < 100;x++){
      if( StrManager::strCompare(readFiles[x].path,path) && StrManager::strCompare(readFiles[x].name,fileselect))
      {
        printLeft=readFiles[x].content;
        break;
      }
    }
    if (menuCursor == element)
    {
      menuCursor = 255;
      debugInterrupt = "SELECT";
      //printLeft = "";
      reloadPath();
    }else{menuCursor = element;}
  }
  else{menuCursor=255;}
}

void TextDesktop::reloadPath()
{
  char* oldpath = path;
  if (fileselect == "RETURN")
  {
    printLeft = "";
    path = "C:";//StrManager::splitallminlast(activeFolder.path,'/');
  } else if (fileselect[0] == '/')
  {
    path = StrManager::glue(path,fileselect);
    printLeft = "";
  }
  bool found = false;
  for (int x = 0;x < 100;x++){
    if(StrManager::strCompare(folders[x].path,path))
    {
      activeFolder=folders[x];
      found=true;
      break;
    }
  }
  if (!found){path = oldpath;menuCursor = 255;}
  fileselect = "";
}


void TextDesktop::OnMouseUp(GenOS::common::uint8_t button)
{
  debugInterrupt = "MOUSEUP";
  Draw();
}

void TextDesktop::OnMouseMove(int xoffset, int yoffset)
{
  debugInterrupt = "MOUSEMOVE";
  mouseX += xoffset;
  if(mouseX/sensivity > 100) mouseX = 0;
  if(mouseX/sensivity > 79) mouseX = 79*sensivity;
  mouseY += yoffset;
  if(mouseY/sensivity > 50) mouseY = 0;
  if(mouseY/sensivity > 24) mouseY = 24*sensivity;
  Draw();

}
