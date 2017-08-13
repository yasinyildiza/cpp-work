#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>

#include "cpprest/json.h"

#include "constants.h"
#include "connector.h"

class Model {
private:
	bool is_existing;

protected:
	void exists(bool flag);

public:
	Model();
	~Model();

	bool exists();

	virtual web::json::value to_json() = 0;
};

#endif /* MODEL_H */
