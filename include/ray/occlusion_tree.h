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
#ifndef _H_OCCLUSION_OBJECT_H_
#define _H_OCCLUSION_OBJECT_H_

#include <ray/occlusion_types.h>

_NAME_BEGIN

class OcclusionTree;
class OcclusionObject
{
public:
    OcclusionObject() noexcept;
    virtual ~OcclusionObject() noexcept;

    bool isLeaf() const noexcept;
    bool isVirtualLeaf() const noexcept;

    const Bound& getBoundingxBox() const noexcept;

private:

    friend OcclusionTree;

    Bound _boundingBox;

    int _depth;
    int _leaves;

    bool _isVirtualLeaf;

    OcclusionObjectPtr _parent;
};

class OcclusionObjectLeaf
{
public:

};

class OcclusionObjectIterator
{
public:

    OcclusionObjectPtr frist();
    OcclusionObjectPtr second();

private:

    OcclusionObjectPtr _frist;
    OcclusionObjectPtr _second;
};

class OcclusionTree
{
public:

    void addOcclusionObject(OcclusionObjectPtr object) noexcept;

    bool isVisiable(OcclusionObjectPtr object) noexcept;

    void collectObjects(OcclusionObjectPtr root, OcclusionObjectContainer& container) noexcept;

    void computeBounds(OcclusionObjectPtr root) noexcept;
    void computeLeaves(OcclusionObjectPtr root) noexcept;


private:

    Bound _boundingBox;

    Frustum _frustum;

    OcclusionObjectPtr _root;

    std::vector<OcclusionObjectPtr> _occlusionObjects;
};

_NAME_END

#endif