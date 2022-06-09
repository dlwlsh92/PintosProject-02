#ifndef INSTRINSIC_H
#include "threads/mmu.h"

/* Store the physical address of the page directory into CR3
   aka PDBR (page directory base register).  This activates our
   new page tables immediately.  See [IA32-v2a] "MOV--Move
   to/from Control Registers" and [IA32-v3a] 3.7.5 "Base Address
   of the Page Directory". */
/*
 * 페이지 디렉토리의 실제 주소를 PDBR(페이지 디렉토리 기본 레지스터)라고 하는 CR3에 저장합니다.
 * 그러면 새 페이지 테이블이 즉시 활성화됩니다.
 * [IA32-v2a] "MOV--컨트롤 레지스터로/에서 이동" 및 [IA32-v3a] 3.7.5 "페이지 디렉토리의 기본 주소"를 참조하십시오. */

__attribute__((always_inline))
static __inline void lcr3(uint64_t val) {
	__asm __volatile("movq %0, %%cr3" : : "r" (val));
}

__attribute__((always_inline))
static __inline void lgdt(const struct desc_ptr *dtr) {
	__asm __volatile("lgdt %0" : : "m" (*dtr));
}

__attribute__((always_inline))
static __inline void lldt(uint16_t sel) {
	__asm __volatile("lldt %0" : : "r" (sel));
}

__attribute__((always_inline))
static __inline void ltr(uint16_t sel) {
	__asm __volatile("ltr %0" : : "r" (sel));
}

__attribute__((always_inline))
static __inline void lidt(const struct desc_ptr *dtr) {
	__asm __volatile("lidt %0" : : "m" (*dtr));
}

__attribute__((always_inline))
static __inline void invlpg(uint64_t addr) {
	__asm __volatile("invlpg (%0)" : : "r" (addr) : "memory");
}

__attribute__((always_inline))
static __inline uint64_t read_eflags(void) {
	uint64_t rflags;
	__asm __volatile("pushfq; popq %0" : "=r" (rflags));
	return rflags;
}

__attribute__((always_inline))
static __inline uint64_t rcr3(void) {
	uint64_t val;
	__asm __volatile("movq %%cr3,%0" : "=r" (val));
	return val;
}

__attribute__((always_inline))
static __inline uint64_t rrax(void) {
	uint64_t val;
	__asm __volatile("movq %%rax,%0" : "=r" (val));
	return val;
}

__attribute__((always_inline))
static __inline uint64_t rrdi(void) {
	uint64_t val;
	__asm __volatile("movq %%rdi,%0" : "=r" (val));
	return val;
}

__attribute__((always_inline))
static __inline uint64_t rrsi(void) {
	uint64_t val;
	__asm __volatile("movq %%rsi,%0" : "=r" (val));
	return val;
}

__attribute__((always_inline))
static __inline uint64_t rrdx(void) {
	uint64_t val;
	__asm __volatile("movq %%rdx,%0" : "=r" (val));
	return val;
}

__attribute__((always_inline))
static __inline uint64_t rr10(void) {
	uint64_t val;
	__asm __volatile("movq %%r10,%0" : "=r" (val));
	return val;
}

__attribute__((always_inline))
static __inline uint64_t rr8(void) {
	uint64_t val;
	__asm __volatile("movq %%r8,%0" : "=r" (val));
	return val;
}

__attribute__((always_inline))
static __inline uint64_t rr9(void) {
	uint64_t val;
	__asm __volatile("movq %%r9,%0" : "=r" (val));
	return val;
}

__attribute__((always_inline))
static __inline uint64_t rrcx(void) {
	uint64_t val;
	__asm __volatile("movq %%rcx,%0" : "=r" (val));
	return val;
}

__attribute__((always_inline))
static __inline uint64_t rrsp(void) {
	uint64_t val;
	__asm __volatile("movq %%rsp,%0" : "=r" (val));
	return val;
}
__attribute__((always_inline))
static __inline uint64_t rcr2(void) {
	uint64_t val;
	__asm __volatile("movq %%cr2,%0" : "=r" (val));
	return val;
}
/* MSR (Model-Specific Register)
 * 디버깅, 프로그램 실행 추적, 컴퓨터 성능 모니터링 및 특정 CPU 기능 전환에 사용되는 
 * x86 명령 집합의 다양한 제어 레지스터 중 하나 */
__attribute__((always_inline))
static __inline void write_msr(uint32_t ecx, uint64_t val) {
	uint32_t edx, eax;
	eax = (uint32_t) val;
	edx = (uint32_t) (val >> 32);
	__asm __volatile("wrmsr" // 
			:: "c" (ecx), "d" (edx), "a" (eax) );
}

#endif /* intrinsic.h */

