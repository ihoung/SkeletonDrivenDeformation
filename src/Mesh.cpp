#include "Mesh.h"
#include <ngl/ShaderLib.h>
#include <ngl/VAOFactory.h>


Mesh::Mesh(const Mesh& other) : ngl::Obj(other)
{

}

Mesh::Mesh(const std::string& _fname, CalcBB _calcBB) : ngl::Obj(_fname, _calcBB), m_skeleton(new Skeleton())
{
    updateMesh();
}

bool Mesh::load(const std::string& _fname, CalcBB _calcBB) noexcept
{
    bool _ret = __super::load(_fname, _calcBB);
    m_skeleton.reset(new Skeleton());
    updateMesh();
    return _ret;
}

void Mesh::updateMesh()
{
    createVAO(ResetVAO::True);
    createWireVAO(ResetVAO::True);
}

void Mesh::createWireVAO(ResetVAO _reset)
{
    //if (_reset == ResetVAO::False)
    //{
    //    if (m_vaoWire) return;
    //}

    //std::vector< VertData > vboWire;
    //VertData d;

    //for (auto face : m_face)
    //{
    //    for (unsigned int j = 0; j < 3; ++j)
    //    {

    //        // pack in the vertex data first
    //        d.x = m_verts[face.m_vert[j]].m_x;
    //        d.y = m_verts[face.m_vert[j]].m_y;
    //        d.z = m_verts[face.m_vert[j]].m_z;
    //        vboWire.push_back(d);
    //    }
    //}


}

void Mesh::loadMatricesToShader(const ngl::Mat4& _view, const ngl::Mat4& _project) const
{
    struct transform
    {
        ngl::Mat4 MVP;
        ngl::Mat4 normalMatrix;
        ngl::Mat4 M;
    };

    transform t;
    t.M = _view;

    t.MVP = _project * t.M;
    t.normalMatrix = t.M;
    t.normalMatrix.inverse().transpose();
    ngl::ShaderLib::setUniformBuffer("TransformUBO", sizeof(transform), &t.MVP.m_00);

    //ngl::ShaderLib::setUniform("lightPosition", (m_mouseGlobalTX * m_lightPos).toVec3());
}

bool Mesh::hasSkeletonRoot()
{
    return m_skeleton->hasRoot();
}

int Mesh::createBone(int parentId)
{
    return m_skeleton->addBone(parentId);
}

void Mesh::deleteBone(int boneId)
{
    m_skeleton->removeBone(boneId);
}

Bone* Mesh::getBone(int id)
{
    return m_skeleton->getBone(id);
}

void Mesh::setSkeletonMode(Skeleton::DisplayMode _mode)
{
    m_skeleton->setDisplayMode(_mode);
}

void Mesh::drawSolid(const ngl::Mat4& _view, const ngl::Mat4& _project, const char* const _shader) const
{
    ngl::ShaderLib::use(_shader);
	loadMatricesToShader(_view, _project);

    ngl::ShaderLib::setUniform("lightDirection", ngl::Vec3(1.0f, -1.0f, 1.0f));
    ngl::ShaderLib::setUniform("lightColor", ngl::Vec3(1.0f));
    ngl::ShaderLib::setUniform("baseColor", ngl::Vec3(1.0f));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPointSize(3);
    m_vaoMesh->setMode(GL_TRIANGLES);
    m_vaoMesh->bind();
	glEnable(GL_PROGRAM_POINT_SIZE);
    m_vaoMesh->draw();
	glDisable(GL_PROGRAM_POINT_SIZE);
    m_vaoMesh->unbind();
}

void Mesh::drawWire(const ngl::Mat4& _view, const ngl::Mat4& _project, const char* const _shader) const
{
    ngl::ShaderLib::use(_shader);
    loadMatricesToShader(_view, _project);

    ngl::ShaderLib::setUniform("lightDirection", ngl::Vec3(1.0f, -1.0f, 1.0f));
    ngl::ShaderLib::setUniform("lightColor", ngl::Vec3(1.0f));
    ngl::ShaderLib::setUniform("baseColor", ngl::Vec3(0.0f, 0.0f, 0.7f));

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(3);
    m_vaoMesh->setMode(GL_TRIANGLES);
    m_vaoMesh->bind();
    glEnable(GL_PROGRAM_POINT_SIZE);
    m_vaoMesh->draw();
    glDisable(GL_PROGRAM_POINT_SIZE);
    m_vaoMesh->unbind();
}

void Mesh::drawSkeleton(const ngl::Mat4& _view, const ngl::Mat4& _project, const char* const _shader) const
{
    ngl::ShaderLib::use(_shader);

    ngl::ShaderLib::setUniform("MVP", _project * _view);
    m_skeleton->draw();
}
