/* MIPS i8500 memcpy helper macros.
   Copyright (c) 2025  MIPS. All rights reserved.

   This copyrighted material is made available to anyone wishing to use,
   modify, copy, or redistribute it subject to the terms and conditions
   of the FreeBSD License.   This program is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY expressed or implied,
   including the implied warranties of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  A copy of this license is available at
   http://www.opensource.org/licenses.
*/

#define ALIGN_AT_64_BYTES_MASK 0x3F
#define ALIGN_AT_16_BYTES_MASK 0x0F

#define ALIGNED_COPY_LOOP(dstp, srcp, endp)	\
	while (endp - dstp > 8) { \
    long t0, t1, t2, t3, t4, t5, t6, t7;  \
		asm volatile ("ld\t%0,0(%1)":"=r"(t0):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,8(%1)":"=r"(t1):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,16(%1)":"=r"(t2):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,24(%1)":"=r"(t3):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,32(%1)":"=r"(t4):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,40(%1)":"=r"(t5):"r"(srcp):"memory");	\
		asm volatile ("sd\t%0,0(%1)"::"r"(t0),"r"(dstp):"memory");	\
		asm volatile ("sd\t%0,8(%1)"::"r"(t1),"r"(dstp):"memory");	\
		asm volatile ("ld\t%0,48(%1)":"=r"(t6):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,56(%1)":"=r"(t7):"r"(srcp):"memory");	\
		srcp += 8;	\
		asm volatile ("sd\t%0,16(%1)"::"r"(t2),"r"(dstp):"memory");	\
		asm volatile ("sd\t%0,24(%1)"::"r"(t3),"r"(dstp):"memory");	\
		asm volatile ("sd\t%0,32(%1)"::"r"(t4),"r"(dstp):"memory");	\
		asm volatile ("sd\t%0,40(%1)"::"r"(t5),"r"(dstp):"memory");	\
		asm volatile ("sd\t%0,48(%1)"::"r"(t6),"r"(dstp):"memory");	\
		asm volatile ("sd\t%0,56(%1)"::"r"(t7),"r"(dstp):"memory");	\
		dstp += 8;	\
	}

