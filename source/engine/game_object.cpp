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
#include <ray/game_object.h>
#include <ray/game_object_manager.h>
#include <ray/game_component.h>

_NAME_BEGIN

__ImplementSubClass(GameObject, rtti::Interface, "Object")

GameObject::GameObject() noexcept
	: _active(false)
	, _layer(0)
	, _needUpdates(true)
	, _scaling(Vector3::One)
	, _translate(Vector3::Zero)
	, _quat(0, 0, 0, 1)
	, _euler(Vector3::Zero)
	, _right(Vector3::Right)
	, _up(Vector3::Up)
	, _forward(Vector3::Forward)
{
	GameObjectManager::instance()->_instanceObject(this, _instanceID);
}

GameObject::~GameObject() noexcept
{
	this->cleanupChildren();
	this->cleanupComponents();

	GameObjectManager::instance()->_unsetObject(this);
}

void
GameObject::setName(const std::string& name) noexcept
{
	_name = name;
}

const std::string&
GameObject::getName() const noexcept
{
	return _name;
}

void
GameObject::setActive(bool active) except
{
	if (_active != active)
	{
		GameObjectManager::instance()->_activeObject(this, active);

		for (auto& it : _components)
		{
			if (active)
			{
				if (it->getActive())
					it->onActivate();
			}
			else
			{
				if (it->getActive())
					it->onDeactivate();
			}
		}

		_active = active;
	}
}

void 
GameObject::setActiveUpwards(bool active) except
{
	if (_active != active)
	{
		for (auto& it : _components)
		{
			if (active)
			{
				if (it->getActive())
					it->onActivate();
			}
			else
			{
				if (it->getActive())
					it->onDeactivate();
			}
		}

		auto parent = this->getParent();
		if (parent)
			parent->setActiveUpwards(active);

		_active = active;
	}
}

void 
GameObject::setActiveDownwards(bool active) except
{
	if (_active != active)
	{
		for (auto& it : _components)
		{
			if (active)
			{
				if (it->getActive())
					it->onActivate();
			}
			else
			{
				if (it->getActive())
					it->onDeactivate();
			}
		}

		for (auto& it : _children)
			it->setActiveDownwards(true);

		_active = active;
	}
}

bool
GameObject::getActive() const noexcept
{
	return _active;
}

void
GameObject::setLayer(std::uint8_t layer) noexcept
{
	if (_layer != layer)
	{
		for (auto& it : _components)
		{
			if (it->getActive())
				it->onLayerChangeBefore();
		}

		_layer = layer;

		for (auto& it : _components)
		{
			if (it->getActive())
				it->onLayerChangeAfter();
		}
	}
}

std::uint8_t
GameObject::getLayer() const noexcept
{
	return _layer;
}

std::uint32_t 
GameObject::getInstanceID() const noexcept
{
	return _instanceID;
}

void
GameObject::setParent(GameObjectPtr parent) noexcept
{
	assert(this != parent.get());

	auto _weak = _parent.lock();
	if (_weak != parent)
	{
		for (auto& it : _components)
			it->onParentChangeBefore();

		if (_weak)
		{
			auto it = _weak->_children.begin();
			auto end = _weak->_children.end();

			for (; it != end; ++it)
			{
				if ((*it).get() == this)
				{
					_weak->_children.erase(it);
					break;
				}
			}
		}

		_parent = parent;
		if (parent)
			parent->_children.push_back(std::dynamic_pointer_cast<GameObject>(this->shared_from_this()));

		for (auto& it : _components)
			it->onParentChangeAfter();
	}
}

GameObjectPtr
GameObject::getParent() const noexcept
{
	return _parent.lock();
}

void
GameObject::addChild(GameObjectPtr entity) noexcept
{
	assert(entity);
	entity->setParent(std::dynamic_pointer_cast<GameObject>(this->shared_from_this()));
}

void
GameObject::removeChild(GameObjectPtr entity) noexcept
{
	assert(entity);

	auto it = _children.begin();
	auto end = _children.end();
	for (; it != end; ++it)
	{
		if ((*it) == entity)
		{
			(*it)->setParent(nullptr);
			break;
		}
	}

	if (it != end)
	{
		_children.erase(it);
	}
}

void
GameObject::cleanupChildren() noexcept
{
	for (auto& it : _children)
		it.reset();

	_children.clear();
}

GameObjectPtr
GameObject::findChild(const std::string& name, bool recuse) noexcept
{
	for (auto& it : _children)
	{
		if (it->getName() == name)
		{
			return it;
		}
	}

	if (recuse)
	{
		for (auto& it : _children)
		{
			auto result = it->findChild(name, recuse);
			if (result)
			{
				return result;
			}
		}
	}

	return nullptr;
}

std::uint32_t
GameObject::getChildCount() const noexcept
{
	return _children.size();
}

GameObjects&
GameObject::getChildren() noexcept
{
	return _children;
}

