//
// Created by rysan on 11/12/23.
//

#include "scene_lvl2.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_pursuer_ai.h"
#include <LevelSystem.h>
#include <iostream>

static std::shared_ptr<Entity> player;
double timer;

void SceneLVL2::Load()
{
  std::cout << ">> LVL 2 LOADING <<" << std::endl;

  ls::loadLevelFile("res/lvls/lvl2.txt", float(Engine::getWindowSize().x));
  float tile_size = ls::getTileSize();
  ls::setOffset(sf::Vector2f(0, Engine::getWindowSize().y - (ls::getHeight() * tile_size)));
  sf::Vector2f spawn_offset (tile_size/2, tile_size/2);

  // PLAYER SPAWNING
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + spawn_offset);
    std::cout << "OF: " << ls::getOffset().x << " " << ls::getOffset().y << std::endl;
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(sf::Vector2f(tile_size, tile_size));
    s->getShape().setOrigin(spawn_offset);
    s->getShape().setFillColor(sf::Color::Green);

    player->addComponent<PlayerMoveComponent>(0.1f);
    player->addTag("player");
  }


  // ENEMIES
  {
    auto enemy = makeEntity();
    enemy->setPosition(player->getPosition());
    auto s = enemy->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(sf::Vector2f(tile_size, tile_size));
    s->getShape().setFillColor(sf::Color::Magenta);
    s->getShape().setOrigin(spawn_offset);

    enemy->addComponent<PursuerAIComponent>();
    enemy->addTag("enemy");
  }

  // Collectibles


  setLoaded(true);
  std::cout << " LVL 2 LOADED " << std::endl;
}

void SceneLVL2::UnLoad()
{
  std::cout << ">> LVL 2 UNLOAD << " << std::endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void SceneLVL2::Update(const double &dt)
{
  timer+= dt;
  auto enemy_ai = ents.find("enemy")[0]->get_components<PursuerAIComponent>()[0];
  if(timer > 1 && !enemy_ai->isActive()) enemy_ai->setActive(true);

  if(ls::getTileAt(player->getPosition())==ls::END) Engine::ChangeScene((Scene*)&menu);

  Scene::Update(dt);
}

void SceneLVL2::Render()
{
  ls::render(Engine::GetWindow());
  Scene::Render();
}
