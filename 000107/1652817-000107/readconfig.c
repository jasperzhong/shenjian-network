#include <stdio.h>

int read_conf(){
	FILE *fp = fopen("/etc/1652817.conf", "r");
	int n;
	fscanf(fp, "%*[^0-9]%d", &n);
	return n;
}
