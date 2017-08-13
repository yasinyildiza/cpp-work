#include "../include/response.h"

errormap Response::message_map = Response::init_messages();

Response::Response():obj(web::json::value::object()) {}

Response::~Response() {}

errormap Response::init_messages() {
	errormap m;

	m[ErrorCode::UnknownError] = "Unknown Error";
	m[ErrorCode::PathMissing] = "Path Missing";
	m[ErrorCode::PathNotFound] = "Path Not Found";
	m[ErrorCode::AuthenticationFailed] = "Authentication Failed";
	m[ErrorCode::TraderAlreadyRegistered] = "Trader Already Registered";
	m[ErrorCode::ParameterMissingUsername] = "Parameter Missing: Username";
	m[ErrorCode::ParameterMissingPassword] = "Parameter Missing: Password";
	m[ErrorCode::ParameterMissingStockCode] = "Parameter Missing: StockCode";
	m[ErrorCode::ParameterMissingQuantity] = "Parameter Missing: Quantity";
	m[ErrorCode::ParameterMissingPrice] = "Parameter Missing: Price";
	m[ErrorCode::ParameterInvalidUsername] = "Parameter Invalid: Username";
	m[ErrorCode::ParameterInvalidPassword] = "Parameter Invalid: Password";
	m[ErrorCode::ParameterInvalidStockCode] = "Parameter Invalid: StockCode";
	m[ErrorCode::ParameterInvalidQuantity] = "Parameter Invalid: Quantity";
	m[ErrorCode::ParameterInvalidPrice] = "Parameter Invalid: Price";
	m[ErrorCode::RecordNotFoundTransaction] = "Record Not Found: Transaction";
	m[ErrorCode::RecordNotFoundTrader] = "Record Not Found: Trader";
	m[ErrorCode::RecordNotFoundPortfolio] = "Record Not Found: Portfolio";
	m[ErrorCode::RecordNotFoundStock] = "Record Not Found: Stock";
	m[ErrorCode::NotEnoughPortfolioQuantity] = "Not Enough Portfolio Quantity";
	m[ErrorCode::NotEnoughTraderBalanceCash] = "Not Enough Trader BalanceCash";

	return m;
}

void Response::set_success(bool flag) {
	obj[KEY_SUCCESS] = web::json::value::boolean(flag);
}

void Response::set_payload(web::json::value payload) {
	obj[KEY_PAYLOAD] = payload;
}

void Response::set_error(int code, std::string message) {
	web::json::value error = web::json::value::object();
	error[KEY_CODE] = web::json::value::number(code);
	error[KEY_MESSAGE] = web::json::value::string(message);
	obj[KEY_ERROR] = error;
}

web::json::value &Response::success() {
	return success(web::json::value::object());
}

web::json::value &Response::success(web::json::value payload) {
    set_success(true);
    set_payload(payload);
    std::cout << obj.serialize() << std::endl;
    return obj;
}

web::json::value &Response::failure(ErrorCode code) {
	auto error = message_map.find(code);
	if(error == message_map.end()) {
		error = message_map.find(ErrorCode::UnknownError);
	}

    return failure((int)error->first, error->second);
}

web::json::value &Response::failure(int code, std::string message) {
	set_success(false);
    set_error(code, message);
    std::cout << obj.serialize() << std::endl;
    return obj;
}
