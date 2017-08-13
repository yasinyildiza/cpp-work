#ifndef WORKER_H
#define WORKER_H

#include "Helper.h"

class Worker;
class Protocol;
class AnotherProtocol;

class Protocol {
	public:
		Protocol(){};
		virtual void workerNotifiesDelegateOK(Worker *worker) = 0;
		virtual void workerNotifiesDeleagateNOK(Worker *worker) = 0;
		~Protocol(){};
};

class AnotherProtocol {
	public:
		AnotherProtocol(){};
		virtual std::string workerRequestDelegateKey(Worker *worker) = 0;
		virtual std::string workerRequestDelegateValue(Worker *worker) = 0;
		~AnotherProtocol(){};
};

class Worker {
	public:
		Protocol *delegate;
		AnotherProtocol *anotherDelegate;
		int xid;
		Worker(int parameter);
		void work(int parameter);
		~Worker();
};

#endif