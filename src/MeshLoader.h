#pragma once
#ifndef MESHLOADER_H
#define MESHLOADER_H

// standard includes
#include <vector>
#include <string>

// assimp includes
#include <scene.h>

class Mesh;
class GameObject;

class MeshLoader
{
public:
	MeshLoader(const std::string& file_name);
	~MeshLoader();

	void loadMesh(const std::string& file_name);
	void loadMeshAndOptimize(const std::string& file_name);

	GameObject* getRoot();
	

private:
	GameObject* scene_root;
};
#endif

