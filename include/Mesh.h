#pragma once

#include <vector>
#include <memory>
#include <ngl/Obj.h>
#include <ngl/Mat4.h>
#include <Skeleton/Skeleton.h>

class Mesh : ngl::Obj
{
public:
	Mesh() : ngl::Obj(), m_skeleton(new Skeleton()) {}
	Mesh(const Mesh&);
	Mesh(const std::string& _fname, CalcBB _calcBB = CalcBB::False);

	virtual bool load(const std::string& _fname, CalcBB _calcBB = CalcBB::True) noexcept override;
	void updateMesh();

	void drawSolid(const ngl::Mat4& _view, const ngl::Mat4& _project, const char* const _shader) const;
	void drawWire(const ngl::Mat4& _view, const ngl::Mat4& _project, const char* const _shader) const;
	void drawSkeleton(const ngl::Mat4& _view, const ngl::Mat4& _project, const char* const _shader) const;

private:
	//std::unique_ptr<ngl::AbstractVAO> m_vaoWire();
	void createWireVAO(ResetVAO _reset = ResetVAO::False);
	void loadMatricesToShader(const ngl::Mat4& _view, const ngl::Mat4& _project) const;

	std::unique_ptr<Skeleton> m_skeleton;
};