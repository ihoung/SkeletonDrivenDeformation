#include <format>
#include "Skeleton/Skeleton.h"

bool Skeleton::hasRoot()
{
	return m_root.lock() != nullptr;
}

int Skeleton::addBone(int parentId)
{
	if (parentId == -1)
	{
		std::shared_ptr<Bone> root = std::make_shared<Bone>(0, "root", nullptr);
		m_bones[0] = root;
		m_root = m_bones[0];
		return 0;
	}

	int boneId = m_bones.rbegin()->first + 1;
	std::string default_name = "bone" + std::to_string(boneId);
	Bone* parent = m_bones[parentId].get();
	std::shared_ptr<Bone> childBone = std::make_shared<Bone>(boneId, default_name, parent);
	parent->addChildBone(childBone.get());
	m_bones[boneId] = (childBone);
	return boneId;
}

void Skeleton::removeBone(int id)
{
	if (m_bones.find(id) == m_bones.end()) return;

	Bone* bone = m_bones[id].get();
	removeBone(bone);
}

void Skeleton::removeBone(Bone* bone)
{
	for (Bone* child : bone->getChildBones())
	{
		removeBone(child);
	}
	Bone* parent = bone->getParent();
	if (parent)
	{
		parent->removeChildBone(bone);
	}
	m_bones.erase(bone->getID());
}

Bone* Skeleton::getBone(int id)
{
	if (m_bones.find(id) == m_bones.end()) return nullptr;
	return m_bones[id].get();
}

void Skeleton::setDisplayMode(DisplayMode _mode)
{
	m_displayMode = _mode;
}

void Skeleton::draw()
{
	if (!m_root.lock()) return;

	//m_root.lock()->buildVAO(true);
	//m_root.lock()->draw();

	for (auto boneData : m_bones)
	{
		Bone* bone = boneData.second.get();
		bone->buildVAO(m_displayMode == DisplayMode::Init);
		bone->draw();
	}
}

