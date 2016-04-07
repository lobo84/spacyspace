#ifndef WORLD_H
#define WORLD_H


#include "Input.h"
#include <vector>
#include "GameObject.h"
#include <tuple>
#include <set>
#include <memory>
using namespace std;

using GameObjects = set<GameObject*>;

class World {
 public:
  World(int width, int height);
  ~World();
  void update(const Input& input, int elapsedMSec);
  GameObject getShip() const;
  const GameObjects& getEnemies() const;
  const GameObjects& getBullets() const;
 private:
  enum class GameObjectType {ENEMY = 0, BULLET, COUNT};
  enum class GameState {RUNNING, GAMEOVER};
  GameState mState;
  GameObjects mGameObjects[static_cast<int>(GameObjectType::COUNT)];
  void addGameObject(GameObjectType type, GameObject* gameObject);
  void removeGameObject(GameObjectType type, GameObject* gameObject);
  const GameObjects& getGameObjects(GameObjectType type) const;
  GameObjects& getGameObjects(GameObjectType type);
  void createFormation(Vector2D<float> pos,
		       int rows,
		       int cols,
		       int width,
		       int height);
  void resolveCollisions();
  void spawnEnemies();
  int mWidth;
  int mHeight;
  World();
  GameObject mShip;
  void updateGameObjects(int elapsedMSec);
  void updateRunning(const Input& input, int elapsedMSec);  
  tuple<set<GameObject*>,set<GameObject*>> collisionDetect(GameObjects& gs1, GameObjects& gs2);
  bool collisionDetect(GameObjects& gs, GameObject& a);
};

#endif
