/*
 * Gmalloc.h
 *
 *  Created on: 2017��8��10��
 *      Author: user
 */

#ifndef GMALLOC_H_
#define GMALLOC_H_
void *Gmalloc(unsigned long Msiz);
void Gfree(void *addr);
void GmallocInit(void *stack, unsigned long stack_siz);
unsigned long GetMallocSiz(void);
#endif /* GMALLOC_H_ */
