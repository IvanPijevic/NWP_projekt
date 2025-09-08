#ifndef GLSL_H
#define GLSL_H

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <vector>

#include "Error.h"

namespace Engine
{

	class GLSL
	{
	public:
		GLSL();
		~GLSL();

		void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void LinkShaders();
		void AddAttribute(const std::string& attributeName);
		GLint getUniformLocation(const std::string& uniformName);

		void Use();
		void Unuse();

	private:
		void CompileShader(const std::string& filePath, GLuint id);

		int m_numAttributes;

		GLuint m_programID;
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
	};

}
#endif  //GLSL_H