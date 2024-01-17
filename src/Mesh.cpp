#include "Mesh.h"
#include <ngl/ShaderLib.h>


Mesh::Mesh(const Mesh& other) : ngl::Obj(other)
{

}

Mesh::Mesh(const std::string& _fname, CalcBB _calcBB) : ngl::Obj(_fname, _calcBB)
{
    updateMesh();
}

bool Mesh::load(const std::string& _fname, CalcBB _calcBB) noexcept
{
    bool _ret = __super::load(_fname, _calcBB);
    updateMesh();
    return _ret;
}

void Mesh::updateMesh()
{
    createVAO(ResetVAO::True);
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

void Mesh::drawSolid(const ngl::Mat4& _view, const ngl::Mat4& _project, const char* const _shader) const
{
    ngl::ShaderLib::use(_shader);
	loadMatricesToShader(_view, _project);

    ngl::ShaderLib::setUniform("lightDirection", ngl::Vec3(1.0f, -1.0f, 1.0f));
    ngl::ShaderLib::setUniform("lightColor", ngl::Vec3(1.0f));
    ngl::ShaderLib::setUniform("baseColor", ngl::Vec3(1.0f));

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
    ngl::ShaderLib::setUniform("lightColor", ngl::Vec3(0.0f));
    ngl::ShaderLib::setUniform("baseColor", ngl::Vec3(0.0f));

    glPointSize(3);
    m_vaoMesh->setMode(GL_LINE_STRIP);
    m_vaoMesh->bind();
    glEnable(GL_PROGRAM_POINT_SIZE);
    m_vaoMesh->draw();
    glDisable(GL_PROGRAM_POINT_SIZE);
    m_vaoMesh->unbind();
}
