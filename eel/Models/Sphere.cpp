#include "Sphere.h"

Sphere::Sphere() : RenderModel() {}
Sphere::~Sphere() {}

void Sphere::create(GLfloat radius, GLuint rings, GLuint sectors, const glm::vec4& color) {
	std::vector<VertexFormat> vertices;
	std::vector<GLuint> indices;

	const double ringsRecip = 1.0 / (double) (rings - 1);
	const double sectorsRecip = 1.0 / (double) (sectors - 1);

	for(unsigned int i = 0; i < rings; i++) {
		const double y = sin(-M_PI / 2 + M_PI * i * ringsRecip) * radius;
		for(unsigned int j = 0; j < sectors; j++) {
			const double x = cos(2 * M_PI * j * sectorsRecip) * sin(M_PI * i * ringsRecip);
			const double z = sin(2 * M_PI * j * sectorsRecip) * sin(M_PI * i * ringsRecip);

			glm::vec3 pos((float) (x * radius), (float) (y), (float) (z * radius));
			glm::vec2 tex((float) (j * sectorsRecip), (float) (i * ringsRecip));
			vertices.push_back(VertexFormat(pos, tex, color));
		}
	}

	for(unsigned int i = 0; i < rings-1; i++) {
		for(unsigned int j = 0; j < sectors-1; j++) {
			indices.push_back(i * sectors + j);
			indices.push_back(i * sectors + j + 1);
			indices.push_back((i + 1) * sectors + j + 1);
			indices.push_back(i * sectors + j);
			indices.push_back((i + 1) * sectors + j + 1);
			indices.push_back((i + 1) * sectors + j);
		}
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	setAttribPointers();

	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
	indicesCount = indices.size();
}

void Sphere::update(const float totalTimePassed, const float deltaTime, const bool force) {
	if(animated) {
		rotate(deltaTime);
	}
}

void Sphere::draw(const GLuint program) {
	glBindVertexArray(vao);

	setPositionUniforms(program);
	setMaterialUniforms(program);

	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}
