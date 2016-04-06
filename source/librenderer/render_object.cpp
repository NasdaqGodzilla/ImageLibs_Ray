// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2016.
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
#include <ray/render_object.h>
#include <ray/render_scene.h>

_NAME_BEGIN

__ImplementSubInterface(RenderObject, rtti::Interface, "RenderObject")

RenderListener::RenderListener() noexcept
{
}

RenderListener::~RenderListener() noexcept
{
}

RenderObject::RenderObject() noexcept
	: _layer(0)
	, _isCastShadow(true)
	, _isReceiveShadow(true)
	, _boundingBox(Vector3::Zero, Vector3::Zero)
	, _worldBoundingxBox(Vector3::Zero, Vector3::Zero)
	, _transform(Matrix4x4::One)
	, _transformInverse(Matrix4x4::One)
	, _transformInverseTranspose(Matrix4x4::One)
	, _renderListener(nullptr)
{
}

RenderObject::~RenderObject() noexcept
{
	this->setRenderScene(nullptr);
}

void
RenderObject::setLayer(std::uint8_t layer) noexcept
{
	_layer = layer;
}

std::uint8_t
RenderObject::getLayer() const noexcept
{
	return _layer;
}

void
RenderObject::setBoundingBox(const Bound& bound) noexcept
{
	_worldBoundingxBox = _boundingBox = bound;
	_worldBoundingxBox.applyMatrix(_transform);
}

const Bound&
RenderObject::getBoundingBox() const noexcept
{
	return _boundingBox;
}

const Bound&
RenderObject::getBoundingBoxInWorld() const noexcept
{
	return _worldBoundingxBox;
}

void
RenderObject::setReceiveShadow(bool enable) noexcept
{
	_isReceiveShadow = enable;
}

bool
RenderObject::getReceiveShadow() const noexcept
{
	return _isReceiveShadow;
}

void
RenderObject::setCastShadow(bool value) noexcept
{
	_isCastShadow = value;
}

bool
RenderObject::getCastShadow()  const noexcept
{
	return _isCastShadow;
}

void
RenderObject::setOwnerListener(RenderListener* listener) noexcept
{
	_renderListener = listener;
}

RenderListener*
RenderObject::getOwnerListener() noexcept
{
	return _renderListener;
}

void
RenderObject::setRenderScene(RenderScenePtr scene) noexcept
{
	if (_renderScene.lock() != scene)
	{
		this->onSceneChangeBefor();

		if (_renderScene.use_count())
			_renderScene.lock()->removeRenderObject(this->cast<RenderObject>());

		if (scene)
			scene->addRenderObject(this->cast<RenderObject>());

		_renderScene = scene;

		this->onSceneChangeAfter();
	}
}

RenderScenePtr
RenderObject::getRenderScene() const noexcept
{
	return _renderScene.lock();
}

void
RenderObject::setTransform(const Matrix4x4& transform, const Matrix4x4& inverse, const Matrix4x4& inverseTranspose) noexcept
{
	this->onMoveBefor();

	_transform = transform;
	_transformInverse = inverse;
	_transformInverseTranspose = inverseTranspose;

	_worldBoundingxBox.applyMatrix(_transform);

	this->onMoveAfter();
}

Vector3
RenderObject::getTranslate() const noexcept
{
	return _transform.getTranslate();
}

Vector3
RenderObject::getRight() const noexcept
{
	return Vector3(_transform.a1, _transform.b1, _transform.c1);
}

Vector3
RenderObject::getUpVector() const noexcept
{
	return Vector3(_transform.a2, _transform.b2, _transform.c2);
}

Vector3
RenderObject::getForward() const noexcept
{
	return Vector3(_transform.a3, _transform.b3, _transform.c3);
}

const Matrix4x4&
RenderObject::getTransform() const noexcept
{
	return _transform;
}

const Matrix4x4&
RenderObject::getTransformInverse() const noexcept
{
	return _transformInverse;
}

const Matrix4x4&
RenderObject::getTransformInverseTranspose() const noexcept
{
	return _transformInverseTranspose;
}

void 
RenderObject::addSubRenderObject(RenderObjectPtr object) noexcept
{
	auto it = std::find(_renderObjects.begin(), _renderObjects.end(), object);
	if (it == _renderObjects.end())
	{
		_renderObjects.push_back(object);
	}
}

void 
RenderObject::removeSubRenderObject(RenderObjectPtr object) noexcept
{
	auto it = std::find(_renderObjects.begin(), _renderObjects.end(), object);
	if (it != _renderObjects.end())
	{
		_renderObjects.erase(it);
	}
}

RenderObjects& 
RenderObject::getSubeRenderObjects() noexcept
{
	return _renderObjects;
}

void 
RenderObject::onMoveBefor() noexcept
{
}

void 
RenderObject::onMoveAfter() noexcept
{
}

void 
RenderObject::onSceneChangeBefor() noexcept
{
}

void 
RenderObject::onSceneChangeAfter() noexcept
{
}

_NAME_END