/*
 ============================================================================
 Name        : Malloc.c
 Author      : f
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Gmalloc.h"
unsigned char stack[500];

int main(void) {

	char *MBuff;
	char *MBuff1;
	char *MBuff2;
	char *MBuff3;
	char *MBuff4;
	char *MBuff5;
	char *MBuff6;
	char *MBuff7;
	char *MBuff8;
	GmallocInit(stack, sizeof(stack));
	MBuff1 = Gmalloc(1);
	if (MBuff1 == NULL) {
		printf("审请空间失败");
	}
	printf("Addr:%p,Siz:%ld", MBuff1, GetMallocSiz());
	memcpy(MBuff1, "1", 1);
	printf("数据：%s\r\n", stack + sizeof(stack) - 1);
	LsGMalloc();

	MBuff2 = Gmalloc(2);
	if (MBuff2 == NULL) {
		printf("审请空间失败");
	}
	printf("Addr:%p,Siz:%ld", MBuff2, GetMallocSiz());
	memcpy(MBuff2, "12", 2);
	printf("数据：%s\r\n", stack + sizeof(stack) - 1 - 1 - 2);
	LsGMalloc();
	MBuff3 = Gmalloc(3);
	LsGMalloc();
	MBuff4 = Gmalloc(4);
	LsGMalloc();
	//printf("删除了一个\r\n");
	// Gfree(MBuff1);
	LsGMalloc();
	MBuff5 = Gmalloc(50);
	printf("Addr:%p,Siz:%ld", MBuff5, GetMallocSiz());
	LsGMalloc();
	MBuff6 = Gmalloc(6);
	LsGMalloc();
	MBuff7 = Gmalloc(2);
	MBuff3 = Gmalloc(20);
	LsGMalloc();
	printf("删除了一个\r\n");
	Gfree(MBuff5);
	printf("删除了一个\r\n");
	Gfree(MBuff7);
	MBuff8 = Gmalloc(1);
	MBuff8 = Gmalloc(20);
	LsGMalloc();
	printf("Addr:%p,Siz:%ld", MBuff3, GetMallocSiz());
	MBuff8 = Gmalloc(340);
	if (MBuff8 != NULL)
		LsGMalloc();
	else {
		printf("Malloc :ERROR");
	}
	/* MBuff=Malloc(10) ;
	 LstMalloc();
	 MBuff1=Malloc(5) ;
	 LstMalloc();
	 MBuff2=Malloc(10) ;
	 LstMalloc();

	 MBuff3=Malloc(10) ;
	 LstMalloc();

	 MBuff4=Malloc(10) ;
	 LstMalloc();
	 */
	/*
	 //LstMalloc();
	 //printf("STACK:%s\r\n",stack);

	 //	MBuff1=Malloc(10) ;
	 // memcpy(MBuff1,"hello1\0",strlen("hello1\0"));
	 /*printf("ADDR:%p  ",MBuff1);
	 printf("STack:%p  ",stack);
	 printf("StackSiz:%ld",*(unsigned long*)(stack+MemStackAuto.siz-sizeof(unsigned long)));
	 printf("MBUFF:%s\r\n",MBuff1);
	 */
	//LstMalloc();
	//printf("STACK:%s\r\n",stack);
	//LstMalloc();
	//MBuff2=Malloc(10) ;
	//memcpy(MBuff2,"hello2\0",strlen("hello3\0"));
	/*printf("ADDR:%p  ",MBuff);
	 printf("STack:%p  ",stack);
	 printf("StackSiz:%ld",*(unsigned long*)(stack+MemStackAuto.siz-sizeof(unsigned long)));
	 printf("MBUFF:%s\r\n",MBuff);
	 //printf("STACK:%s\r\n",stack);
	 */
	//LstMalloc();
//	Free(MBuff1);
	//MBuff3=Malloc(10) ;
	//memcpy(MBuff3,"hello3\0",strlen("hello4\0"));
	/*printf("ADDR:%p  ",MBuff);
	 printf("STack:%p  \r\n",stack);
	 printf("StackSiz:%ld",*(unsigned long*)(stack+MemStackAuto.siz-sizeof(unsigned long)));
	 printf("MBUFF:%s\r\n",MBuff);
	 //printf("STACK:%s\r\n",stack);
	 */
	//LstMalloc();
	// printf("StackSiz:%ld",*(unsigned long*)(stack+MemStackAuto.siz-sizeof(unsigned long)));
	//printf("UN: \r\n");
	//Free(MBuff1);
	//LstMalloc();
	// printf("StackSiz:%ld",*(unsigned long*)(stack+MemStackAuto.siz-sizeof(unsigned long)));
	//LstMalloc();
	puts("Hello World\r\n"); /* prints Hello World */
	return EXIT_SUCCESS;
}
