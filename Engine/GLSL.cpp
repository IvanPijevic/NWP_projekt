#include "GLSL.h"

namespace Engine
{

	GLSL::GLSL() :
		m_numAttributes(0),
		m_programID(0),
		m_vertexShaderID(0),
		m_fragmentShaderID(0)
	{}

	GLSL::~GLSL()
	{

	}

	void GLSL::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		m_programID = glCreateProgram();

		m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (m_vertexShaderID == 0)
		{
			fatalError("Vertex shader failed to be created!");
		}

		m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_fragmentShaderID == 0)
		{
			fatalError("Fragment shader failed to be created!");
		}

		CompileShader(vertexShaderFilePath, m_vertexShaderID);
		CompileShader(fragmentShaderFilePath, m_fragmentShaderID);

	}

	void GLSL::LinkShaders()
	{
		glAttachShader(m_programID, m_vertexShaderID);
		glAttachShader(m_programID, m_fragmentShaderID);

		glLinkProgram(m_programID);

		//Error check
		GLint isLinked = 0;
		glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char>errorLog(maxLength);
			glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);


			glDeleteProgram(m_programID);

			glDeleteShader(m_vertexShaderID);
			glDeleteShader(m_fragmentShaderID);

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader failed to link!");
		}

		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);
	}

	GLint GLSL::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform " + uniformName + " not found in shader!");
		}

		return location;
	}

	void GLSL::Use()
	{
		glUseProgram(m_programID);
		for (int i = 0; i < m_numAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSL::Unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < m_numAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	void GLSL::CompileShader(const std::string& filePath, GLuint id)
	{
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail())
		{
			fatalError("Failed to open " + filePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(vertexFile, line))
		{
			fileContents += line + "\n";
		}

		vertexFile.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//Provide the infolog in whatever manoe you deem best.
			//Exit with failure
			glDeleteShader(id);    //Don't leak the shader

			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + filePath + " failed to compile");
		}
	}

	void GLSL::AddAttribute(const std::string& attributeName)
	{
		glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
	}

}