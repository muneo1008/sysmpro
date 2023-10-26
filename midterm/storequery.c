#include <stdio.h>
#include "store.h"

int main(int argc, char*argv[]){
	struct store item;
	int num;
	FILE *fp;
	
	if(argc != 2){
		fprintf(stderr, "How to use : %s file\n",argv[0]);
		return 1;
	}

	printf("0: list of all goods, 1: list of available goods ) ");
	scanf("%d",&num);
	
	fp = fopen(argv[1],"rb");

	if (num == 0){
		printf("%3s %15s %9s %13s %5s\n","id","name","category", "expired date", "stock");
		while(fread(&item,sizeof(item),1,fp)>0){
			if(item.id != 0){
				printf("%3d %15s %9s %13d %5d\n", item.id, item.name, item.category, item.date, item.stock);
			}
		}
	}else if (num == 1){
		printf("%3s %15s %9s %13s %5s\n", "id", "name", "category", "expired date", "stock");
		while(fread(&item, sizeof(item), 1, fp) > 0){
			if(item.date > 2022 && item.stock != 0){
				printf("%3d %15s %9s %13d %5d\n",item.id, item.name, item.category, item.date, item.stock);
			}
		}
	}


	fclose(fp);
	return 0;
}


