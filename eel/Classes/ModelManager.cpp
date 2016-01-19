#include "ModelManager.h"

ModelManager::ModelManager() {
	Triangle* t3 = new Triangle();
	t3->setProgram(ShaderManager::getProgram("simpleColorShader"));
	t3->create();
	modelListNDC["triangle1"] = t3;

	Tetragon* t4 = new Tetragon();
	t4->setProgram(ShaderManager::getProgram("simpleColorShader"));
	t4->create();
	modelListNDC["tetragon1"] = t4;
}

ModelManager::~ModelManager() {
	for(auto model : modelList) {
		delete model.second;
	}
	modelList.clear();
	for(auto model : modelListNDC) {
		delete model.second;
	}
	modelListNDC.clear();
}

void ModelManager::draw() {
	for(auto model : modelListNDC) {
		model.second->draw();
	}
}

void ModelManager::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & viewMatrix) {
	for(auto model : modelList) {
		model.second->draw(projectionMatrix, viewMatrix);
	}
}

void ModelManager::update() {
	for(auto model : modelList) {
		model.second->update();
	}
	for(auto model : modelListNDC) {
		model.second->update();
	}
}

void ModelManager::deleteModel(const std::string& modelName) {
	std::map<std::string, RenderObject*>::iterator it;
	it = modelList.find(modelName);
	if(it == modelList.end()) {
		return;
	}

	it->second->destroy();
	modelList.erase(it);
}

void ModelManager::deleteNDCModel(const std::string& modelName) {
	std::map<std::string, RenderObject*>::iterator it;
	it = modelListNDC.find(modelName);
	if(it == modelListNDC.end()) {
		return;
	}

	it->second->destroy();
	modelListNDC.erase(it);
}

const RenderObject& ModelManager::getModel(const std::string& modelName) {
	return (*modelList.at(modelName));
}

const RenderObject & ModelManager::getNDCModel(const std::string& modelName) {
	return (*modelListNDC.at(modelName));
}

void ModelManager::setModel(const std::string& modelName, RenderObject* modelObject) {
	modelList[modelName.c_str()] = modelObject;
}