#include <stdio.h>
#include "store.h"

int main(int argc, char* argv[]){
	struct store item;
	FILE *fp;
	if(argc != 2){
		fprintf(stderr, "How to use : %s FileName\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "wb");
	printf("%-3s %-5s %-9s %-13s %-6s\n", "id", "name", "category", "date", "stock");
	while(scanf("%d %s %s %d %d", &item.id, item.name, item.category, &item.date, &item.stock)==5){
		fwrite(&item, sizeof(item), 1, fp);
	}
	fclose(fp);
	return 0;
}
