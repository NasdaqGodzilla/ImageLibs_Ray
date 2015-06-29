// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2014.
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
#ifndef _H_RENDER_SCENE_H_
#define _H_RENDER_SCENE_H_

#include <ray/camera.h>
#include <ray/light.h>
#include <ray/render_object.h>

_NAME_BEGIN

enum FogMode
{
    FM_LINEAR,
    FM_EXP,
    FM_EXP2,
};

class EXPORT RenderScene : public Reference<RenderScene>
{
public:
    typedef std::vector<Camera*> CameraList;
    typedef std::vector<Light*> LightList;
    typedef std::vector<RenderObject*> RenderObjects;

public:

    RenderScene() noexcept;
    virtual ~RenderScene() noexcept;

    void addCamera(Camera* camera) noexcept;
    void removeCamera(Camera* camera) noexcept;
    void sortCamera() noexcept;

    CameraList& getCameraList() noexcept;

    void addLight(Light* light) noexcept;
    void removeLight(Light* light) noexcept;
    void sortLight() noexcept;

    LightList& getLightList() noexcept;

    void addRenderObject(RenderObject* object) noexcept;
    void removeRenderObject(RenderObject* object) noexcept;

    void computVisiableLight(Camera* camera, std::vector<Light*>& lights) noexcept;
    void computVisiable(Camera* camera, std::vector<RenderObject*>& object) noexcept;

    void setAmbientColor(const Vector3& color) noexcept;
    const Vector3& getAmbientColor() const noexcept;

private:

    bool    _fogEnable;
    Vector3 _fogColor;
    FogMode _fogMode;
    float   _fogStart;
    float   _fogEnd;

    Vector3 _ambientLight;

    CameraList _cameraList;
    LightList _lightList;
    RenderObjects _renderObjectList;
};

_NAME_END

#endif