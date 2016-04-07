#include "World.h"
#include "Vector2D.h"
#include <functional>
#include <memory>



World::World(int width, int height) : mWidth(width),
				      mHeight(height),
				      mShip{Vector2D<float>(50,height-150), Vector2D<float>(0,0),50, 50, 1}
{
  for (int i = 0; i < 10; ++i) {
    auto pos = Vector2D<float>(i * 40, 20);
    auto dir = Vector2D<float>(0,1);
    addGameObject(GameObjectType::ENEMY, new GameObject(pos,dir, 50, 50,0.1));
  }
}

void World::addGameObject(GameObjectType type, GameObject* gameObject) {
  mGameObjects[static_cast<int>(type)].insert(gameObject);
}

void World::removeGameObject(GameObjectType type, GameObject* gameObject) {
  mGameObjects[static_cast<int>(type)].erase(gameObject);
  delete gameObject;
}

const GameObjects& World::getGameObjects(GameObjectType type) const {
  return mGameObjects[static_cast<int>(type)];
}

GameObjects& World::getGameObjects(GameObjectType type) {
  return mGameObjects[static_cast<int>(type)];
}

void World::updateGameObjects(int elapsedMSec) {
  for (auto t = 0; t < static_cast<int>(GameObjectType::COUNT); t++) {
    auto type = static_cast<GameObjectType>(t);
    for (auto g : getGameObjects(type)) {
      g->move(elapsedMSec);
      // remove if outside screen
      if (!g->isInside(0,0,mWidth,mHeight)) {
	removeGameObject(type, g);
      }
    }
  }
}

tuple<set<GameObject*>,set<GameObject*>> World::collisionDetect(GameObjects& gs1, GameObjects& gs2){
  tuple<set<GameObject*>,set<GameObject*>> gSets;
  for (auto g1 : gs1) {
    for (auto g2 : gs2) {
      if (g1->checkCollision(*g2)) {
	get<0>(gSets).insert(g1);
	get<1>(gSets).insert(g2);
      }
    }
  }  
  return gSets;
}

void World::update(const Input& input, int elapsedMSec) {
  Vector2D<float> dir {0.0, 0.0};
  if (input.getUp()) {
    dir.setY(-1.0);
  }
  if (input.getDown()) {
    dir.setY(1.0);
  }
  if (input.getLeft()) {
    dir.setX(-1.0);
  }
  if (input.getRight()) {
    dir.setX(1.0);
  }
  if (input.getSpace()) {
    auto pos = Vector2D<float>(mShip.getPos().getX(), mShip.getPos().getY());
    auto dir = Vector2D<float>(0.0,-1.0);
    addGameObject(GameObjectType::BULLET, new GameObject(pos,dir,5,10,1.0));
  }
  mShip.setDir(dir);
  mShip.move(elapsedMSec);
  updateGameObjects(elapsedMSec);
  auto collisions = collisionDetect(getGameObjects(GameObjectType::BULLET),
				    getGameObjects(GameObjectType::ENEMY));
  auto& collidedBullets = get<0>(collisions);
  for (auto bullet : collidedBullets) {
    removeGameObject(GameObjectType::BULLET, bullet);
  }
  auto& collidedEnemies = get<1>(collisions);
  for (auto enemy : collidedEnemies) {
    removeGameObject(GameObjectType::ENEMY, enemy);
  }
}

const GameObjects& World::getEnemies() const {
  return getGameObjects(GameObjectType::ENEMY);
}

const GameObjects& World::getBullets() const {
  return getGameObjects(GameObjectType::BULLET);
}

GameObject World::getShip() const {
  return mShip;
}
