USE StockExchange;

INSERT INTO trader(username, password, balancecash) VALUES('testuser', 'testpass', 100000);

INSERT INTO stock(stockcode, lastsaleprice) VALUES('TEST1', 10);
INSERT INTO stock(stockcode, lastsaleprice) VALUES('TEST2', 37);
INSERT INTO stock(stockcode, lastsaleprice) VALUES('TEST3', 55);

INSERT INTO portfolio(username, stockcode, quantity, totalcost) VALUES('testuser', 'TEST1', 12, 13);
INSERT INTO portfolio(username, stockcode, quantity, totalcost) VALUES('testuser', 'TEST2', 14, 15);

#INSERT INTO transaction(username, stockcode, quantity, datetime, action, status) VALUES('testuser', 'TEST1', 4, 5, 6, 7);
#INSERT INTO transaction(username, stockcode, quantity, datetime, action, status) VALUES('testuser', 'TEST1', 8, 9, 10, 11);