#define ALIGNED_COPY_LOOP_WITH_PREF(dstp, srcp, endp)	\
	while (endp - dstp > 8) { \
    long t0, t1, t2, t3, t4, t5, t6, t7;  \
		asm volatile ("ld\t%0,0(%1)":"=r"(t0):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,8(%1)":"=r"(t1):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,16(%1)":"=r"(t2):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,24(%1)":"=r"(t3):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,32(%1)":"=r"(t4):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,40(%1)":"=r"(t5):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,48(%1)":"=r"(t6):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,56(%1)":"=r"(t7):"r"(srcp):"memory");	\
		srcp += 8;	\
		asm volatile ("mips.sdp\t%0,%1,0(%2)"::"r"(t0),"r"(t1),"r"(dstp):"memory");	\
		asm volatile ("mips.sdp\t%0,%1,16(%2)"::"r"(t2),"r"(t3),"r"(dstp):"memory");	\
		asm volatile ("mips.sdp\t%0,%1,32(%2)"::"r"(t4),"r"(t5),"r"(dstp):"memory");	\
		asm volatile ("mips.sdp\t%0,%1,48(%2)"::"r"(t6),"r"(t7),"r"(dstp):"memory");	\
		dstp += 8;	\
		asm volatile ("prefetch.r\t384(%0)"::"r"(srcp));	\
	}

#define ALIGNED_COPY_LOOP_WITH_PREF_AND_CBO(dstp, srcp, endp)	\
	while (endp - dstp > 8) { \
    long t0, t1, t2, t3, t4, t5, t6, t7;  \
		asm volatile ("ld\t%0,0(%1)":"=r"(t0):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,8(%1)":"=r"(t1):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,16(%1)":"=r"(t2):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,24(%1)":"=r"(t3):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,32(%1)":"=r"(t4):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,40(%1)":"=r"(t5):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,48(%1)":"=r"(t6):"r"(srcp):"memory");	\
		asm volatile ("ld\t%0,56(%1)":"=r"(t7):"r"(srcp):"memory");	\
		srcp += 8;	\
		asm ("cbo.zero\t(%0)"::"r"(dstp));	\
		asm volatile ("mips.sdp\t%0,%1,0(%2)"::"r"(t0),"r"(t1),"r"(dstp):"memory");	\
		asm volatile ("mips.sdp\t%0,%1,16(%2)"::"r"(t2),"r"(t3),"r"(dstp):"memory");	\
		asm volatile ("mips.sdp\t%0,%1,32(%2)"::"r"(t4),"r"(t5),"r"(dstp):"memory");	\
		asm volatile ("mips.sdp\t%0,%1,48(%2)"::"r"(t6),"r"(t7),"r"(dstp):"memory");	\
		dstp += 8;	\
		asm volatile ("prefetch.r\t384(%0)"::"r"(srcp));	\
	}

#define UNALIGNED_COPY_LOOP(dstp, srcp, endp, LD_OFF1, LD_OFF2, LD_OFF3, LD_OFF4, LD_OFF5, LD_OFF6,OFFSET)	\
	while (endp - dstp > 8) { \
    long t0, t1, t2, t3, t4, t5;  \
		asm volatile ("ld\t%0,%c[offset_plus](%1)":"=r"(t0):"r"(srcp),[offset_plus] "i" (LD_OFF1):"memory");	\
		asm volatile ("ld\t%0,%c[offset_plus](%1)":"=r"(t1):"r"(srcp),[offset_plus] "i" (LD_OFF2):"memory");	\
		asm volatile ("ld\t%0,%c[offset_plus](%1)":"=r"(t2):"r"(srcp),[offset_plus] "i" (LD_OFF3):"memory");	\
		asm volatile ("ld\t%0,%c[offset_plus](%1)":"=r"(t3):"r"(srcp),[offset_plus] "i" (LD_OFF4):"memory");	\
		asm volatile ("sd\t%0,%c[offset_plus](%1)"::"r"(t0),"r"(dstp),[offset_plus] "i" (LD_OFF1):"memory");	\
		asm volatile ("sd\t%0,%c[offset_plus](%1)"::"r"(t1),"r"(dstp),[offset_plus] "i" (LD_OFF2):"memory");	\
		asm volatile ("ld\t%0,%c[offset_plus](%1)":"=r"(t4):"r"(srcp),[offset_plus] "i" (LD_OFF5):"memory");	\
		asm volatile ("ld\t%0,%c[offset_plus](%1)":"=r"(t5):"r"(srcp),[offset_plus] "i" (LD_OFF6):"memory");	\
		\
		asm volatile ("sd\t%0,%c[offset_plus](%1)"::"r"(t2),"r"(dstp),[offset_plus] "i" (LD_OFF3):"memory");	\
		asm volatile ("sd\t%0,%c[offset_plus](%1)"::"r"(t3),"r"(dstp),[offset_plus] "i" (LD_OFF4):"memory");	\
		asm volatile ("sd\t%0,%c[offset_plus](%1)"::"r"(t4),"r"(dstp),[offset_plus] "i" (LD_OFF5):"memory");	\
		asm volatile ("sd\t%0,%c[offset_plus](%1)"::"r"(t5),"r"(dstp),[offset_plus] "i" (LD_OFF6):"memory");	\
		\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t0):"r"(srcp),[offset_plus] "i" (OFFSET + 0):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t1):"r"(srcp),[offset_plus] "i" (OFFSET + 1):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t2):"r"(srcp),[offset_plus] "i" (OFFSET + 8):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t3):"r"(srcp),[offset_plus] "i" (OFFSET + 9):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t0),"r"(dstp),[offset_plus] "i" (OFFSET + 0):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t1),"r"(dstp),[offset_plus] "i" (OFFSET + 1):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t2),"r"(dstp),[offset_plus] "i" (OFFSET + 8):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t3),"r"(dstp),[offset_plus] "i" (OFFSET + 9):"memory");	\
		\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t0):"r"(srcp),[offset_plus] "i" (OFFSET + 2):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t1):"r"(srcp),[offset_plus] "i" (OFFSET + 3):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t2):"r"(srcp),[offset_plus] "i" (OFFSET + 10):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t3):"r"(srcp),[offset_plus] "i" (OFFSET + 11):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t0),"r"(dstp),[offset_plus] "i" (OFFSET + 2):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t1),"r"(dstp),[offset_plus] "i" (OFFSET + 3):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t2),"r"(dstp),[offset_plus] "i" (OFFSET + 10):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t3),"r"(dstp),[offset_plus] "i" (OFFSET + 11):"memory");	\
		\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t0):"r"(srcp),[offset_plus] "i" (OFFSET + 4):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t1):"r"(srcp),[offset_plus] "i" (OFFSET + 5):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t2):"r"(srcp),[offset_plus] "i" (OFFSET + 12):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t3):"r"(srcp),[offset_plus] "i" (OFFSET + 13):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t0),"r"(dstp),[offset_plus] "i" (OFFSET + 4):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t1),"r"(dstp),[offset_plus] "i" (OFFSET + 5):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t2),"r"(dstp),[offset_plus] "i" (OFFSET + 12):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t3),"r"(dstp),[offset_plus] "i" (OFFSET + 13):"memory");	\
		\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t0):"r"(srcp),[offset_plus] "i" (OFFSET + 6):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t1):"r"(srcp),[offset_plus] "i" (OFFSET + 7):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t2):"r"(srcp),[offset_plus] "i" (OFFSET + 14):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t3):"r"(srcp),[offset_plus] "i" (OFFSET + 15):"memory");	\
		srcp += 8;	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t0),"r"(dstp),[offset_plus] "i" (OFFSET + 6):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t1),"r"(dstp),[offset_plus] "i" (OFFSET + 7):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t2),"r"(dstp),[offset_plus] "i" (OFFSET + 14):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t3),"r"(dstp),[offset_plus] "i" (OFFSET + 15):"memory");	\
		dstp += 8;	\
	}

