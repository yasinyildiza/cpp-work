#include <iostream>

#include "Worker.h"

Worker::Worker(int parameter) {
	xid = parameter;
}

void Worker::work(int parameter) {
	if(delegate) {
		if(xid == parameter) {
			delegate->workerNotifiesDelegateOK(this);
		} else {
			delegate->workerNotifiesDeleagateNOK(this);
		}
	} else {
		printLog("No delegate assinged to Worker");
	}

	if(anotherDelegate) {
		std::string key = anotherDelegate->workerRequestDelegateKey(this);
		std::string value = anotherDelegate->workerRequestDelegateValue(this);
		printLog("anotherDelegate declared value " + value + " for key " + key);
	} else {
		printLog("No anotherDelegate assinged to Worker");
	}
}

Worker::~Worker() {}