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

	printf("(n) : sell one goods ] ");
	scanf("%d",&num);
	
	fp = fopen(argv[1],"rb+");
		fseek(fp, num*sizeof(item), SEEK_SET);
			if(item.stock == 0){
				printf("\'%s\' has been sold out... (There is no stock)\n", item.name);
			}else if(item.stock > 0){
				item.stock--;
				printf("\'%s\'(1) has been sold...\n",item.name);
			}




	printf("%3s %15s %9s %13s %5s\n","id","name","category", "expired date", "stock");
		
	fseek(fp, 0L, SEEK_SET);
	while(fread(&item,sizeof(item),1,fp)>0){
		printf("%3d %15s %9s %13d %5d\n", item.id, item.name, item.category, item.date, item.stock);
	}


	fclose(fp);
	return 0;
}


