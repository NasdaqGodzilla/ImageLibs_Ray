// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2017.
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
	: _visible(true)
	, _layer(0)
	, _boundingBox(Vector3::Zero, Vector3::Zero)
	, _worldBoundingxBox(Vector3::Zero, Vector3::Zero)
	, _transform(float4x4::One)
	, _transformInverse(float4x4::One)
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
RenderObject::setVisible(bool enable) noexcept
{
	_visible = enable;
}

bool
RenderObject::getVisible() const noexcept
{
	return _visible;
}

void
RenderObject::setBoundingBox(const BoundingBox& bound) noexcept
{
	_worldBoundingxBox = _boundingBox = bound;
	_worldBoundingxBox.transform(_transform);
}

const BoundingBox&
RenderObject::getBoundingBox() const noexcept
{
	return _boundingBox;
}

const BoundingBox&
RenderObject::getBoundingBoxInWorld() const noexcept
{
	return _worldBoundingxBox;
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
	if (_renderScene != scene)
	{
		this->onSceneChangeBefore();

		if (_renderScene)
			_renderScene->removeRenderObject(this);

		if (scene)
			scene->addRenderObject(this);

		_renderScene = scene;

		this->onSceneChangeAfter();
	}
}

const RenderScenePtr&
RenderObject::getRenderScene() const noexcept
{
	return _renderScene;
}

void
RenderObject::setTransform(const float4x4& transform) noexcept
{
	this->setTransform(transform, math::transformInverse(transform));
}

void
RenderObject::setTransform(const float4x4& transform, const float4x4& transformInverse) noexcept
{
	this->onMoveBefore();

	_transform = transform;
	_transformInverse = transformInverse;

	_worldBoundingxBox = _boundingBox;
	_worldBoundingxBox.transform(_transform);

	this->onMoveAfter();
}

const Vector3&
RenderObject::getRight() const noexcept
{
	return _transform.getRight();
}

const Vector3&
RenderObject::getUpVector() const noexcept
{
	return _transform.getUpVector();
}

const Vector3&
RenderObject::getForward() const noexcept
{
	return _transform.getForward();
}

const Vector3&
RenderObject::getTranslate() const noexcept
{
	return _transform.getTranslate();
}

const float4x4&
RenderObject::getTransform() const noexcept
{
	return _transform;
}

const float4x4&
RenderObject::getTransformInverse() const noexcept
{
	return _transformInverse;
}

void
RenderObject::onRenderBefore(const Camera& camera) noexcept
{
	auto listener = this->getOwnerListener();
	if (listener)
		listener->onRenderObjectPre(camera);
}

void
RenderObject::onRenderAfter(const Camera& camera) noexcept
{
	auto listener = this->getOwnerListener();
	if (listener)
		listener->onRenderObjectPost(camera);
}

void
RenderObject::onMoveBefore() noexcept
{
}

void
RenderObject::onMoveAfter() noexcept
{
}

void
RenderObject::onSceneChangeBefore() noexcept
{
}

void
RenderObject::onSceneChangeAfter() noexcept
{
}

bool
RenderObject::onVisiableTest(const Camera& camera, const Frustum& fru) noexcept
{
	return fru.contains(this->getBoundingBoxInWorld().aabb());
}

void
RenderObject::onAddRenderData(RenderDataManager& manager) noexcept
{
}

void
RenderObject::onRenderObject(RenderPipeline& pipelineContext, RenderQueue queue, MaterialTech* tech) noexcept
{
}

_NAME_END