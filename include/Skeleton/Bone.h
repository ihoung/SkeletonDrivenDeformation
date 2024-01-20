#pragma once
#include <memory>
#include <vector>
#include <ngl/Transformation.h>
#include <ngl/SimpleIndexVAO.h>

class Bone
{
public:
	enum DisplayMode
	{
		Init,
		Current,
	};

	Bone() = default;
	Bone(const Bone&) = default;
	Bone(std::string _name, Bone* _parent);
	Bone(std::string _name, Bone* _parent, ngl::Transformation _transform);
	void rename(std::string _name);
	void resetInitTransform(ngl::Transformation _transform);
	void setCurrentTransform(ngl::Transformation _transform);
	void setMode(DisplayMode _mode);
	// rendering
	void buildVAO(bool isInit = true);
	void draw();

private:
	std::string m_name;
	ngl::Transformation m_originTrans;
	ngl::Transformation m_curTrans;
	DisplayMode m_mode;

	std::vector<std::shared_ptr<Bone>> m_childBones;
	std::unique_ptr<Bone> m_parent;

	// rendering
	std::shared_ptr<ngl::AbstractVAO> m_boneVAO;
};