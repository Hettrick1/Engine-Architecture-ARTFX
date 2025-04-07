#pragma once

#include <string>
#include <fstream>

enum class ShaderType {
	VERTEX,
	FRAGMENT,
	TESSELLATION_CONTROL,
	TESSELLATION_EVALUATION,
	GEOMETRY
};
class Shader
{
public:
	static const std::string SHADER_PATH;
	Shader();
	Shader(int pId, std::string pCode, ShaderType pShaderType);
	~Shader();

	void Load(std::string pFileName, ShaderType pShaderType);

	int GetID() const 
	{
		return mId;
	}

	std::string& GetCode();

	inline ShaderType GetType() const { return mType; }
protected:
	std::string mCode;
	unsigned int mId;
	ShaderType mType;
	const char* mSource;
};