#include "ShaderLoader.h"

ShaderLoader::ShaderLoader() {}
ShaderLoader::~ShaderLoader() {}

std::string ShaderLoader::readShader(char* filename) {
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);
	if(!file.good()) {
		std::cout << "ERROR reading shader: " << filename << "\n";
		std::terminate();
	}
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderLoader::createShader(GLenum shaderType, std::string source, char* shaderName) {
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();
	GLuint shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	int compile_result = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	if (compile_result == GL_FALSE)	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName << "\n" << &shader_log[0] << "\n";
		return 0;
	}
	return shader;
}

GLuint ShaderLoader::createProgram(char* vertexShaderFilename, char* fragmentShaderFilename) {
	std::string vertex_shader_code = readShader(vertexShaderFilename);
	std::string fragment_shader_code = readShader(fragmentShaderFilename);
	GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE) {
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "ERROR linking shader.\n" << &program_log[0] << "\n";
		return 0;
	}
	return program;
}