#define UNALIGNED_COPY_LOOP_WITH_PREF(dstp, srcp, endp, LD_OFF1, LD_OFF2, LD_OFF3, OFFSET)	\
	while (endp - dstp > 8) { \
    long t0, t1, t2, t3, t4, t5;  \
		asm volatile ("mips.ldp\t%0,%1,%c[offset_plus](%2)":"=r"(t0),"=r"(t1):"r"(srcp),[offset_plus] "i" (LD_OFF1):"memory");	\
		asm volatile ("mips.ldp\t%0,%1,%c[offset_plus](%2)":"=r"(t2),"=r"(t3):"r"(srcp),[offset_plus] "i" (LD_OFF2):"memory");	\
		asm volatile ("mips.ldp\t%0,%1,%c[offset_plus](%2)":"=r"(t4),"=r"(t5):"r"(srcp),[offset_plus] "i" (LD_OFF3):"memory");	\
		asm volatile ("mips.sdp\t%0,%1,%c[offset_plus](%2)"::"r"(t0),"r"(t1),"r"(dstp),[offset_plus] "i" (LD_OFF1):"memory");	\
		asm volatile ("mips.sdp\t%0,%1,%c[offset_plus](%2)"::"r"(t2),"r"(t3),"r"(dstp),[offset_plus] "i" (LD_OFF2):"memory");	\
		asm volatile ("mips.sdp\t%0,%1,%c[offset_plus](%2)"::"r"(t4),"r"(t5),"r"(dstp),[offset_plus] "i" (LD_OFF3):"memory");	\
		\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t0):"r"(srcp),[offset_plus] "i" (OFFSET + 0):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t1):"r"(srcp),[offset_plus] "i" (OFFSET + 1):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t2):"r"(srcp),[offset_plus] "i" (OFFSET + 8):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t3):"r"(srcp),[offset_plus] "i" (OFFSET + 9):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t0),"r"(dstp),[offset_plus] "i" (OFFSET + 0):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t1),"r"(dstp),[offset_plus] "i" (OFFSET + 1):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t2),"r"(dstp),[offset_plus] "i" (OFFSET + 8):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t3),"r"(dstp),[offset_plus] "i" (OFFSET + 9):"memory");	\
		\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t0):"r"(srcp),[offset_plus] "i" (OFFSET + 2):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t1):"r"(srcp),[offset_plus] "i" (OFFSET + 3):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t2):"r"(srcp),[offset_plus] "i" (OFFSET + 10):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t3):"r"(srcp),[offset_plus] "i" (OFFSET + 11):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t0),"r"(dstp),[offset_plus] "i" (OFFSET + 2):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t1),"r"(dstp),[offset_plus] "i" (OFFSET + 3):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t2),"r"(dstp),[offset_plus] "i" (OFFSET + 10):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t3),"r"(dstp),[offset_plus] "i" (OFFSET + 11):"memory");	\
		\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t0):"r"(srcp),[offset_plus] "i" (OFFSET + 4):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t1):"r"(srcp),[offset_plus] "i" (OFFSET + 5):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t2):"r"(srcp),[offset_plus] "i" (OFFSET + 12):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t3):"r"(srcp),[offset_plus] "i" (OFFSET + 13):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t0),"r"(dstp),[offset_plus] "i" (OFFSET + 4):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t1),"r"(dstp),[offset_plus] "i" (OFFSET + 5):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t2),"r"(dstp),[offset_plus] "i" (OFFSET + 12):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t3),"r"(dstp),[offset_plus] "i" (OFFSET + 13):"memory");	\
		\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t0):"r"(srcp),[offset_plus] "i" (OFFSET + 6):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t1):"r"(srcp),[offset_plus] "i" (OFFSET + 7):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t2):"r"(srcp),[offset_plus] "i" (OFFSET + 14):"memory");	\
		asm volatile ("lbu\t%0,%c[offset_plus](%1)":"=r"(t3):"r"(srcp),[offset_plus] "i" (OFFSET + 15):"memory");	\
		srcp += 8;	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t0),"r"(dstp),[offset_plus] "i" (OFFSET + 6):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t1),"r"(dstp),[offset_plus] "i" (OFFSET + 7):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t2),"r"(dstp),[offset_plus] "i" (OFFSET + 14):"memory");	\
		asm volatile ("sb\t%0,%c[offset_plus](%1)"::"r"(t3),"r"(dstp),[offset_plus] "i" (OFFSET + 15):"memory");	\
		dstp += 8;	\
		asm volatile ("prefetch.r\t384(%0)"::"r"(srcp));	\
	}
