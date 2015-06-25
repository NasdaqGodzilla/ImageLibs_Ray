// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#include <ray/game_application.h>
#include <ray/game_scene.h>

#include "terrain.h"
#include "terrain_items.h"
#include "first_person_camera.h"

int main()
{
    try
    {
        ray::Application app;
        if (!app.initialize())
        {
            throw ray::failure("App::initialize() fail");
        }

        ray::GameApplication game;

        game.open();

        game.addFeatures(std::make_shared<ray::WindowFeatures>("Cube World", 1376, 768));
        game.addFeatures(std::make_shared<ray::InputFeatures>());
        game.addFeatures(std::make_shared<ray::PhysicFeatures>());
        game.addFeatures(std::make_shared<ray::RenderFeatures>());

        game.start();

        if (game.openScene("dlc:cube\\scene.map"))
        {
            auto scene = game.findScene("cubes");
            if (scene)
            {
                auto terrain = std::make_shared<Terrain>();
                terrain->addObject(std::make_shared<TerrainGrass>());
                terrain->addObject(std::make_shared<TerrainTree>());
                terrain->addObject(std::make_shared<TerrainClound>());
                terrain->addObject(std::make_shared<TerrainWater>());

                auto terrainObj = std::make_shared<ray::GameObject>();
                terrainObj->addComponent(terrain);
                terrainObj->setParent(scene->getRootObject());
                terrainObj->setActive(true);

                auto player = ray::GameObject::find("first_person_camera");
                player->addComponent(std::make_shared<FirstPersonCamera>());
                player->setActive(true);

                while (!game.isQuitRequest())
                {
                    ray::AppEvent event;
                    while (app.pollEvents(event))
                    {
                        game.sendEvent(event);
                    }

                    game.update();
                }
            }
            else
            {
                throw ray::failure("Scene::find('cubes') fail");
            }
        }
        else
        {
            throw ray::failure("App::openScene('dlc:cube\\scene.map') fail");
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
        std::system("pause");
    }

    return 0;
}