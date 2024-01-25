#pragma once

#include <map>
#include "Skeleton/Bone.h"

class Skeleton
{
public:
	enum DisplayMode
	{
		Init,
		Current,
	};

	Skeleton() = default;
	bool hasRoot();
	int addBone(int);
	void removeBone(int);
	Bone const* getBone(int);
	void setDisplayMode(DisplayMode);
	void draw();

private:
	std::weak_ptr<Bone> m_root;
	std::map<int, std::shared_ptr<Bone>> m_bones;

	void removeBone(Bone*);
};