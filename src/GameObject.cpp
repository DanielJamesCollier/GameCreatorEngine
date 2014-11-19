#include "GameObject.h"

#include <iostream>
using namespace std;

RenderingEngine* GameObject::renderer = NULL;

GameObject::GameObject() :

m_ChildCount(0),
vertices_count(0),
indices_count(0),
faces_count(0),
m_Active(true)
{
	setName("NO NAME");
}

GameObject::GameObject(const std::string& name) :
m_ChildCount(0),
vertices_count(0),
indices_count(0),
faces_count(0),
m_Active(true)

{
	setName(name);
	setActive(true);
}

GameObject::GameObject(const std::string& name, bool active) :

m_ChildCount(0),
vertices_count(0),
indices_count(0),
faces_count(0),
m_Active(true)

{
	setName(name);
	setActive(active);
}

GameObject::~GameObject()
{
	//cout << getName() << endl;

	//cout << "child count: " << m_ChildCount << endl;

	for (int i = 0; i < m_Children.size(); i++)
	{
		delete m_Children[i];

		//cout << "deleting: " << i << endl;
	}
	m_Children.clear();

	m_Parent = nullptr;
}

void GameObject::setRenderingEngine(RenderingEngine* renderer)
{
	this->renderer = renderer;
}

void GameObject::addChild(GameObject *child)
{
	
	if (child != nullptr)
	{
		if (child->getParent() != nullptr)
		{
			child->setParent(this);
		}

		this->vertices_count += child->getVerticesCount();
		this->indices_count += child->getIndicesCount();
		this->faces_count += child->getFacesCount();

		m_Children.push_back(child);
		m_ChildCount++;

;
	}
}

void GameObject::removeChild(GameObject *child)
{
	
	if (child != nullptr && !m_Children.empty())
	{
		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			delete m_Children[i];
			m_Children.erase(m_Children.begin() + i);
			m_ChildCount--;
			break;
		}
	}

}

GameObject* GameObject::getParent(void) const
{
	return m_Parent;
}

void GameObject::setParent(GameObject *parent)
{
	if (m_Parent == nullptr)
	{
		m_Parent->removeChild(this);
	}
	m_Parent = parent;
}

GameObject* GameObject::getChild(unsigned int i)
{
	if (!(m_Children.size() < i || m_Children.empty()))
	{
		return m_Children[i];
	}

	return nullptr;
}

void GameObject::setName(const std::string& name)
{
	m_Name = name;
}

std::string GameObject::getName(void)
{
	return m_Name;
}

void GameObject::setActive(bool active)
{
	m_Active = active;
}

bool GameObject::isActive(void)
{
	return m_Active;
}

unsigned int GameObject::getChildCount(void)
{
	return m_ChildCount;
}

unsigned int& GameObject::getVerticesCount(void)
{
	return vertices_count;
}

unsigned int& GameObject::getIndicesCount(void)
{
	return indices_count;
}

unsigned int& GameObject::getFacesCount(void)
{
	return faces_count;
}

void GameObject::update(WindowEngine* window)
{
	if (!m_Children.empty())
	{
		for (int i = 0; i < m_ChildCount; i++)
		{
			if (isActive()) m_Children[i]->update(window);
		}
	}
}

void GameObject::render()
{
	if (!m_Children.empty())
	{
		for (auto i = 0; i < m_Children.size(); ++i)
		{
			if (isActive()) m_Children[i]->render();
		}
	}
}

void GameObject::render(ShaderProgram* program, RenderingEngine* renderer)
{
	if (!m_Children.empty())
	{
		for (int i = 0; i < m_ChildCount; i++)
		{
			if (isActive()) m_Children[i]->render(program, renderer);
		}
	}
}


