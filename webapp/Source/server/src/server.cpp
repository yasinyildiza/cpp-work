#include "../include/server.h"

SimpleServer::SimpleServer(std::string url) : m_listener(url) {
    m_listener.support(web::http::methods::GET, std::bind(&SimpleServer::handle_get, this, std::placeholders::_1));
    m_listener.support(web::http::methods::POST, std::bind(&SimpleServer::handle_post, this, std::placeholders::_1));
    m_listener.support(web::http::methods::PUT, std::bind(&SimpleServer::handle_put, this, std::placeholders::_1));
    m_listener.support(web::http::methods::DEL, std::bind(&SimpleServer::handle_delete, this, std::placeholders::_1));
}

pplx::task<void> SimpleServer::open() {
    return m_listener.open();
}

pplx::task<void> SimpleServer::close() {
    return m_listener.close();
}

bool SimpleServer::authenticate(web::http::http_request request, parameterlist params) {
    auto username = params.find(KEY_USERNAME);
    if(username == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingUsername));
        return false;
    }

    auto password = params.find(KEY_PASSWORD);
    if(password == params.end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::ParameterMissingPassword));
        return false;
    }

    if(!Trader::authenticate(username->second, password->second)) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::AuthenticationFailed));
        return false;
    }

    return true;
}

void SimpleServer::handle_request(web::http::http_request request, std::string method_name) {
    std::cout << method_name << "::" << request.relative_uri().to_string() << std::endl;

    auto params = web::http::uri::split_query(web::http::uri::decode(request.relative_uri().query()));
    auto paths = web::http::uri::split_path(web::http::uri::decode(request.relative_uri().path()));
    if(paths.empty()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::PathMissing));
    }
    auto path = paths.at(0);

    auto handler_method = Handler::path_map[method_name].find(path);
    if(handler_method == Handler::path_map[method_name].end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::PathNotFound));
    } else {
        if(authenticate(request, params)) {
            handler_method->second(request, params);
        }
    }
}

void SimpleServer::handle_get(web::http::http_request request) {
    handle_request(request, METHOD_GET);
};

void SimpleServer::handle_post(web::http::http_request request) {
    std::cout << "post" << "::" << request.relative_uri().to_string() << std::endl;

    auto params = web::http::uri::split_query(web::http::uri::decode(request.relative_uri().query()));
    auto paths = web::http::uri::split_path(web::http::uri::decode(request.relative_uri().path()));
    if(paths.empty()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::PathMissing));
    }
    auto path = paths.at(0);

    auto handler_method = Handler::path_map[METHOD_POST].find(path);
    if(handler_method == Handler::path_map[METHOD_POST].end()) {
        request.reply(web::http::status_codes::OK, Response().failure(ErrorCode::PathNotFound));
    } else {
        if(path == URL_REGISTER || authenticate(request, params)) {
            handler_method->second(request, params);
        }
    }
};

void SimpleServer::handle_put(web::http::http_request request) {
    handle_request(request, METHOD_PUT);
};

void SimpleServer::handle_delete(web::http::http_request request) {
    handle_request(request, METHOD_DEL);
};
