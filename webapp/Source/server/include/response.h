#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>

#include "cpprest/json.h"

#include "constants.h"

enum class ErrorCode {
	UnknownError,
	PathMissing,
	PathNotFound,
	AuthenticationFailed,
	TraderAlreadyRegistered,
	ParameterMissingUsername,
	ParameterMissingPassword,
	ParameterMissingStockCode,
	ParameterMissingQuantity,
	ParameterMissingPrice,
	ParameterInvalidUsername,
	ParameterInvalidPassword,
	ParameterInvalidStockCode,
	ParameterInvalidQuantity,
	ParameterInvalidPrice,
	RecordNotFoundTransaction,
	RecordNotFoundTrader,
	RecordNotFoundPortfolio,
	RecordNotFoundStock,
	NotEnoughPortfolioQuantity,
	NotEnoughTraderBalanceCash
};

typedef std::map<ErrorCode, std::string> errormap;

class Response {
private:
	web::json::value obj;

	static errormap init_messages();

	void set_success(bool flag);
	void set_payload(web::json::value payload);
	void set_error(int code, std::string message);
public:
	static errormap message_map;

	Response();
	~Response();

	web::json::value &success();
	web::json::value &success(web::json::value payload);
	web::json::value &failure(ErrorCode code);
	web::json::value &failure(int code, std::string message);
};

#endif /* RESPONSE_H */
