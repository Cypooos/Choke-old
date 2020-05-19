#ifndef __GENOS__GAME__GAMEMANAGER_H
#define __GENOS__GAME__GAMEMANAGER_H

#include <common/types.h>
#include <common/includer.h>

namespace GenOS
{
  namespace game
  {
    class GameManager :
    {

    public:
      void Draw(common::string key);

      void LoadLevel(common::string key);

    };

  }
}
#endif
