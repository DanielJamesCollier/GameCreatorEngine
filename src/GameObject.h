#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Transform.h"

#include <string>
#include <vector>

class WindowEngine;
class RenderingEngine;
class ShaderProgram;

class GameObject : public Transform
{
public:

	GameObject(const std::string& name);
	GameObject(const std::string& name, bool active);
	GameObject();

	virtual ~GameObject();

	// setters
	void setRenderingEngine(RenderingEngine* renderer);
	void setName(const std::string& name);
	void setActive(bool active);
	void setParent(GameObject *parent);
	void addChild(GameObject *child);
	void removeChild(GameObject *child);

	//getters
	std::string getName(void);
	GameObject* getParent(void) const;
	GameObject* getChild(unsigned int i);
	bool isActive(void);
	unsigned int getChildCount(void);

	
	// virtual functions
	virtual void render();
	virtual void update(WindowEngine* window);
	virtual void render(ShaderProgram* program, RenderingEngine* render);
	virtual unsigned int& getVerticesCount(void);
	virtual unsigned int& getIndicesCount(void);
	virtual unsigned int& getFacesCount(void);

private:
	GameObject* m_Parent;

	std::string m_Name;
	std::vector<GameObject*> m_Children;
	int m_ChildCount;
	bool m_Active;

	unsigned int vertices_count;
	unsigned int indices_count;
	unsigned int faces_count;
	 
protected:
	static RenderingEngine* renderer;
};
#endif

