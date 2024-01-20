#include "Skeleton/Skeleton.h"

void Skeleton::addBone(Bone* parent, std::string name)
{
	if (parent == nullptr)
	{
		m_root.reset(new Bone("root", nullptr));
	}
}

void Skeleton::draw()
{
	m_root.reset(new Bone("root", nullptr));
	m_root->buildVAO(true);
	m_root->draw();
}
