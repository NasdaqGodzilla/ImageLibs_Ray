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
#include <ray/game_scene.h>
#include <ray/game_server.h>
#include <ray/game_component.h>
#include <ray/rtti_factory.h>

_NAME_BEGIN

__ImplementSubClass(GameScene, GameListener, "GameScene")

std::uint32_t GameScene::_instanceCount = 0;

GameScene::Setting::Setting() noexcept
	: gravity(0.0f, 9.81f, 0.0f)
	, length(1.0f)
	, mass(1000.0f)
	, speed(10.0f)
	, skinWidth(0.0001f)
{
	aabb.min = Vector3(-1000, -1000, -1000);
	aabb.max = Vector3(1000, 1000, 1000);
}

GameScene::RootObject::RootObject(GameScene* scene) noexcept
	: _scene(scene)
{
}

GameScene::RootObject::~RootObject() noexcept
{
}

GameServer*
GameScene::RootObject::getGameServer() noexcept
{
	return _scene->getGameServer();
}

GameScene*
GameScene::RootObject::getGameScene() noexcept
{
	return _scene;
}

GameScene::GameScene() noexcept
	: _gameServer(nullptr)
	, _instanceID(++_instanceCount)
{	
}

GameScene::GameScene(const std::string& name) noexcept
	: _gameServer(nullptr)
{
	this->setName(name);
}

GameScene::~GameScene() noexcept
{
	this->setActive(false);
}

void
GameScene::setActive(bool active) except
{
	if (!_root)
		_root = std::make_unique<RootObject>(this);
	if (_root)
		_root->setActive(active);
}

bool
GameScene::getActive() const noexcept
{
	if (_root)
		_root->getActive();
	return false;
}

std::uint32_t 
GameScene::getInstanceID() const noexcept
{
	return _instanceID;
}

void
GameScene::setEnvironment(const Setting& setting) noexcept
{
	_setting = setting;
}

const GameScene::Setting&
GameScene::getEnvironment() const noexcept
{
	return _setting;
}

GameObjectPtr
GameScene::getRootObject() noexcept
{
	return _root;
}

void
GameScene::setGameServer(GameServer* server) noexcept
{
	if (_gameServer != server)
	{
		if (_gameServer)
			_gameServer->removeScene(std::dynamic_pointer_cast<GameScene>(this->shared_from_this()));
		
		_gameServer = server;

		if (_gameServer)
			_gameServer->addScene(std::dynamic_pointer_cast<GameScene>(this->shared_from_this()));
	}
}

GameServer*
GameScene::getGameServer() noexcept
{
	return _gameServer;
}

void
GameScene::onMessage(const GameMessage& message) except
{
	auto root = this->getRootObject();
	if (root)
	{
		auto childrens = root->getChildren();
		for (auto& child : childrens)
			child->sendMessage(message);
	}
}

GameObjectPtr
GameScene::instanceObject(iarchive& reader, GameObjectPtr parent) except
{
	std::string name = reader.getCurrentNodeName();
	if (name == "object")
	{
		auto actor = std::make_shared<GameObject>();
		actor->setParent(parent);

		reader.setToFirstChild();

		bool active = false;

		do
		{
			auto key = reader.getCurrentNodeName();
			if (key == "attribute")
			{
				auto attributes = reader.getAttrs();
				for (auto& it : attributes)
				{
					if (it == "name")
					{
						actor->setName(reader.getString(it));
					}
					else if (it == "active")
					{
						active = reader.getBoolean(it);
					}
					else if (it == "position")
					{
						actor->setTranslate(reader.getFloat3(it));
					}
					else if (it == "scale")
					{
						actor->setScale(reader.getFloat3(it));
					}
					else if (it == "lookat")
					{
						actor->setLookAt(reader.getFloat3(it));
					}
					else if (it == "up")
					{
						actor->setUpVector(reader.getFloat3(it));
					}
					else if (it == "rotate")
					{
						float3 value = reader.getFloat3(it);
						actor->setRotate(Quaternion(value.x, value.y, value.z));
					}
					else if (it == "layer")
					{
						actor->setLayer(reader.getInteger(it));
					}
				}
			}
			else if (key == "component")
			{
				auto name = reader.getString("name");
				if (!name.empty())
				{
					auto component = rtti::make_shared<GameComponent>(name);
					if (component)
					{
						reader >> component;
						actor->addComponent(component);
					}
					else
					{
						throw failure("Unknown component name : " + name);
					}
				}
				else
				{
					throw failure("empty component name : " + reader.getCurrentNodePath());
				}
			}
			else if (key == "object")
			{
				instanceObject(reader, actor);
			}
		} while (reader.setToNextChild());

		actor->setActive(active);
		return actor;
	}

	return nullptr;
}

void
GameScene::load(iarchive& reader) except
{
	std::string nodeName;
	nodeName = reader.getCurrentNodeName();
	if (nodeName == "scene")
	{
		reader.setToFirstChild();

		do
		{
			nodeName = reader.getCurrentNodeName();
			if (nodeName == "attribute")
			{
				std::string name = "unknown";
				reader >> make_name(name);

				this->setName(name);
			}
			else if (nodeName == "object")
			{
				instanceObject(reader, this->getRootObject());
			}
		} while (reader.setToNextChild());
	}
}
_NAME_END