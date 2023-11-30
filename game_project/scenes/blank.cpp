//
// Created by rysan on 29/11/23.
//

#include "blank.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_actor_movement.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

static std::shared_ptr<Entity> player;

void Blank::Load() {
  std::cout << ">> BLANK CANVAS LOADING <<" << std::endl;

  // Importing Level from file
  ls::loadLevelFile("res/blank_level.txt", 40.f);
  ls::setOffset(sf::Vector2f(0, Engine::getWindowSize().y - (ls::getHeight() * 40.f)));

  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(sf::Vector2ul(10,10)) + ls::getOffset());
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(sf::Vector2f(40.f, 40.f));
    s->getShape().setFillColor(sf::Color::Green);
    s->getShape().setOrigin(sf::Vector2f (20.f,20.f));

    player->addComponent<PlayerMoveComponent>();
    player->get_components<PlayerMoveComponent>()[0]->setSpeed(0.4f);
  }

  setLoaded(true);
  std::cout <<">> BLANK CANVAS LOADED <<" << std::endl;
}

void Blank::UnLoad() {
  std::cout << ">> BLANK CANVAS UNLOAD <<" << std::endl;
  // REMOVE PLAYER OR ANYTHING IN THE CANVAS
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Blank::Update(const double& dt) {
  Scene::Update(dt);
}

void Blank::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}