#include "RenderModel.h"

RenderModel::RenderModel() {}

RenderModel::~RenderModel() {
	destroy();
}

void RenderModel::draw() {}

void RenderModel::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix) {}

void RenderModel::update() {}

void RenderModel::destroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();

	for(auto t : textures) {
		glDeleteTextures(1, &t.second);
	}
	textures.clear();
}

void RenderModel::setProgram(GLuint program) {
	if(program == 0) {
		return;
	}
	this->program = program;
}

void RenderModel::setTexture(const std::string& textureName, GLuint texture) {
	if(texture == 0) {
		return;
	}
	textures[textureName] = texture;
}

GLuint RenderModel::getVao() const {
	return vao;
}

const std::vector<GLuint>& RenderModel::getVbos() const {
	return vbos;
}

const GLuint RenderModel::getTexture(const std::string& textureName) const {
	return textures.at(textureName);
}