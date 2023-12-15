//
// Created by rysan on 29/11/23.
//
#pragma once

#include "engine.h"

class SceneLVL0_5 : public Scene {
public:
    void Load() override;
    void UnLoad() override;
    void Update(const double& dt) override;
    void Render() override;
};


