#pragma once

#ifndef SB_PRECOMPILED_HEADER
#include <vector>
#include <filesystem>
#include <glad/glad.h>
#endif

#include "Core/Base/Base.h"
#include "Core/Renderer/Mesh.h"

namespace sb {

	class Model {

	public:

		Model(const std::filesystem::path& path);

		inline const std::vector<Ref<Mesh>>& GetMeshes() const { return m_Meshes; }

		static Ref<Model> Create(const std::filesystem::path& path);

	private:

		std::vector<Ref<Mesh>> m_Meshes;
		Vector3f m_Position;
	};
}
