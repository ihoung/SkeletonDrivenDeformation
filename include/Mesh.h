#pragma once

#include <string>
#include <vector>
#include <memory>
#include <ngl/Obj.h>
#include <ngl/Mat4.h>

class Mesh : ngl::Obj
{
public:
	Mesh() : ngl::Obj() {}
	Mesh(const Mesh&);
	Mesh(const std::string& _fname, CalcBB _calcBB = CalcBB::False);

	virtual bool load(const std::string& _fname, CalcBB _calcBB = CalcBB::True) noexcept override;
	void updateMesh();

	void drawSolid(const ngl::Mat4& _view, const ngl::Mat4& _project, const char* const _shader) const;
	void drawWire(const ngl::Mat4& _view, const ngl::Mat4& _project, const char* const _shader) const;

private:

	void loadMatricesToShader(const ngl::Mat4& _view, const ngl::Mat4& _project) const;
};