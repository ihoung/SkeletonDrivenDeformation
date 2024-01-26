#pragma once
#include <memory>
#include <vector>
#include <ngl/Transformation.h>
#include <ngl/SimpleIndexVAO.h>

class Bone
{
public:
	enum Selection
	{
		Unselected,
		Selected
	};

	Bone() = default;
	Bone(const Bone&) = default;
	Bone(int _id, std::string _name, Bone* _parent);
	Bone(int _id, std::string _name, Bone* _parent, ngl::Transformation _transform);
	void rename(std::string _name);
	void resetInitTransform(ngl::Transformation _transform);
	void setCurrentTransform(ngl::Transformation _transform);
	int getID() const;
	std::string getName() const;
	ngl::Transformation getInitTransform() const;
	ngl::Transformation getCurTransform() const;
	const std::vector<Bone*>& getChildBones() const;
	Bone* getParent() const;
	void addChildBone(Bone* childBone);
	void removeChildBone(Bone* childBone);
	void setSelection(bool isSelected);
	bool isSelected() const;

	// rendering
	void buildVAO(bool isInit = true);
	void draw();

private:
	int m_id;
	std::string m_name;
	ngl::Transformation m_initTrans;
	ngl::Transformation m_curTrans;

	std::vector<Bone*> m_childBones;
	Bone* m_parent;

	// rendering
	Selection m_select;
	std::unique_ptr<ngl::AbstractVAO> m_boneVAO;
};