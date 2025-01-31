// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define SFML_STATIC
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <nlohmann/json.hpp>
#include "Box2D\Box2D.h"
#include <iostream>
#include <vector>
#include <string>
#include "Helper.h"
#include "GameObject.h"
#include "Player.h"
#include "Platform.h"
#include "Camera.h"
#include "ComplexPlatform.h"
#include "Snow.h"
#include <fstream>
#include <chrono>

#define SFML_HEIGHT 720
#define SFML_WIDTH 1280
#define PLAYER_X_REL 1.0f
#define PLAYER_Y_REL 0.5f
#define PLAYER_X_ABS 0.f
#define PLAYER_Y_ABS 200.f
#define DEBUG_MODE false
#define USE_REL false
#define PLAT_COLOR sf::Color(100,100,100)
#define CLEAR_COLOR sf::Color(150,150,255)

#define SET_LEFT(width,x)  x - width/2

#define elif else if

#define json nlohmann::json
