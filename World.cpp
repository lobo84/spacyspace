#include "World.h"
#include "Vector2D.h"
#include <functional>
#include <memory>
#include <cstdlib>

World::World(int width, int height) : mWidth(width),
				      mHeight(height),
				      mState(GameState::RUNNING),
				      mShip{Vector2D<float>(50,height-150),
                                            Vector2D<float>(0,0),50, 50, 1}
{
    Vector2D<float> pos(40, 20);
    spawnEnemies();
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

void World::createFormation(Vector2D<float> pos,
			    int rows,
			    int cols,
			    int width,
			    int height) {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      auto x = pos.getX() + row * width;
      auto y = pos.getY() + col * height;
      Vector2D<float> enemyPos(x, y);
      Vector2D<float> dir(0,1);
      auto enemy = new GameObject(enemyPos,dir,width,height,0.1);
      addGameObject(GameObjectType::ENEMY, enemy);
    }
  }
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

bool World::collisionDetect(GameObjects& gs, GameObject& a) {
  for (auto g : gs) {
    bool colision = a.checkCollision(*g);
    if (colision) {
      return true;
    }
  }
  return false;
}

tuple<set<GameObject*>,set<GameObject*>> World::collisionDetect(GameObjects& gs1,
								GameObjects& gs2){
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

void World::resolveCollisions() {
  auto& enemies = getGameObjects(GameObjectType::ENEMY);
  auto collisions = collisionDetect(getGameObjects(GameObjectType::BULLET),
				    enemies);
  auto& collidedBullets = get<0>(collisions);
  for (auto bullet : collidedBullets) {
    removeGameObject(GameObjectType::BULLET, bullet);
  }
  auto& collidedEnemies = get<1>(collisions);
  for (auto enemy : collidedEnemies) {
    removeGameObject(GameObjectType::ENEMY, enemy);
  }
  if (collisionDetect(enemies, mShip)) {
    mState = GameState::GAMEOVER;
  }
}

void World::spawnEnemies() {
  const int count = 4;
  int scenarios[count][4] = {
    {5, 5, 20, 20},
    {2, 2, 20, 20},
    {10, 10, 20, 20},
    {3, 3, 20, 20}
  };
  if (getGameObjects(GameObjectType::ENEMY).size() == 0) {
    int s = rand() % count;
    auto& rows = scenarios[s][0];
    auto& cols = scenarios[s][1];
    auto& width = scenarios[s][2];
    auto& height = scenarios[s][3];
    auto totalWidth = width * cols;
    auto maxWidthPos = mWidth - totalWidth;
    auto xPos = rand() % maxWidthPos;
    createFormation(Vector2D<float>(xPos,10),
		    rows,cols,width,height);
  }
}

void World::update(const Input& input, int elapsedMSec) {
  switch (mState) {
  case GameState::RUNNING:
    updateRunning(input, elapsedMSec);
    break;
  case GameState::GAMEOVER:
    break;
  }
}

void World::updateRunning(const Input& input, int elapsedMSec) {
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
  resolveCollisions();
  spawnEnemies();
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

World::~World() {
  for (auto t = 0; t < static_cast<int>(GameObjectType::COUNT); t++) {
    auto type = static_cast<GameObjectType>(t);
    for (auto g : getGameObjects(type)) {      
      delete g;
    }
  }
}
