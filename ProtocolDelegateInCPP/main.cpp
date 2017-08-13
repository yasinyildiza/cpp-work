#include <iostream>

#include "Owner.h"

int main(void) {
	Owner *owner = new Owner(5);
	owner->doSomething(5);
	delete owner;
	return 0;
}