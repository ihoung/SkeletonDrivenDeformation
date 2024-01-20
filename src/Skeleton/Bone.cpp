#include "Skeleton/Bone.h"
#include <ngl/VAOFactory.h>
#include <ngl/Util.h>
#include "MathUtils.h"

Bone::Bone(std::string _name, Bone* _parent) :m_name(_name), m_parent(_parent), m_mode(DisplayMode::Init),
m_boneVAO(ngl::VAOFactory::createVAO(ngl::simpleIndexVAO, GL_LINES))
{
}

Bone::Bone(std::string _name, Bone* _parent, ngl::Transformation _transform) :m_name(_name), m_mode(DisplayMode::Init),
m_parent(_parent), m_originTrans(_transform), m_boneVAO(ngl::VAOFactory::createVAO(ngl::simpleIndexVAO, GL_LINES))
{
}

void Bone::rename(std::string _name)
{
	m_name = _name;
}

void Bone::resetInitTransform(ngl::Transformation _transform)
{
	m_originTrans = _transform;

	if (m_mode == DisplayMode::Init)
	{
		buildVAO(true);
	}
}

void Bone::setCurrentTransform(ngl::Transformation _transform)
{
	m_curTrans = _transform;

	if (m_mode == DisplayMode::Current)
	{
		buildVAO(false);
	}
}

void Bone::setMode(DisplayMode _mode)
{
	m_mode = _mode;
	buildVAO(m_mode == DisplayMode::Init);
}

// rendering
void Bone::buildVAO(bool isInit)
{
	ngl::Vec3 startPos = isInit ? m_originTrans.getPosition() : m_curTrans.getPosition();
	float radius = 0.05f;
	// sphere
	float offset = radius * sin(ngl::radians(45));
	std::vector<ngl::Vec3> vertices{
		{0.0f, radius, 0.0f}, {-offset, offset, 0.0f}, {-radius, 0.0f, 0.0f},{-offset, -offset, 0.0f},
		{0.0f, -radius, 0.0f}, {offset, -offset, 0.0f}, {radius, 0.0f, 0.0f}, {offset, offset, 0.0f},
		{-offset, 0.0f, -offset}, {0.0f, 0.0f, -radius}, {offset, 0.0f, -offset}, {offset, 0.0f, offset},
		{0.0f, 0.0f, radius}, {-offset, 0.0f, offset}, {0.0f, offset, -offset}, {0.0f, -offset, -offset},
		{0.0f, -offset, offset}, {0.0f, offset, offset},
	};
	for (int i = 0; i < vertices.size(); ++i)
	{
		vertices[i] += startPos;
	}
	std::vector<GLushort> indicies{ 0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,0,
		2,8,8,9,9,10,10,6,6,11,11,12,12,13,13,2,
		0,14,14,9,9,15,15,4,4,16,16,12,12,17,17,0
	};

	// pyramid
	std::vector<ngl::Vec3> pyramidBase_vert{
		{radius, radius, radius}, {-radius, radius, radius},
		{-radius, radius, -radius}, {radius, radius, -radius},
	};
	std::vector<GLushort> pyramid_indices{ 0,1,1,2,2,3,3,0,0,3,1,2,0,4,1,4,2,4,3,4 };
	for (int i=0; i<m_childBones.size(); ++i)
	{
		ngl::Vec3 endPos = isInit ? 
			m_childBones[i]->m_originTrans.getPosition() : m_childBones[i]->m_curTrans.getPosition();
		ngl::Vec3 direction = endPos - startPos;
		float distance = direction.length();
		ngl::Quaternion q = MathUtils::QuaternionFromTwoVectors(ngl::Vec3({ 0,1,0 }), direction);
		std::vector<ngl::Vec3> pyramid_vert;
		for (auto vertex : pyramidBase_vert)
		{
			ngl::Vec4 rel_direction = (q * ngl::Vec4{ vertex, 0.0f }).normalize();
			pyramid_vert.push_back(rel_direction.toVec3() * vertex.length() + startPos);
		}
		vertices.insert(vertices.end(), pyramid_vert.begin(), pyramid_vert.end());
		vertices.push_back(endPos);
		for (auto j : pyramid_indices)
		{
			indicies.push_back(j + 18 + i * pyramid_indices.size());
		}
	}

	m_boneVAO->bind();
	m_boneVAO->setData(ngl::SimpleIndexVAO::VertexData(
		vertices.size() * sizeof(ngl::Vec3), vertices[0].m_x,
		indicies.size(), &indicies[0], GL_UNSIGNED_SHORT
	));
	m_boneVAO->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(ngl::Vec3), 0);
	m_boneVAO->setNumIndices(indicies.size());
	m_boneVAO->unbind();
}

void Bone::draw()
{
	glPointSize(3);
	m_boneVAO->bind();
	glEnable(GL_PROGRAM_POINT_SIZE);
	m_boneVAO->draw();
	glDisable(GL_PROGRAM_POINT_SIZE);
	m_boneVAO->unbind();
}
