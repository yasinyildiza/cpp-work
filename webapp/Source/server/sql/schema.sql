DROP DATABASE IF EXISTS StockExchange;
CREATE DATABASE IF NOT EXISTS StockExchange;

USE StockExchange;

CREATE TABLE IF NOT EXISTS transaction (
    username varchar(255) NOT NULL,
    stockcode varchar(255) NOT NULL,
    quantity integer NOT NULL,
    datetime integer NOT NULL,
    action integer NOT NULL,
    status integer NOT NULL
);

CREATE TABLE IF NOT EXISTS trader (
    username varchar(255) NOT NULL PRIMARY KEY,
    password varchar(255) NOT NULL,
    balancecash integer NOT NULL
);

CREATE TABLE IF NOT EXISTS portfolio (
    username varchar(255) NOT NULL,
    stockcode varchar(255) NOT NULL,
    quantity integer NOT NULL,
    totalcost integer NOT NULL
);
ALTER TABLE portfolio ADD UNIQUE unique_index (username, stockcode);

CREATE TABLE IF NOT EXISTS stock (
    stockcode varchar(255) NOT NULL PRIMARY KEY,
    lastsaleprice integer NOT NULL
);
