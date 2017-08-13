#ifndef OWNER_H
#define OWNER_H

#include "Helper.h"
#include "Worker.h"

class Owner : public Protocol, public AnotherProtocol {
	public:
		int xid;
		Worker *worker;
		Owner(int parameter);
		void workerNotifiesDelegateOK(Worker *worker);
		void workerNotifiesDeleagateNOK(Worker *worker);
		std::string workerRequestDelegateKey(Worker *worker);
		std::string workerRequestDelegateValue(Worker *worker);
		void doSomething(int parameter);
		~Owner();
};

#endif