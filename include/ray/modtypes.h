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
#ifndef _H_MODEL_TYPES_H_
#define _H_MODEL_TYPES_H_

#include <ray/memory.h>
#include <ray/math.h>
#include <ray/fstream.h>
#include <ray/reference.h>
#include <ray/moddef.h>

_NAME_BEGIN

typedef std::shared_ptr<class AnimationProperty> AnimationPropertyPtr;
typedef std::shared_ptr<class TextureProperty> TexturePropertyPtr;
typedef std::shared_ptr<class CameraProperty> CameraPropertyPtr;
typedef std::shared_ptr<class LightProperty> LightPropertyPtr;
typedef std::shared_ptr<class MeshProperty> MeshPropertyPtr;
typedef std::shared_ptr<class MaterialProperty> MaterialPropertyPtr;
typedef std::shared_ptr<class Model> ModelPtr;
typedef std::shared_ptr<class Bone> BonePtr;
typedef std::shared_ptr<class IKAttr> IKAttrPtr;
typedef std::shared_ptr<class RigidbodyProperty> RigidbodyPropertyPtr;
typedef std::shared_ptr<class JointProperty> JointPropertyPtr;
typedef std::shared_ptr<class VertexWeight> VertexWeightPtr;
typedef std::shared_ptr<class MeshProperty> MeshPropertyPtr;

typedef std::vector<VertexWeight> VertexWeights;
typedef std::vector<MeshPropertyPtr> MeshPropertys;
typedef std::vector<Bone> Bones;
typedef std::vector<IKAttr> InverseKinematics;
typedef std::vector<class CombineMesh> CombineMeshes;

enum TextureType
{
	TextureTypeNone,
	TextureTypeDiffuse,
	TextureTypeSpecular,
	TextureTypeAmbient,
	TextureTypeEmissive,
	TextureTypeHeight,
	TextureTypeNormals,
	TextureTypeShininess,
	TextureTypeOpacity,
	TextureTypeDisplacement,
	TextureTypeLightmap,
	TextureTypeReflection,
};

enum PropertyTypeInfo
{
	PropertyTypeInfoFloat = 0x01,
	PropertyTypeInfoString = 0x02,
	PropertyTypeInfoInt = 0x04,
	PropertyTypeInfoBuffer = 0x08,
};

_NAME_END

#endif