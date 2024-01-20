#pragma once

#include "Skeleton/Bone.h"

class Skeleton
{
public:
	Skeleton() = default;
	void addBone(Bone* parent, std::string name);
	void draw();

private:
	std::unique_ptr<Bone> m_root;
};