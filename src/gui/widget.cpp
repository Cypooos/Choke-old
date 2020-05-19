#include <gui/widget.h>
using namespace GenOS::common;
using namespace GenOS::gui;


Widget::Widget(Widget* parent, int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int32_t g,int32_t b) : KeyboardEventHandler()
{
  this->parent = parent;
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->r = r;
  this->g = g;
  this->b = b;
  this->focussable = true;
}

Widget::~Widget()
{}



void Widget::GetFocus(Widget* widget)
{
  if(parent !=0)
    parent->GetFocus(widget);
}
// Get position of the widget
void Widget::ModelToScreen(int32_t &x, int32_t &y)
{
  if(parent !=0)
    parent->ModelToScreen(x,y);
  // add offset of parent
  x += this->x;y += this->y;
}
void Widget::Draw(GraphicsContext* gc)
{
  int X = 0;
  int Y = 0;
  ModelToScreen(X,Y);
  gc->FillRectangle(X,Y,w,h, r,g,b);
}
bool Widget::CountainsCoordinate(int32_t x,int32_t y)
{
  return this->x <= x && x < this->x + this->w
    && this->y <= y && y < this->y + this->h;
}


void Widget::OnMouseUp(int32_t x,int32_t y, uint8_t button){}
void Widget::OnMouseDown(int32_t x,int32_t y, uint8_t button)
{
  if(focussable)
    GetFocus(this);// On prend le focus
}
void Widget::OnMouseMove(int32_t oldx,int32_t oldy,int32_t newx,int32_t newy){}

void Widget::OnMouseEnter(int32_t oldx,int32_t oldy,int32_t newx,int32_t newy)
{
}
void Widget::OnMouseLeave(int32_t oldx,int32_t oldy,int32_t newx,int32_t newy)
{
}











CompositeWidget::CompositeWidget(Widget* parent, int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int32_t g,int32_t b) : Widget(parent, x,y,w,h, r,g,b)
{
  focussedChild = 0;
  numChildren =0;
}

CompositeWidget::~CompositeWidget()
{}

void CompositeWidget::GetFocus(Widget* widget)
{
  this->focussedChild = widget;
  if(parent !=0)
    parent->GetFocus(this);
}

// TODO : Securise
bool CompositeWidget::AddChild(Widget* child)
{
  if(numChildren >= 100)
    return false;
  children[numChildren++] = child;
  return true;
}

void CompositeWidget::Draw(GraphicsContext* gc)
{
  Widget::Draw(gc);
  for (int i = numChildren-1; i >= 0; i--)
    children[i]->Draw(gc);
}

void CompositeWidget::OnMouseUp(int32_t x,int32_t y, uint8_t button)
{
  for (int i = 0; i <numChildren; i++)
    if(children[i]->CountainsCoordinate(x-this->x,y-this->y))
      {
        children[i]->OnMouseUp(x-this->x,y-this->y, button);break;
      }

}
void CompositeWidget::OnMouseDown(int32_t x,int32_t y, uint8_t button)
{
  bool find = false;
  for (int i = 0; i <numChildren; i++)
    if(children[i]->CountainsCoordinate(x-this->x,y-this->y))
      {
        find = true;
        children[i]->OnMouseDown(x-this->x,y-this->y, button);break;
      }
}

// TODO: OnMouseLeave & OnMouseEnter
void CompositeWidget::OnMouseMove(int32_t oldx,int32_t oldy,int32_t newx,int32_t newy)
{
  // int firstChild = -1;
  // for (int i = 0; i <numChildren; i++)
  //   if(children[i]->CountainsCoordinate(oldx-this->x,oldy-this->y))
  //     {
  //       firstChild = i;
  //       children[i]->OnMouseMove(oldx-this->x,oldy-this->y,newx-this->x,newy-this->y);
  //       break;
  //     }
  // for (int i = 0; i <numChildren; i++)
  //   if(children[i]->CountainsCoordinate(newx-this->x,newy-this->y))
  //     {
  //       if(firstChild !=i)
  //       {
  //         children[i]->OnMouseEnter(oldx-this->x,oldy-this->y,newx-this->x,newy-this->y);
  //         children[i]->OnMouseMove(oldx-this->x,oldy-this->y,newx-this->x,newy-this->y);
  //       }
  //       break;
  //   }else{
  //       if(firstChild ==i)
  //         {children[i]->OnMouseLeave(oldx-this->x,oldy-this->y,newx-this->x,newy-this->y);
  //         break;}
  //     }

  for (int i = 0; i < numChildren; i++)
  {
    bool first = children[i]->CountainsCoordinate(oldx-this->x,oldy-this->y);
    bool second = children[i]->CountainsCoordinate(newx-this->x,newy-this->y);
    if(first || second) {
      children[i]->OnMouseMove(oldx-this->x,oldy-this->y,newx-this->x,newy-this->y);
      if(first && second)
        break;
      if(first)
        children[i]->OnMouseLeave(oldx-this->x,oldy-this->y,newx-this->x,newy-this->y);
      else
        children[i]->OnMouseEnter(oldx-this->x,oldy-this->y,newx-this->x,newy-this->y);
    }
  }

}

void CompositeWidget::OnMouseEnter(int32_t oldx,int32_t oldy,int32_t newx,int32_t newy)
{
}
void CompositeWidget::OnMouseLeave(int32_t oldx,int32_t oldy,int32_t newx,int32_t newy)
{
}


void CompositeWidget::OnKeyDown(common::string str)
{
  if(focussedChild !=0)
    focussedChild->OnKeyDown(str);
}

void CompositeWidget::OnKeyUp(common::string str)
{
  if(focussedChild !=0)
    focussedChild->OnKeyDown(str);
}
