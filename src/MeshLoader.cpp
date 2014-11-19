#include "MeshLoader.h"
#include "Logger.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Texture.h"
#include "cout.h"

// assimp includes
#include <Importer.hpp>
#include <postprocess.h>

MeshLoader::MeshLoader(const std::string& file_name)
{
	scene_root = new GameObject("scene root");

	loadMesh(file_name);
	//loadMeshAndOptimize(file_name);

}

void MeshLoader::loadMesh(const std::string& file_name)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(file_name,
		aiProcess_CalcTangentSpace |
		aiProcess_GenNormals |
		aiProcess_FlipUVs |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_OptimizeMeshes |
		aiProcess_SortByPType);

	if (!scene)
	{
		Logger::errorBlock("Scene failed to open", "File name: " + file_name + "\nError: " + importer.GetErrorString(), true);
		return;
	}

	// texturing

	/*for (unsigned int j = 0; j < scene->mNumMaterials; ++j)
	{
		const aiMaterial* material = scene->mMaterials[j];
		int a = 5;
		int texIndex = 0;

		cout << "texture: " << j << endl;

		aiString file_name;

		if (material->GetTexture(aiTextureType_DIFFUSE, texIndex, &file_name) == AI_SUCCESS)
		{
			std::string dir = "Models/";
			std::string texture_name = file_name.data;
			std::string full_path = dir + texture_name;

			textures.push_back(Texture(full_path));


		}
	}*/

	// texturing test
	for (unsigned int j = 0; j < scene->mNumMaterials; ++j)
	{
		int texIndex = 0;
		aiString path;  // filename
		aiReturn texFound = AI_SUCCESS;

		while (texFound == AI_SUCCESS)
		{
			texFound = scene->mMaterials[j]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);

			std::string dir = "Models/";
			std::string texture_name = path.data;
			std::string full_path = dir + texture_name;

			texIndex++;
			
		}
	}

	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		//get the mesh
		aiMesh* mesh = scene->mMeshes[i];

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		


		// indices
		for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
		{
			const aiFace& face = mesh->mFaces[j];

			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		//vertices
		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
		{

			// temp vertex to be assined and pushed back to the vertices vector
			Vertex v;

			const aiVector3D texCoord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][j] : aiZeroVector; // 0 might be i because this loads more than one model

			v.setPosition(glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z));

			if (mesh->mNormals)	v.setNormals(glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z));
			else
			{
				v.setNormals(glm::vec3());
			}

			v.setTexCord(glm::vec2(texCoord.x, texCoord.y));
			
			if (mesh->mTangents) v.setTangent(glm::vec3());
			else
			{
				v.setTangent(glm::vec3(0, 1, 0));
			}

			vertices.push_back(v);
		}

		Mesh *meshd = new Mesh(vertices, indices);
		//meshd->setScale(0.1);

		scene_root->addChild(meshd);

	}

	std::string s_mesh_count = std::to_string(scene->mNumMeshes);
	std::string vertices_count = std::to_string(scene_root->getVerticesCount());
	std::string indices_count = std::to_string(scene_root->getIndicesCount());
	std::string faces_count = std::to_string(scene_root->getFacesCount());

	Logger::infoBlock("Mesh Loaded", "Name: " + file_name + "\nMesh Count: " + s_mesh_count +  "\nVertices: " + vertices_count + "\nIndices: " + indices_count + "\nFaces: " + faces_count, true);
}

/* if the model file contains more than one mesh this function will
*  combine them all into one mesh reducing the amount of meshes created which
	intern reduces the draw call to one per model file instead of making it have a draw call
	depending on the number of meshes

	FIX THIS FUNCTION
*/

void MeshLoader::loadMeshAndOptimize(const std::string& file_name)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(file_name,
		aiProcessPreset_TargetRealtime_Quality |
		aiProcess_CalcTangentSpace |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_OptimizeMeshes |
		aiProcess_SortByPType);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	if (!scene)
	{
		Logger::errorBlock("Scene failed to open", "File name: " + file_name + "\nError: " + importer.GetErrorString(), true);
		return;
	}

	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		//get the mesh
		aiMesh* mesh = scene->mMeshes[i];


		// indices
		for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
		{
			const aiFace& face = mesh->mFaces[j];

			indices.push_back(face.mIndices[0] * (i + 1));
			indices.push_back(face.mIndices[1] * (i + 1));
			indices.push_back(face.mIndices[2] * (i + 1));
		}

		//vertices
		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
		{

			// temp vertex to be assined and pushed back to the vertices vector
			Vertex v;

			const aiVector3D texCoord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][j] : aiZeroVector; // 0 might be i because this loads more than one model

			v.setPosition(glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z));
			v.setNormals(glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z));
			v.setTexCord(glm::vec2(texCoord.x, texCoord.y));

			

			v.setTangent(glm::vec3());

			vertices.push_back(v);
		}

		// texturing
		for (unsigned int j = 0; j < scene->mNumMaterials; ++j)
		{
			const aiMaterial* material = scene->mMaterials[j];
			int a = 5;
			int texIndex = 0;

			aiString file_name;

			if (material->GetTexture(aiTextureType_DIFFUSE, texIndex, &file_name) == AI_SUCCESS)
			{
				std::string dir = "Models/";
				std::string texture_name = file_name.data;
				std::string full_path = dir + texture_name;

			}
		}
	}

	scene_root->addChild(new Mesh(vertices, indices));

	std::string s_mesh_count = std::to_string(scene->mNumMeshes);

	Logger::infoBlock("Mesh Loaded", "Name: " + file_name + "\nVertices: to add vertex counter\nIndices: to add indices counter\nMesh Count: " + s_mesh_count, true);
}

MeshLoader::~MeshLoader()
{

}


GameObject* MeshLoader::getRoot()
{
	return scene_root;
}