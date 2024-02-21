all:
	gcc -o server main.c broadcast_udp.c handle_tcp_connection.c
	gcc -o client client.c
clean:
	rm client server