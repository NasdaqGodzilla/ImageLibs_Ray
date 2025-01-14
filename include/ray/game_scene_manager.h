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
#ifndef _H_GAME_SCENE_MANAGER_H_
#define _H_GAME_SCENE_MANAGER_H_

#include <ray/game_features.h>

_NAME_BEGIN

class EXPORT GameSceneManager final
{
	__DeclareSingleton(GameSceneManager)
public:
	GameSceneManager() noexcept;
	~GameSceneManager() noexcept;

	bool open() noexcept;
	void close() noexcept;

	GameScenePtr findScene(const util::string& name) noexcept;
	GameScenePtr findActiveScene(const util::string& name) noexcept;

	GameScenePtr instantiate(const util::string& name) except;

	bool activeScene(const util::string& name) noexcept;

	void onFrameBegin() noexcept;
	void onFrame() noexcept;
	void onFrameEnd() noexcept;

private:
	friend GameScene;
	void _instanceScene(GameScene* entity, std::size_t& instanceID) noexcept;
	void _unsetScene(GameScene* entity) noexcept;
	void _activeScene(GameScene* entity, bool active) noexcept;

private:

	bool _hasEmptyActors;

	std::vector<std::size_t> _emptyLists;
	std::vector<GameScene*> _instanceLists;
	std::vector<GameScene*> _activeActors;
};

_NAME_END

#endif
