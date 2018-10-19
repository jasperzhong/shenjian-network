CC=g++

mysql_demo: mysql_demo.cpp
	$(CC) -static -o $@ $< -I /usr/include/mysql -L. -lmysqlclient -lpthread -ldl
clean:
	rm mysql_demo	
