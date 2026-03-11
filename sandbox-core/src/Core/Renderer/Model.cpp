#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Renderer/Model.h"

namespace sb {

	static Matrix4f ConvertAssimpMatrixToGLM(const aiMatrix4x4& mat);
	static void ProcessNode(std::vector<Mesh>& meshes, aiNode* node, const aiScene* scene, const Matrix4f& parent_transform);
	static void ProcessMesh(std::vector<Mesh>& meshes, aiMesh* mesh, const aiScene* scene, const Matrix4f& transform);

	Model::Model(const std::filesystem::path& path) {

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.string(),
			aiProcess_Triangulate |
			aiProcess_SortByPType |
			aiProcess_ImproveCacheLocality |
			aiProcess_FixInfacingNormals |
			aiProcess_FlipUVs |
			aiProcess_GenSmoothNormals |
			aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {

			SB_ERROR("Failed to load model: {}", importer.GetErrorString());
			return;
		}

		if (!scene->HasMeshes()) {

			SB_ERROR("Failed to find any mesh in the model");
			return;
		}

		m_Meshes.reserve(scene->mNumMeshes);
		ProcessNode(m_Meshes, scene->mRootNode, scene, Matrix4f(1.0f));
	}

	Model::Model(const Model& other)
		: m_Meshes(other.m_Meshes)

	{}

	Ref<Model> Model::Create(const std::filesystem::path& path) {

		return CreateRef<Model>(path);
	}

	Matrix4f ConvertAssimpMatrixToGLM(const aiMatrix4x4& mat) {

		Matrix4f transform(1.0f);
		transform[0][0] = mat.a1;
		transform[0][1] = mat.b1;
		transform[0][2] = mat.c1;
		transform[0][3] = mat.d1;
		transform[1][0] = mat.a2;
		transform[1][1] = mat.b2;
		transform[1][2] = mat.c2;
		transform[1][3] = mat.d2;
		transform[2][0] = mat.a3;
		transform[2][1] = mat.b3;
		transform[2][2] = mat.c3;
		transform[2][3] = mat.d3;
		transform[3][0] = mat.a4;
		transform[3][1] = mat.b4;
		transform[3][2] = mat.c4;
		transform[3][3] = mat.d4;

		return transform;
	}

	void ProcessNode(std::vector<Mesh>& meshes, aiNode* node, const aiScene* scene, const Matrix4f& parent_transform) {

		Matrix4f worldTransform = parent_transform * ConvertAssimpMatrixToGLM(node->mTransformation);

		for (unsigned int i = 0; i < node->mNumMeshes; i++) {

			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(meshes, mesh, scene, worldTransform);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
			ProcessNode(meshes, node->mChildren[i], scene, worldTransform);
	}

	void ProcessMesh(std::vector<Mesh>& meshes, aiMesh* mesh, const aiScene* scene, const Matrix4f& transform) {

		unsigned int indicesCount = 0;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			indicesCount += mesh->mFaces[i].mNumIndices;

		std::vector<Vertex> vertices(mesh->mNumVertices);
		std::vector<Uint32> indices;
		indices.reserve(indicesCount);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

			Vertex& vertex = vertices[i];

			// Position
			vertex.Position.x = mesh->mVertices[i].x;
			vertex.Position.y = mesh->mVertices[i].y;
			vertex.Position.z = mesh->mVertices[i].z;

			// If the mesh has normals
			Matrix3f normalMatrix(1.0f);
			if (mesh->HasNormals()) {

				// Normal
				vertex.Normal.x = mesh->mNormals[i].x;
				vertex.Normal.y = mesh->mNormals[i].y;
				vertex.Normal.z = mesh->mNormals[i].z;
			}

			// If the mesh has colors
			if (mesh->HasVertexColors(0)) {

				// Color
				vertex.Color.r = mesh->mColors[0][i].r;
				vertex.Color.g = mesh->mColors[0][i].g;
				vertex.Color.b = mesh->mColors[0][i].b;
				vertex.Color.a = mesh->mColors[0][i].a;
			}

			else
				vertex.Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);

			if (mesh->HasTextureCoords(0)) {

				// TexCoords
				vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;

				if (mesh->HasTangentsAndBitangents()) {

					// Tangents
					vertex.Tangent.x = mesh->mTangents[i].x;
					vertex.Tangent.y = mesh->mTangents[i].y;
					vertex.Tangent.z = mesh->mTangents[i].z;

					// Bitangents
					vertex.Bitangent.x = mesh->mBitangents[i].x;
					vertex.Bitangent.y = mesh->mBitangents[i].y;
					vertex.Bitangent.z = mesh->mBitangents[i].z;
				}
			}

			else {

				//SB_WARN("Model requested texture coordinates, but found none!");
				vertex.TexCoords = Vector2f(0.0f, 0.0f);
			}
		}

		// Faces
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {

			const aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		meshes.emplace_back(mesh->mName.C_Str(), vertices, indices, transform);
	}
}
