/*
 * Gmalloc.c
 *
 *  Created on: 2017年8月10日
 *      Author: user
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Gmalloc.h"
typedef struct MemStack {
	void *dat;
	unsigned long siz;
} MemStack_t, *PMemStack;
unsigned char *MemAutoStack;
typedef struct Mem {
	unsigned long addr;
	unsigned long siz;
} MemAuto_t, *PMemAuto;
MemStack_t MemStackAuto;
void SmallLargeSort(PMemAuto pmem, int n, char direction) {
	int low = 0;
	int high = n - 1; //设置变量的初始值
	int j;
	MemAuto_t Mtmp;
	switch (direction) {
	case 0x01:
		while (low < high) {
			for (j = low; j < high; ++j) //正向冒泡,找到最大者
				if (pmem[j].addr < pmem[j + 1].addr) {
					Mtmp = pmem[j];
					pmem[j] = pmem[j + 1];
					pmem[j + 1] = Mtmp;
				}
			--high;                 //修改high值, 前移一位
			for (j = high; j > low; --j) //反向冒泡,找到最小者
				if (pmem[j].addr > pmem[j - 1].addr) {
					Mtmp = pmem[j];
					pmem[j] = pmem[j - 1];
					pmem[j - 1] = Mtmp;
				}
			++low;                  //修改low值,后移一位
		}
		break;
	default:
		while (low < high) {
			for (j = low; j < high; ++j) //正向冒泡,找到最大者
				if (pmem[j].addr > pmem[j + 1].addr) {
					Mtmp = pmem[j];
					pmem[j] = pmem[j + 1];
					pmem[j + 1] = Mtmp;
				}
			--high;                 //修改high值, 前移一位
			for (j = high; j > low; --j) //反向冒泡,找到最小者
				if (pmem[j].addr < pmem[j - 1].addr) {
					Mtmp = pmem[j];
					pmem[j] = pmem[j - 1];
					pmem[j - 1] = Mtmp;
				}
			++low;                  //修改low值,后移一位
		}
		break;
	}

}
PMemAuto FindNullAddLinkedList() {
	MemAuto_t ListNull;
	unsigned long siz = *(unsigned long*) MemStackAuto.dat;
	PMemAuto Nlist = (MemAuto_t*) ( MemStackAuto.dat + sizeof(unsigned long));
	memset(&ListNull, 0, sizeof(MemAuto_t));
	if (siz > 0) {
		for (unsigned long i = 0;
				memcmp(Nlist, &ListNull, sizeof(MemAuto_t)) != 0 && (i < siz);
				i++) {

			Nlist++;
		}
	}
	return Nlist;
}
void Gfree(void *addr) {
	unsigned long siz = *(unsigned long*) MemStackAuto.dat;
	PMemAuto Nlist = (MemAuto_t*) ( MemStackAuto.dat + sizeof(unsigned long));
	for (unsigned long i = 0; i < siz; i++) {
		if ((MemStackAuto.dat + Nlist->addr) == addr) {
			memcpy(Nlist, Nlist + 1, sizeof(MemAuto_t) * (siz - i));
			memset(Nlist + siz, 0, sizeof(MemAuto_t));
			(*(unsigned long*)  MemStackAuto.dat)--;
			SmallLargeSort(Nlist, (*(unsigned long*)  MemStackAuto.dat), 1);
			return ;
		}
		Nlist++;
	}
	return;
}
unsigned long GetMallocSiz() {
	unsigned long Msiz = 0;
	unsigned long siz = *(unsigned long*)  MemStackAuto.dat;
	PMemAuto Nlist = (MemAuto_t*) ( MemStackAuto.dat + sizeof(unsigned long));
	SmallLargeSort(Nlist, (*(unsigned long*)  MemStackAuto.dat), 1);
	if(Nlist->siz!=0)
	{
	for (unsigned long i = 0; i <= siz; i++) {
		if ((((Nlist)->addr) - ((Nlist + 1)->siz) - (Nlist + 1)->addr) > Msiz) {
			Msiz = (((Nlist)->addr) - ((Nlist + 1)->siz) - (Nlist + 1)->addr);
		}
		Nlist++;
	}
	return Msiz - (siz + 1) * sizeof(MemAuto_t);
	}
	return MemStackAuto.siz-(siz + 1) * sizeof(MemAuto_t);
}
void *Gmalloc(unsigned long Msiz) {
	unsigned long siz = *(unsigned long*)  MemStackAuto.dat;
	PMemAuto Nlist = (MemAuto_t*) ( MemStackAuto.dat + sizeof(unsigned long));
	PMemAuto memauto;
	PMemAuto SmalList = NULL;
	unsigned long SmallSiz = 0;
	void *Ret;
	unsigned long StackSiz = 0;
	StackSiz = GetMallocSiz();
	if (StackSiz >= Msiz) {
		memauto = FindNullAddLinkedList();
		if (((Nlist)->siz) > 0) {
        	for (unsigned long i = 0; i <= siz; i++) {
                if ((((Nlist)->addr) - ((Nlist + 1)->siz) - (Nlist + 1)->addr)>= Msiz) {
				if (SmallSiz != 0) {
						if (SmallSiz
								> (((Nlist)->addr) - ((Nlist + 1)->siz)
										- (Nlist + 1)->addr)) {
							SmalList = Nlist;
							SmallSiz = (((Nlist)->addr) - ((Nlist + 1)->siz)
									- (Nlist + 1)->addr);
						}
					} else {
						SmalList = Nlist;
						SmallSiz = (((Nlist)->addr) - ((Nlist + 1)->siz)
								- (Nlist + 1)->addr);
					}
				}

				Nlist++;

			}
			if (SmalList != NULL) {
				memauto->siz = Msiz;
				memauto->addr = (SmalList)->addr - Msiz;
				(*(unsigned long*)  MemStackAuto.dat)++;
				Ret = MemStackAuto.dat + memauto->addr;
				return Ret;
			} else {
				return NULL;
			}

		} else {
			memauto->siz = Msiz;
			memauto->addr = (MemStackAuto.siz - Msiz);
			(*(unsigned long*)  MemStackAuto.dat)++;
			return MemStackAuto.dat + memauto->addr;
		}
	}
	return NULL;
}
void GmallocInit(void *stack, unsigned long stack_siz) {
	PMemAuto Mconfig;
	MemStackAuto.dat = stack;
	MemStackAuto.siz = stack_siz;
	memset(MemStackAuto.dat, 0, stack_siz);
	Mconfig = (MemAuto_t*) (MemStackAuto.dat + MemStackAuto.siz- sizeof(MemAuto_t) - sizeof(unsigned long));
	Mconfig->addr = 0;
	Mconfig->siz = 0;
}

void LsGMalloc() {
	unsigned long siz = *(unsigned long*) MemStackAuto.dat;
	PMemAuto Nlist = (MemAuto_t*) ( MemStackAuto.dat + sizeof(unsigned long));
	for (unsigned long i = 0; i < siz; i++) {
		printf("Stack:%ld,%ld\r\n", Nlist->addr, Nlist->siz);
		Nlist++;
	}

}
void *Grealloc(void *addr,unsigned long Msiz)
{
	unsigned long siz = *(unsigned long*)  MemStackAuto.dat;
	PMemAuto Nlist = (MemAuto_t*) ( MemStackAuto.dat + sizeof(unsigned long));
	unsigned long i = 0;
	char *mem=NULL;
	SmallLargeSort(Nlist, (*(unsigned long*)  MemStackAuto.dat), 1);
	for (i=0; i < siz&&(MemStackAuto.dat + Nlist->addr) != addr; i++) {
			Nlist++;
	}

	if(i<siz)
	{
		if ((((Nlist)->addr) - ((Nlist + 1)->siz) - (Nlist + 1)->addr)>= Msiz) {
            Nlist->siz=Msiz;
		}
		else
		{
			mem=Gmalloc(Msiz);
			memcpy(mem,addr,Nlist->siz);
			return mem;
		}


	}
	return addr;
}
