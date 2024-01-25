#pragma once
#include <memory>
#include <vector>
#include <ngl/Transformation.h>
#include <ngl/SimpleIndexVAO.h>

class Bone
{
public:

	Bone() = default;
	Bone(const Bone&) = default;
	Bone(std::string _name, Bone* _parent);
	Bone(std::string _name, Bone* _parent, ngl::Transformation _transform);
	void rename(std::string _name);
	void resetInitTransform(ngl::Transformation _transform);
	void setCurrentTransform(ngl::Transformation _transform);
	std::string getName() const;
	ngl::Transformation getInitTransform() const;
	ngl::Transformation getCurTransform() const;
	const std::vector<Bone*>& getChildBones() const;
	Bone* getParent() const;
	void addChildBone(Bone* childBone);
	void removeChildBone(Bone* childBone);
	// rendering
	void buildVAO(bool isInit = true);
	void draw();

private:
	std::string m_name;
	ngl::Transformation m_initTrans;
	ngl::Transformation m_curTrans;

	std::vector<Bone*> m_childBones;
	Bone* m_parent;

	// rendering
	std::shared_ptr<ngl::AbstractVAO> m_boneVAO;
};