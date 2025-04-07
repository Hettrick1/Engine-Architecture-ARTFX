#pragma once

#include "glew.h"

#include "Shader.h"

#include "Matrix4DRow.h"
#include "Matrix4D.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include <vector>

namespace ShaderProgramType {
	enum Type {
		VERTEX = 1 << 0,
		FRAGMENT = 1 << 1,
		TESSELLATION_CONTROL = 1 << 2,
		TESSELLATION_EVALUATION = 1 << 3,
		GEOMETRY = 1 << 4
	};
	inline uint8_t operator + (uint8_t& a, Type& b) {
		return a | static_cast<uint8_t>(b);
	}

	inline uint8_t operator - (uint8_t& a, Type& b) {
		return a ^ static_cast<uint8_t>(b);
	}
	inline void operator += (uint8_t& a, Type b) {
		a |= static_cast<uint8_t>(b);
	}

	inline void operator -= (uint8_t& a, Type b) {
		a ^= static_cast<uint8_t>(b);
	}
}

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram() = default;
	void Unload();
	void Compose(std::vector<Shader*> shaders);

	unsigned int GetID();
	inline uint8_t GetType() const { return mShaderProgramType; }
	void Use();
	void setFloat(const GLchar* name, GLfloat value);
	void setInteger(const GLchar* name, GLint value);
	void setVector2f(const GLchar* name, GLfloat x, GLfloat y);
	void setVector2f(const GLchar* name, const Vector2D& value);
	void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);
	void setVector3f(const GLchar* name, const Vector3D& value);
	void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setVector4f(const GLchar* name, const Vector4D& value);
	void setMatrix4(const GLchar* name, const Matrix4D& matrix);
	void setMatrix4Row(const GLchar* name, const Matrix4DRow& matrix);

private:
	unsigned int mId;
	uint8_t mShaderProgramType;
};