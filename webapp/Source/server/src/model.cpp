#include "../include/model.h"

Model::Model():is_existing(false) {}

Model::~Model() {}

bool Model::exists() {
	return is_existing;
}

void Model::exists(bool flag) {
	is_existing = flag;
}
