1) Installation

	The project has been developed under Ubuntu, and only Makefiles for g++ compiler are provided within the solution.

	So, all dependencies are listed below can be installed by the Package Manager (apt, yum, etc.).

	Within the same directory of this file, there is a shell script (setup.sh --requiring sudo privileges), which includes installation commands (for Ubuntu) for all the dependent packages.

	1) So, open a console.
	2) change directory (cd) to project root.
	3) ./setup.sh

	Other than these packages, the C++ REST API must be built and installed from source.

	First, clone the repository from git.

	git clone https://git.codeplex.com/casablanca

	cd casablanca/Release
	mkdir build.release
	cd build.release
	CXX=g++-4.8 cmake .. -DCMAKE_BUILD_TYPE=Release
	make

	For more information:

	https://casablanca.codeplex.com/wikipage?title=Setup%20and%20Build%20on%20Linux&referringTitle=Documentation

2) Database initialization

	The database used in the project is MySQL.

	Required packages will be installed by the setup shell script once you run it.

	After installing MySQL Server, please be sure that the server is running and you created a database.

	To complete the database installation, please run the "schema.sql" MySQL script under "server/sql".

	mysql -u <username> -p < schema.sql

	Also, to insert test data to the database, please use the "seed.sql" MySQL script.

	Anytime, you want to run tests, run "truncate.sql" and "seed.sql" consequtively.

3) Preparing Source Code (Build & Compile)

	There are two main modules inside the project package: "server" and "client".

	"server" module is the REST API, and "client" module is the web application.

	There is a Makefile under each module's root directory to compile the module and create the executable.

	Just cd into the module directory and run the command: "make"

	This will generate the binary file of the module.

4) Assumptions & Missing Requirements

	In the REST API, several services may be added such as:
		updating trader's password
		querying trader's balancecash (implemented)
		querying trader's single portfolio (implemented)
		quoting all stocks at once

	Although not indicated explicitly, the following constraints must be handled by the application:
		username of a Trader must be unique
		stockcode of a Stock must be unique
		username - stockcode pair of Portfolio must be unique

	Cascading delete on a record delete is not mandatory because no delete operation is defined within the application.

	quantity and price fields in Buy and Sell requests are validated within handler.

	Logout functionality is added to User Interface.

	A simple Login service added to REST API.

5) Issues & Feedback
	
	The size of the project is fairly good to measure one's C++ knowledge and programming ability, but it didn't seem possible to me to complete it in 3 days (not even in 5 days).

	So, I think, the initial duration of the project can be extended (if the limited duration is not a part of the measurement process).

	Another issue is that it is sometimes hard to support more than 1 platform (i.e.; support Linux and Windows at the same time), especially when third party libraries (like cpprest, mysqlcppcpon) are included in the project.

6) Running Applications

	To run the REST API (server):
		cd server
		make
		./server <db_ip> <db_port> <db_username> <db_password>

	To run the Web Application (client):
		cd client
		make
		./run

7) Running Unit Tests
	
	Due to time constraint, I could not complete the unit tests of the Client module, so unit tests provided are only for the Server module.

	There are two types of unit tests written for the Server module:

	A) Boost Unit Test Framework
		These unit tests contain regular test cases, providing several input combinations to functions and classes within the module.
		These unit tests do not cover the module completely because many parts of the module depends on data restored in the database.
		Running and connecting to a database within the framework is not easy.
		So, Boost UTF tests cover only the parts which do not touch the database.

		To run:
			cd server/tests
			make
			./runtest

	B) Test Client
		This module provides a simple client application, which sends requests yielding urls for each of the test cases.
		The logic behind this test module relies on the url as well as the database state.
		In combination with MySQL scripts, Test Client covers all the cases, all the combinations within the Server.

		To run:
			cd server/sql
			mysql -u root -p < schema.sql
			mysql -u root -p < seed.sql
			
			cd server/
			make
			./server //to run the server actually

			cd server/tests/client
			make
			./client

		The name of the test cases and test progress will be printed to the console.