const GameObjects&
GameObject::getChildren() const noexcept
{
	return _children;
}

void
GameObject::setTranslate(const Vector3& pos) noexcept
{
	if (_translate != pos)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_translate = pos;
		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

void
GameObject::setTranslateAccum(const Vector3& v) noexcept
{
	this->setTranslate(_translate + v);
}

const Vector3&
GameObject::getTranslate() const noexcept
{
	return _translate;
}

void
GameObject::setScale(const Vector3& pos) noexcept
{
	if (_scaling != pos)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_scaling = pos;
		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

void
GameObject::setScaleAccum(const Vector3& scale) noexcept
{
	this->setScale(_scaling + scale);
}

const Vector3&
GameObject::getScale() const noexcept
{
	return _scaling;
}

void
GameObject::setQuaternion(const Quaternion& quat) noexcept
{
	if (_quat != quat)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_quat = quat;
		_euler.makeRotate(_quat);

		_right = _quat.rotate(Vector3::Right);
		_right.normalize();

		_up = _quat.rotate(Vector3::Up);
		_up.normalize();

		_forward = _quat.rotate(Vector3::Forward);
		_forward.normalize();

		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

void
GameObject::setQuaternionAccum(const Quaternion& quat) noexcept
{
	this->setQuaternion(quat.cross(_quat));
}

const Quaternion&
GameObject::getQuaternion() const noexcept
{
	return _quat;
}

void
GameObject::setEulerAngles(const EulerAngles& euler) noexcept
{
	if (_euler != euler)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_euler = euler;
		_quat.makeRotate(euler);

		_right = _quat.rotate(Vector3::Right);
		_right.normalize();

		_up = _quat.rotate(Vector3::Up);
		_up.normalize();

		_forward = _quat.rotate(Vector3::Forward);
		_forward.normalize();

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

void
GameObject::setEulerAnglesAccum(const EulerAngles& euler) noexcept
{
	this->setEulerAngles(_euler + euler);
}

const EulerAngles&
GameObject::getEulerAngles() const noexcept
{
	return _euler;
}

void
GameObject::setRight(const Vector3& right) noexcept
{
	if (_right != right)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_right = right;
		_right.normalize();

		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

const Vector3&
GameObject::getRight() const noexcept
{
	return _right;
}

void
GameObject::setUpVector(const Vector3& up) noexcept
{
	if (_up != up)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_up = up;
		_up.normalize();

		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveBefore();
		}
	}
}

const Vector3&
GameObject::getUpVector() const noexcept
{
	return _up;
}

void
GameObject::setForward(const Vector3& forward) noexcept
{
	if (_forward != forward)
	{
		if (this->getActive())
		{
			this->_onMoveBefore();
		}

		_forward = forward;
		_forward.normalize();

		_needUpdates = true;

		if (this->getActive())
		{
			this->_onMoveAfter();
		}
	}
}

const Vector3&
GameObject::getForward() const noexcept
{
	return _forward;
}

const Matrix4x4&
GameObject::getTransform() const noexcept
{
	this->_updateTransform();
	return _transform;
}

const Matrix4x4&
GameObject::getTransformInverse() const noexcept
{
	this->_updateTransform();
	return _transformInverse;
}

const Matrix4x4&
GameObject::getTransformInverseTranspose() const noexcept
{
	this->_updateTransform();
	return _transformInverseTranspose;
}

void
GameObject::_updateTransform() const noexcept
{
	if (_needUpdates)
	{
		_transform.makeTransform(_translate, _quat, _scaling);

		_transformInverse = _transform;
		_transformInverse.inverse();

		_transformInverseTranspose = _transformInverse;
		_transformInverseTranspose.transpose();

		_needUpdates = false;
	}
}

void
GameObject::addComponent(GameComponentPtr component) except
{
	assert(component);
	assert(component->_gameObject == nullptr);

	auto it = std::find_if(_components.begin(), _components.end(), [component](GameComponentPtr& it) { return component->isInstanceOf(it->rtti()); });
	if (it == _components.end())
	{
		component->_setGameObject(this);
		component->onAttach();

		if (this->getActive() && component->getActive())
			component->onActivate();

		for (auto& it : _components)
			component->onAttachComponent(it);

		for (auto& it : _components)
			it->onAttachComponent(component);

		_components.push_back(component);
	}
}

void
GameObject::removeComponent(GameComponentPtr component) noexcept
{
	assert(component);
	assert(component->_gameObject == this);

	auto it = std::find(_components.begin(), _components.end(), component);
	if (it != _components.end())
	{
		_components.erase(it);

		for (auto& it : _components)
			component->onDetachComponent(it);

		for (auto& it : _components)
			it->onDetachComponent(component);

		if (this->getActive() && component->getActive())
			component->onDeactivate();

		component->onDetach();
		component->_setGameObject(nullptr);
	}
}

void
GameObject::cleanupComponents() noexcept
{
	for (auto& it : _components)
	{
		for (auto& component : _components)
		{
			if (it != component)
				it->onDetachComponent(component);
		}

		if (it->getActive())
			it->onDeactivate();

		it->onDetach();
	}

	_components.clear();
}

GameComponentPtr
GameObject::getComponent(const rtti::Rtti* type) const noexcept
{
	assert(type);

	for (auto& it : _components)
	{
		if (it->isA(type))
			return it;
	}

	return nullptr;
}

GameComponentPtr
GameObject::getComponent(const rtti::Rtti& type) const noexcept
{
	return this->getComponent(&type);
}

GameComponentPtr
GameObject::getComponentInChildren(const rtti::Rtti* type) const noexcept
{
	assert(type);

	for (auto& it : _components)
	{
		if (it->isA(type))
			return it;
	}

	for (auto& it : _children)
	{
		auto component = it->getComponentInChildren(type);
		if (component)
			return component;
	}

	return nullptr;
}

GameComponentPtr 
GameObject::getComponentInChildren(const rtti::Rtti& type) const noexcept
{
	return this->getComponentInChildren(&type);
}

const GameComponents&
GameObject::getComponents() const noexcept
{
	return _components;
}

void
GameObject::destroy() noexcept
{
	this->cleanupChildren();
	this->cleanupComponents();
	this->setParent(nullptr);
}

void
GameObject::sendMessage(const MessagePtr& message) noexcept
{
	assert(message);

	if (!this->getActive())
		return;

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMessage(message);
	}
}

void
GameObject::sendMessageUpwards(const MessagePtr& message) noexcept
{
	assert(message);

	if (!this->getActive())
		return;

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMessage(message);
	}

	auto parent = _parent.lock();
	if (parent)
		parent->sendMessageDownwards(message);
}

void
GameObject::sendMessageDownwards(const MessagePtr& message) noexcept
{
	assert(message);

	if (!this->getActive())
		return;

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMessage(message);
	}

	for (auto& it : _children)
		it->sendMessageDownwards(message);
}

