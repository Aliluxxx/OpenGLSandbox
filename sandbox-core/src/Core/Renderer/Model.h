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
		Model(const Model& other);

		inline const std::vector<Mesh>& GetMeshes() const { return m_Meshes; }

		static Ref<Model> Create(const std::filesystem::path& path);
		static Ref<Model> Create(const Ref<Model>& other);

	private:

		std::vector<Mesh> m_Meshes;
	};
}
