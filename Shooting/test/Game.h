#pragma once
#include "DxLib.h"
#include "Input.h"
#include "Game.h"
#include "Cube.h"
#include "Camera.h"
#include"Player.h"
#include <vector>

class Game
{
public:
    Game();
    void Update();
    bool CheckGoNext() const { return m_goNext; }
    float GetOrbitDist() const { return m_OrbitDist; }

private:
    bool   m_initialized = false;
    bool   m_goNext = false;

    Player m_player;
    Camera m_camera;
    float  m_OrbitDist = 0.0f;
	std::vector<Cube> m_cubes; // 将来的に複数のキューブを管理するためのコンテナ

};