GameServerPtr
GameObject::getGameServer() noexcept
{
	auto parent = _parent.lock();
	if (parent)
		return parent->getGameServer();
	return nullptr;
}

GameScenePtr
GameObject::getGameScene() noexcept
{
	auto parent = _parent.lock();
	if (parent)
		return parent->getGameScene();
	return nullptr;
}

void 
GameObject::load(iarchive& reader) noexcept
{
	std::string name;
	bool active = false;
	int layer = 0;
	float3 position = float3::Zero;
	float3 scale = float3::One;
	float3 rotate = float3::Zero;
	float3 right = float3::UnitX;
	float3 up = float3::UnitY;
	float3 forward = float3::UnitZ;

	reader >> make_archive(name, "name");
	reader >> make_archive(active, "active");
	reader >> make_archive(layer, "layer");
	reader >> make_archive(position, "position");
	reader >> make_archive(scale, "scale");
	reader >> make_archive(rotate, "rotate");
	reader >> make_archive(right, "right");
	reader >> make_archive(forward, "forward");
	reader >> make_archive(up, "up");

	right.normalize();
	up.normalize();
	forward.normalize();

	this->setName(name);
	this->setActive(active);
	this->setLayer(layer);
	this->setUpVector(up);
	this->setForward(forward);
	this->setTranslate(position);
	this->setScale(scale);
	this->setEulerAngles(EulerAngles(rotate));
}

void 
GameObject::save(oarchive& write) noexcept
{
}

GameObjectPtr
GameObject::clone() const noexcept
{
	auto instance = std::make_shared<GameObject>();
	instance->setParent(this->getParent());
	instance->setName(this->getName());
	instance->setLayer(this->getLayer());
	instance->setForward(this->getForward());
	instance->setUpVector(this->getUpVector());
	instance->setQuaternion(this->getQuaternion());
	instance->setScale(this->getScale());
	instance->setTranslate(this->getTranslate());

	for (auto& it : _components)
		instance->addComponent(it->clone());

	for (auto& it : this->getChildren())
		instance->addChild(it->clone());

	return instance;
}

void
GameObject::_onFrameBegin() except
{
	assert(this->getActive());

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onFrameBegin();
	}
}

void
GameObject::_onFrame() except
{
	assert(this->getActive());

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onFrame();
	}
}

void
GameObject::_onFrameEnd() except
{
	assert(this->getActive());

	for (auto& it : _components)
	{
		if (it->getActive())
			it->onFrameEnd();
	}		
}

void
GameObject::_onMoveBefore() except
{
	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMoveBefore();
	}

	for (auto& it : _children)
		it->_onMoveBefore();
}

void
GameObject::_onMoveAfter() except
{
	for (auto& it : _components)
	{
		if (it->getActive())
			it->onMoveAfter();
	}

	for (auto& it : _children)
		it->_onMoveAfter();
}

_NAME_END