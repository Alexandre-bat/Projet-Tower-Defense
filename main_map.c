#include "all.h"

int main(){
	int** map;
	int* ps;
	int size;
	ps=&size;
	map=generatePath(ps);
	showPath(map,size);
	return 0;
}
