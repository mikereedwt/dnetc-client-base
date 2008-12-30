/*
 * Copyright 2008 Vyacheslav Chupyatov <goteam@mail.ru>
 * For use in distributed.net projects only.
 * Any other distribution or use of this source violates copyright.
 *
 * Special thanks for help in testing this core to:
 * Alexander Kamashev
 * PanAm
 * Alexei Chupyatov
 *
 * $Id: r72stream-vc4c_il.cpp,v 1.1 2008/12/30 16:26:45 andreasb Exp $
*/

static const char il4c_src[]=

"il_ps_2_0\n"
"dcl_input_position_interp(linear_noperspective) vWinCoord0.xy__\n"
"dcl_output_generic o0			;#CMC,CMC_hi,CMC_CMC_mid,CMC_lo\n"
"dcl_cb cb0[3]				;key_hi,key_mid,key_lo,key_inc\n"
"					;plain_lo,plain_hi,cypher_lo,cypher_hi\n"
"					;iters,rest,width\n"
"dcl_literal	l0,	0xBF0A8B1D,0x1f,32,0\n"
"dcl_literal l1, 0x5618cb1c, 0x5618cb1c, 0x5618cb1c, 0x5618cb1c\n"
"dcl_literal l2, 0xf45044d5, 0xf45044d5, 0xf45044d5, 0xf45044d5\n"
"dcl_literal l3, 0x9287be8e, 0x9287be8e, 0x9287be8e, 0x9287be8e\n"
"dcl_literal l4, 0x30bf3847, 0x30bf3847, 0x30bf3847, 0x30bf3847\n"
"dcl_literal l5, 0xcef6b200, 0xcef6b200, 0xcef6b200, 0xcef6b200\n"
"dcl_literal l6, 0x6d2e2bb9, 0x6d2e2bb9, 0x6d2e2bb9, 0x6d2e2bb9\n"
"dcl_literal l7, 0x0b65a572, 0x0b65a572, 0x0b65a572, 0x0b65a572\n"
"dcl_literal l8, 0xa99d1f2b, 0xa99d1f2b, 0xa99d1f2b, 0xa99d1f2b\n"
"dcl_literal l9, 0x47d498e4, 0x47d498e4, 0x47d498e4, 0x47d498e4\n"
"dcl_literal l10, 0xe60c129d, 0xe60c129d, 0xe60c129d, 0xe60c129d\n"
"dcl_literal l11, 0x84438c56, 0x84438c56, 0x84438c56, 0x84438c56\n"
"dcl_literal l12, 0x227b060f, 0x227b060f, 0x227b060f, 0x227b060f\n"
"dcl_literal l13, 0xc0b27fc8, 0xc0b27fc8, 0xc0b27fc8, 0xc0b27fc8\n"
"dcl_literal l14, 0x5ee9f981, 0x5ee9f981, 0x5ee9f981, 0x5ee9f981\n"
"dcl_literal l15, 0xfd21733a, 0xfd21733a, 0xfd21733a, 0xfd21733a\n"
"dcl_literal l16, 0x9b58ecf3, 0x9b58ecf3, 0x9b58ecf3, 0x9b58ecf3\n"
"dcl_literal l17, 0x399066ac, 0x399066ac, 0x399066ac, 0x399066ac\n"
"dcl_literal l18, 0xd7c7e065, 0xd7c7e065, 0xd7c7e065, 0xd7c7e065\n"
"dcl_literal l19, 0x75ff5a1e, 0x75ff5a1e, 0x75ff5a1e, 0x75ff5a1e\n"
"dcl_literal l20, 0x1436d3d7, 0x1436d3d7, 0x1436d3d7, 0x1436d3d7\n"
"dcl_literal l21, 0xb26e4d90, 0xb26e4d90, 0xb26e4d90, 0xb26e4d90\n"
"dcl_literal l22, 0x50a5c749, 0x50a5c749, 0x50a5c749, 0x50a5c749\n"
"dcl_literal l23, 0xeedd4102, 0xeedd4102, 0xeedd4102, 0xeedd4102\n"
"dcl_literal l24, 0x8d14babb, 0x8d14babb, 0x8d14babb, 0x8d14babb\n"
"dcl_literal l25, 0x2b4c3474, 0x2b4c3474, 0x2b4c3474, 0x2b4c3474\n"
"dcl_literal l26, 0x0,0x1,0x2,0x3\n"
"dcl_literal l27, 0xff,0x00ff0000,0x0000ff00,3\n"
"dcl_literal l28, 8,24,2,29\n"
"dcl_literal l29, 8.0,8.0,8.0,0x80000000\n"
"	;r100.x=key_hi,r100.y=key_mid,r100.z=key_lo\n"
"	mov	r100.x,cb0[0].x\n"
"	mov	r100.y,cb0[0].y\n"
"	mov	r100.z,cb0[0].z\n"
"	mov	r100.w,cb0[2].x			;iters\n"
"	;r101	CMC_COUNT,CMC hi:mid:lo\n"
"	mov	r101,l26.xxxx\n"
"	;Add thread index to key_hi\n"
"	flr	r50.x,vWinCoord0.x\n"
"	flr	r50.y,vWinCoord0.y\n"
"	mad	r50.x,r50.y,cb0[2].z,r50.x\n"
"	ftou	r50.x,r50.x\n"
"	ishl	r50.z,r50.x,l28.z\n"
"	iadd	r100.x,r50.z,r100.x				;hi+objIndex*4\n"
"	ilt	r50.y,r50.x,cb0[2].y				;idx<rest?\n"
"	cmov_logical r50.x,r50.y,l26.x,l26.y\n"
"	iadd	r100.w,r100.w,r50.x_neg(x)\n"
"	\n"
"	whileloop\n"
"		break_logicalz	r100.w\n"
"		;unpack mid \n"
"		ishl	r50.x,r100.y,l28.y			;t=(mid<<24)|(mid>>24);\n"
"		ushr	r50.y,r100.y,l28.y\n"
"		iand	r50.z,r100.y,l27.y			;t=t|((mid&(unsigned)0x00ff0000)>>8);\n"
"		iand	r50.w,r100.y,l27.z			;t=t|((mid&(unsigned)0x0000ff00)<<8);\n"
"		ushr	r50.z,r50.z,l28.x\n"
"		ishl	r50.w,r50.w,l28.x\n"
"		ior	r50.x,r50.x,r50.y\n"
"		ior	r50.w,r50.z,r50.w\n"
"		ior	r50.x,r50.x,r50.w			;bswap mid\n"
"		mov	r50.y,r50.x				;t3=t\n"
"	\n"
"		ushr	r51.x,r100.x,l28.x			;(hi>>8)\n"
"		iadd	r50.x,r50.x,r51.x			;t+=(hi>>8)\n"
"		ult	r51.y,r50.x,r50.y			;if(t<t3)\n"
"		if_logicalnz	r51.y\n"
"			;unpack lo\n"
"			ishl	r52.x,r100.z,l28.y		;t=(lo<<24)|(lo>>24);\n"
"			ushr	r52.y,r100.z,l28.y\n"
"			iand	r52.z,r100.z,l27.y		;t=t|((lo&(unsigned)0x00ff0000)>>8);\n"
"			iand	r52.w,r100.z,l27.z		;t=t|((lo&(unsigned)0x0000ff00)<<8);\n"
"			\n"
"			ushr	r52.z,r52.z,l28.x\n"
"			ishl	r52.w,r52.w,l28.x\n"
"			ior		r52.x,r52.x,r52.y\n"
"			ior		r52.w,r52.z,r52.w\n"
"			ior		r52.x,r52.x,r52.w		;bswap lo\n"
"			iadd	r52.x,r52.x,l26.y		;t2=t2+1\n"
"			;pack lo\n"
"			ishl	r53.x,r52.x,l28.y		;t2=(lo<<24)|(lo>>24);\n"
"			ushr	r53.y,r52.x,l28.y\n"
"			iand	r53.z,r52.x,l27.y		;t2=t2|((lo&0x00ff0000)>>8);\n"
"			iand	r53.w,r52.x,l27.z		;t2=t2|((lo&0x0000ff00)<<8);\n"
"			ushr	r53.z,r53.z,l28.x\n"
"			ishl	r53.w,r53.w,l28.x\n"
"			ior	r53.x,r53.x,r53.y\n"
"			ior	r53.z,r53.z,r53.w\n"
"			ior	r100.z,r53.x,r53.z		;bswap lo		\n"
"		endif\n"
"		;pack mid\n"
"		ishl	r50.y,r50.x,l28.y\n"
"		ushr	r50.z,r50.x,l28.y\n"
"		iand	r51.x,r50.x,l27.y\n"
"		iand	r51.y,r50.x,l27.z\n"
"		ushr	r50.w,r51.x,l28.x\n"
"		ishl	r50.x,r51.y,l28.x\n"
"		ior	r50.y,r50.z,r50.y\n"
"		ior	r50.w,r50.x,r50.w\n"
"		ior	r100.y,r50.y,r50.w			;bswap mid\n"
"		iand	r100.x,r100.x,l27.x\n"
"		;L2 = key_hi;\n"
"		;L1 = key_mid;\n"
"		;L0 = key_lo;\n"
"		mov	r0,r100.zzzz\n"
"		mov	r1,r100.yyyy\n"
"		mov	r2,r100.xxxx\n"
"	\n"
"		iadd	r2,r2,l26\n"
"		;round 1\n"
"		;S0=r10,S1=r11,...,S25=r35\n"
"	\n"
"		;L0=ROTL(L0+S0,S0)=ROTL(L0+S0,0x1d)\n"
"		iadd	r50,r0,l0.xxxx\n"
"		ushr	r51,r50,l27.w\n"
"		ishl	r52,r50,l28.w\n"
"		ior	r0,r51,r52\n"
"	\n"
"		;S1=ROTL3(Sc1+S0+L0)\n"
"		iadd	r56,l0.xxxx,l1.xxxx	\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r11,r56,r57\n"
"		;L1=ROTL(L1+S1+L0,S1+L0)\n"
"		iadd	r55,r11,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S2=ROTL3(Sc2+S1+L1)\n"
"		iadd	r56,r11,l2.xxxx\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r12,r56,r57\n"
"	\n"
"		;L2=ROTL(L2+S2+L1,S2+L1)\n"
"		iadd	r55,r12,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy	\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"	\n"
"		;S3=ROTL3(Sc3+S2+L2)\n"
"		iadd	r56,r12,l3.xxxx\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r13,r56,r57\n"
"		;L0=ROTL(L0+S3+L2,S3+L2)\n"
"		iadd	r55,r13,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior		r0,r55,r59\n"
"		;S4=ROTL3(Sc4+S3+L0)\n"
"		iadd	r56,r13,l4.xxxx\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r14,r56,r57\n"
"		;L1=ROTL(L1+S4+L0,S4+L0)\n"
"		iadd	r55,r14,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy	\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior		r1,r55,r59\n"
"		;S5=ROTL3(Sc5+S4+L1)\n"
"		iadd	r56,r14,l5.xxxx\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r15,r56,r57\n"
"		;L2=ROTL(L2+S5+L1,S5+L1);\n"
"		iadd	r55,r15,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy	\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"	\n"
"		;S6=ROTL3(Sc6+S5+L2)\n"
"		iadd	r56,r15,l6.xxxx\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r16,r56,r57\n"
"		;L0=ROTL(L0+S6+L2,S6+L2)\n"
"		iadd	r55,r16,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S7=ROTL3(Sc7+S6+L0)\n"
"		iadd	r56,r16,l7.xxxx\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r17,r56,r57\n"
"	\n"
"		;L1=ROTL(L1+S7+L0,S7+L0)\n"
"		iadd	r55,r17,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S8=ROTL3(Sc8+S7+L1)\n"
"		iadd	r56,r17,l8.xxxx\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r18,r56,r57\n"
"		;L2=ROTL(L2+S8+L1,S8+L1)\n"
"		iadd	r55,r18,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S9=ROTL3(Sc9+S8+L2)\n"
"		iadd	r56,r18,l9.xxxx\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r19,r56,r57\n"
"		;L0=ROTL(L0+S9+L2,S9+L2)\n"
"		iadd	r55,r19,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S10=ROTL3(Sc10+S9+L0)\n"
"		iadd	r56,r19,l10.xxxx\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r20,r56,r57\n"
"		;L1=ROTL(L1+S10+L0,S10+L0)\n"
"		iadd	r55,r20,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S11=ROTL3(Sc11+S10+L1)\n"
"		iadd	r56,r20,l11.xxxx\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r21,r56,r57\n"
"		;L2=ROTL(L2+S11+L1,S11+L1)\n"
"		iadd	r55,r21,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S12=ROTL3(Sc12+S11+L2)\n"
"		iadd	r56,r21,l12.xxxx\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r22,r56,r57\n"
"		;L0=ROTL(L0+S12+L2,S12+L2);\n"
"		iadd	r55,r22,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S13=ROTL3(Sc13+S12+L0)\n"
"		iadd	r56,r22,l13.xxxx\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r23,r56,r57\n"
"		;L1=ROTL(L1+S13+L0,S13+L0)\n"
"		iadd	r55,r23,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S14=ROTL3(Sc14+S13+L1)\n"
"		iadd	r56,r23,l14.xxxx\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r24,r56,r57\n"
"		;L2=ROTL(L2+S14+L1,S14+L1)\n"
"		iadd	r55,r24,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S15=ROTL3(Sc15+S14+L2)\n"
"		iadd	r56,r24,l15.xxxx\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r25,r56,r57\n"
"		;L0=ROTL(L0+S15+L2,S15+L2)\n"
"		iadd	r55,r25,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S16=ROTL3(Sc16+S15+L0)\n"
"		iadd	r56,r25,l16.xxxx\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r26,r56,r57\n"
"		;L1=ROTL(L1+S16+L0,S16+L0)\n"
"		iadd	r55,r26,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S17=ROTL3(Sc17+S16+L1)\n"
"		iadd	r56,r26,l17.xxxx\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r27,r56,r57\n"
"		;L2=ROTL(L2+S17+L1,S17+L1)\n"
"		iadd	r55,r27,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S18=ROTL3(Sc18+S17+L2)\n"
"		iadd	r56,r27,l18.xxxx\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r28,r56,r57\n"
"		;L0=ROTL(L0+S18+L2,S18+L2)\n"
"		iadd	r55,r28,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S19=ROTL3(Sc19+S18+L0)\n"
"		iadd	r56,r28,l19.xxxx\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r29,r56,r57\n"
"		;L1=ROTL(L1+S19+L0,S19+L0)\n"
"		iadd	r55,r29,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S20=ROTL3(Sc20+S19+L1)\n"
"		iadd	r56,r29,l20.xxxx\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r30,r56,r57\n"
"		;L2=ROTL(L2+S20+L1,S20+L1)\n"
"		iadd	r55,r30,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S21=ROTL3(Sc21+S20+L2)\n"
"		iadd	r56,r30,l21.xxxx\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r31,r56,r57\n"
"		;L0=ROTL(L0+S21+L2,S21+L2)\n"
"		iadd	r55,r31,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S22=ROTL3(Sc22+S21+L0)\n"
"		iadd	r56,r31,l22.xxxx\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r32,r56,r57\n"
"	\n"
"		;L1=ROTL(L1+S22+L0,S22+L0)\n"
"		iadd	r55,r32,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S23=ROTL3(Sc23+S22+L1)\n"
"		iadd	r56,r32,l23.xxxx\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r33,r56,r57\n"
"		;L2=ROTL(L2+S23+L1,S23+L1)\n"
"		iadd	r55,r33,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S24=ROTL3(Sc24+S23+L2)\n"
"		iadd	r56,r33,l24.xxxx\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r34,r56,r57\n"
"		;L0=ROTL(L0+S24+L2,S24+L2)\n"
"		iadd	r55,r34,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S25=ROTL3(Sc25+S24+L0)\n"
"		iadd	r56,r34,l25.xxxx\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r35,r56,r57\n"
"		;L1=ROTL(L1+S25+L0,S25+L0)\n"
"		iadd	r55,r35,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;//����� 2\n"
"		;S0=ROTL3(S0+S25+L1)\n"
"		iadd	r56,r35,l0.xxxx\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r10,r56,r57\n"
"		;L2=ROTL(L2+S0+L1,S0+L1)\n"
"		iadd	r55,r10,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S1=ROTL3(S1+S0+L2)\n"
"		iadd	r56,r10,r11\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r11,r56,r57\n"
"		;L0=ROTL(L0+S1+L2,S1+L2)\n"
"		iadd	r55,r11,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S2=ROTL3(S2+S1+L0)\n"
"		iadd	r56,r11,r12\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r12,r56,r57\n"
"		;L1=ROTL(L1+S2+L0,S2+L0)\n"
"		iadd	r55,r12,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S3=ROTL3(S3+S2+L1)\n"
"		iadd	r56,r12,r13\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r13,r56,r57\n"
"		;L2=ROTL(L2+S3+L1,S3+L1)\n"
"		iadd	r55,r13,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S4=ROTL3(S4+S3+L2)\n"
"		iadd	r56,r13,r14\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r14,r56,r57\n"
"		;L0=ROTL(L0+S4+L2,S4+L2)\n"
"		iadd	r55,r14,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S5=ROTL3(S5+S4+L0)\n"
"		iadd	r56,r14,r15\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r15,r56,r57\n"
"		;L1=ROTL(L1+S5+L0,S5+L0)\n"
"		iadd	r55,r15,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S6=ROTL3(S6+S5+L1)\n"
"		iadd	r56,r15,r16\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r16,r56,r57\n"
"		;L2=ROTL(L2+S6+L1,S6+L1)\n"
"		iadd	r55,r16,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S7=ROTL3(S7+S6+L2)\n"
"		iadd	r56,r16,r17\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r17,r56,r57\n"
"		;L0=ROTL(L0+S7+L2,S7+L2)\n"
"		iadd	r55,r17,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S8=ROTL3(S8+S7+L0)\n"
"		iadd	r56,r17,r18\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r18,r56,r57\n"
"		;L1=ROTL(L1+S8+L0,S8+L0)\n"
"		iadd	r55,r18,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S9=ROTL3(S9+S8+L1)\n"
"		iadd	r56,r18,r19\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r19,r56,r57\n"
"		;L2=ROTL(L2+S9+L1,S9+L1)\n"
"		iadd	r55,r19,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S10=ROTL3(S10+S9+L2)\n"
"		iadd	r56,r19,r20\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r20,r56,r57\n"
"		;L0=ROTL(L0+S10+L2,S10+L2)\n"
"		iadd	r55,r20,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S11=ROTL3(S11+S10+L0)\n"
"		iadd	r56,r20,r21\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r21,r56,r57\n"
"		;L1=ROTL(L1+S11+L0,S11+L0)\n"
"		iadd	r55,r21,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S12=ROTL3(S12+S11+L1)\n"
"		iadd	r56,r21,r22\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r22,r56,r57\n"
"		;L2=ROTL(L2+S12+L1,S12+L1)\n"
"		iadd	r55,r22,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S13=ROTL3(S13+S12+L2)\n"
"		iadd	r56,r22,r23\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r23,r56,r57\n"
"		;L0=ROTL(L0+S13+L2,S13+L2)\n"
"		iadd	r55,r23,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S14=ROTL3(S14+S13+L0)\n"
"		iadd	r56,r23,r24\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r24,r56,r57\n"
"		;L1=ROTL(L1+S14+L0,S14+L0)\n"
"		iadd	r55,r24,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S15=ROTL3(S15+S14+L1)\n"
"		iadd	r56,r24,r25\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r25,r56,r57\n"
"		;L2=ROTL(L2+S15+L1,S15+L1)\n"
"		iadd	r55,r25,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S16=ROTL3(S16+S15+L2)\n"
"		iadd	r56,r25,r26\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r26,r56,r57\n"
"		;L0=ROTL(L0+S16+L2,S16+L2)\n"
"		iadd	r55,r26,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S17=ROTL3(S17+S16+L0)\n"
"		iadd	r56,r26,r27\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r27,r56,r57\n"
"		;L1=ROTL(L1+S17+L0,S17+L0)\n"
"		iadd	r55,r27,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S18=ROTL3(S18+S17+L1)\n"
"		iadd	r56,r27,r28\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r28,r56,r57\n"
"		;L2=ROTL(L2+S18+L1,S18+L1)\n"
"		iadd	r55,r28,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S19=ROTL3(S19+S18+L2)\n"
"		iadd	r56,r28,r29\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r29,r56,r57\n"
"		;L0=ROTL(L0+S19+L2,S19+L2)\n"
"		iadd	r55,r29,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S20=ROTL3(S20+S19+L0)\n"
"		iadd	r56,r29,r30\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r30,r56,r57\n"
"		;L1=ROTL(L1+S20+L0,S20+L0)\n"
"		iadd	r55,r30,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S21=ROTL3(S21+S20+L1)\n"
"		iadd	r56,r30,r31\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r31,r56,r57\n"
"		;L2=ROTL(L2+S21+L1,S21+L1)\n"
"		iadd	r55,r31,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S22=ROTL3(S22+S21+L2)\n"
"		iadd	r56,r31,r32\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r32,r56,r57\n"
"		;L0=ROTL(L0+S22+L2,S22+L2)\n"
"		iadd	r55,r32,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S23=ROTL3(S23+S22+L0)\n"
"		iadd	r56,r32,r33\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r33,r56,r57\n"
"		;L1=ROTL(L1+S23+L0,S23+L0)\n"
"		iadd	r55,r33,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S24=ROTL3(S24+S23+L1)\n"
"		iadd	r56,r33,r34\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r34,r56,r57\n"
"		;L2=ROTL(L2+S24+L1,S24+L1)\n"
"		iadd	r55,r34,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S25=ROTL3(S25+S24+L2)\n"
"		iadd	r56,r34,r35\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r35,r56,r57\n"
"		;L0=ROTL(L0+S25+L2,S25+L2)\n"
"		iadd	r55,r35,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;//����� 3\n"
"		;S0=ROTL3(S0+S25+L0)\n"
"		iadd	r56,r35,r10\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r10,r56,r57\n"
"		;L1=ROTL(L1+S0+L0,S0+L0)\n"
"		iadd	r55,r10,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S1=ROTL3(S1+S0+L1)\n"
"		iadd	r56,r10,r11\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r11,r56,r57\n"
"		;L2=ROTL(L2+S1+L1,S1+L1)\n"
"		iadd	r55,r11,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S2=ROTL3(S2+S1+L2)\n"
"		iadd	r56,r11,r12\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r12,r56,r57\n"
"		;L0=ROTL(L0+S2+L2,S2+L2)\n"
"		iadd	r55,r12,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S3=ROTL3(S3+S2+L0)\n"
"		iadd	r56,r12,r13\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r13,r56,r57\n"
"		;L1=ROTL(L1+S3+L0,S3+L0)\n"
"		iadd	r55,r13,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S4=ROTL3(S4+S3+L1)\n"
"		iadd	r56,r13,r14\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r14,r56,r57\n"
"		;L2=ROTL(L2+S4+L1,S4+L1)\n"
"		iadd	r55,r14,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S5=ROTL3(S5+S4+L2)\n"
"		iadd	r56,r14,r15\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r15,r56,r57\n"
"		;L0=ROTL(L0+S5+L2,S5+L2)\n"
"		iadd	r55,r15,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S6=ROTL3(S6+S5+L0)\n"
"		iadd	r56,r15,r16\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r16,r56,r57\n"
"		;L1=ROTL(L1+S6+L0,S6+L0)\n"
"		iadd	r55,r16,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S7=ROTL3(S7+S6+L1)\n"
"		iadd	r56,r16,r17\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r17,r56,r57\n"
"       	\n"
"		;L2=ROTL(L2+S7+L1,S7+L1)\n"
"		iadd	r55,r17,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S8=ROTL3(S8+S7+L2)\n"
"		iadd	r56,r17,r18\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r18,r56,r57\n"
"		;L0=ROTL(L0+S8+L2,S8+L2)\n"
"		iadd	r55,r18,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S9=ROTL3(S9+S8+L0)\n"
"		iadd	r56,r18,r19\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r19,r56,r57\n"
"		;L1=ROTL(L1+S9+L0,S9+L0)\n"
"		iadd	r55,r19,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S10=ROTL3(S10+S9+L1)\n"
"		iadd	r56,r19,r20\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r20,r56,r57\n"
"		;L2=ROTL(L2+S10+L1,S10+L1)\n"
"		iadd	r55,r20,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S11=ROTL3(S11+S10+L2)\n"
"		iadd	r56,r20,r21\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r21,r56,r57\n"
"		;L0=ROTL(L0+S11+L2,S11+L2)\n"
"		iadd	r55,r21,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S12=ROTL3(S12+S11+L0)\n"
"		iadd	r56,r21,r22\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r22,r56,r57\n"
"		;L1=ROTL(L1+S12+L0,S12+L0)\n"
"		iadd	r55,r22,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S13=ROTL3(S13+S12+L1)\n"
"		iadd	r56,r22,r23\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r23,r56,r57\n"
"		;L2=ROTL(L2+S13+L1,S13+L1)\n"
"		iadd	r55,r23,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S14=ROTL3(S14+S13+L2)\n"
"		iadd	r56,r23,r24\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r24,r56,r57\n"
"		;L0=ROTL(L0+S14+L2,S14+L2)\n"
"		iadd	r55,r24,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S15=ROTL3(S15+S14+L0)\n"
"		iadd	r56,r24,r25\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r25,r56,r57\n"
"		;L1=ROTL(L1+S15+L0,S15+L0)\n"
"		iadd	r55,r25,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"	\n"
"		;S16=ROTL3(S16+S15+L1)\n"
"		iadd	r56,r25,r26\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r26,r56,r57\n"
"		;L2=ROTL(L2+S16+L1,S16+L1)\n"
"		iadd	r55,r26,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S17=ROTL3(S17+S16+L2)\n"
"		iadd	r56,r26,r27\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r27,r56,r57\n"
"		;L0=ROTL(L0+S17+L2,S17+L2)\n"
"		iadd	r55,r27,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S18=ROTL3(S18+S17+L0)\n"
"		iadd	r56,r27,r28\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r28,r56,r57\n"
"		;L1=ROTL(L1+S18+L0,S18+L0)\n"
"		iadd	r55,r28,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S19=ROTL3(S19+S18+L1)\n"
"		iadd	r56,r28,r29\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r29,r56,r57\n"
"		;L2=ROTL(L2+S19+L1,S19+L1)\n"
"		iadd	r55,r29,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S20=ROTL3(S20+S19+L2)\n"
"		iadd	r56,r29,r30\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r30,r56,r57\n"
"		;L0=ROTL(L0+S20+L2,S20+L2)\n"
"		iadd	r55,r30,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S21=ROTL3(S21+S20+L0)\n"
"		iadd	r56,r30,r31\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r31,r56,r57\n"
"		;L1=ROTL(L1+S21+L0,S21+L0)\n"
"		iadd	r55,r31,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S22=ROTL3(S22+S21+L1)\n"
"		iadd	r56,r31,r32\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r32,r56,r57\n"
"		;L2=ROTL(L2+S22+L1,S22+L1)\n"
"		iadd	r55,r32,r1\n"
"		iadd	r56,r55,r2\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r2,r55,r59\n"
"		;S23=ROTL3(S23+S22+L2)\n"
"		iadd	r56,r32,r33\n"
"		iadd	r55,r56,r2\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r33,r56,r57\n"
"		;L0=ROTL(L0+S23+L2,S23+L2)\n"
"		iadd	r55,r33,r2\n"
"		iadd	r56,r55,r0\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r0,r55,r59\n"
"		;S24=ROTL3(S24+S23+L0)\n"
"		iadd	r56,r33,r34\n"
"		iadd	r55,r56,r0\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r34,r56,r57\n"
"		;//Encryption round\n"
"		;//setup\n"
"	\n"
"		;eA=PLAIN_LO+S0\n"
"		iadd	r10,r10,cb0[1].xxxx		;eA\n"
"		;eB=PLAIN_HI+S1;\n"
"		iadd	r11,r11,cb0[1].yyyy		;eB\n"
"		;eA=ROTL(eA^eB,eB)+S2\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r12\n"
"		;eB=ROTL(eB^eA,eA)+S3\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r13\n"
"		;eA=ROTL(eA^eB,eB)+S4\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r14\n"
"		;eB=ROTL(eB^eA,eA)+S5\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r15\n"
"		;eA=ROTL(eA^eB,eB)+S6\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r16\n"
"		;eB=ROTL(eB^eA,eA)+S7\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r17\n"
"		;eA=ROTL(eA^eB,eB)+S8\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r18\n"
"		;eB=ROTL(eB^eA,eA)+S9;\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r19\n"
"		;eA=ROTL(eA^eB,eB)+S10\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r20\n"
"		;eB=ROTL(eB^eA,eA)+S11\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r21\n"
"		;eA=ROTL(eA^eB,eB)+S12\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r22\n"
"		;eB=ROTL(eB^eA,eA)+S13\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r23\n"
"		;eA=ROTL(eA^eB,eB)+S14\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r24\n"
"		;eB=ROTL(eB^eA,eA)+S15\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r25\n"
"		;eA=ROTL(eA^eB,eB)+S16;\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r26\n"
"	\n"
"		;eB=ROTL(eB^eA,eA)+S17\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r27\n"
"		;eA=ROTL(eA^eB,eB)+S18\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r28\n"
"		;eB=ROTL(eB^eA,eA)+S19\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r29\n"
"		;eA=ROTL(eA^eB,eB)+S20\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r30\n"
"		;eB=ROTL(eB^eA,eA)+S21\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r31\n"
"		;eA=ROTL(eA^eB,eB)+S22\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r32\n"
"		;eB=ROTL(eB^eA,eA)+S23\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r33\n"
"		;eA=ROTL(eA^eB,eB)+S24\n"
"		ixor	r10,r10,r11\n"
"		iand	r58,r11,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r10,r58\n"
"		ushr	r59,r10,r59\n"
"		ior	r10,r55,r59\n"
"		iadd	r10,r10,r34\n"
"		;o0: # CMC, hi,mid,lo\n"
"		ieq	r12,r10,cb0[1].zzzz\n"
"		ior	r12.x,r12.x,r12.y\n"
"		ior	r12.z,r12.z,r12.w\n"
"		ior	r12.x,r12.x,r12.z\n"
"		mov	r50.x,r100.x\n"
"		iadd	r100.x,r100.x,cb0[0].w\n"
"		iadd	r100.w,r100.w,l26.y_neg(y)\n"
"		\n"
"		continue_logicalz r12.x\n"
"		;L1=ROTL(L1+S24+L0,S24+L0)\n"
"		iadd	r55,r34,r0\n"
"		iadd	r56,r55,r1\n"
"		iand	r58,r55,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r56,r58\n"
"		ushr	r59,r56,r59\n"
"		ior	r1,r55,r59\n"
"		;S25=ROTL3(S25+S24+L1)\n"
"		iadd	r56,r34,r35\n"
"		iadd	r55,r56,r1\n"
"		ishl	r56,r55,l27.w\n"
"		ushr	r57,r55,l28.w\n"
"		ior	r35,r56,r57\n"
"		;eB=ROTL(eB^eA,eA)+S25\n"
"		ixor	r11,r11,r10\n"
"		iand	r58,r10,l0.yyyy\n"
"		iadd	r59,l0.zzzz,r58_neg(xyzw)\n"
"		ishl	r55,r11,r58\n"
"		ushr	r59,r11,r59\n"
"		ior	r11,r55,r59\n"
"		iadd	r11,r11,r35\n"
"		ieq	r55.x,r10.x,cb0[1].z\n"
"		if_logicalnz	r55.x		;key #0\n"
"			;CMC increment\n"
"			iadd	r101.x,r101.x,l26.y\n"
"			mov	r101.y,r50.x\n"
"			mov	r101.z,r100.y\n"
"			mov	r101.w,r100.z\n"
"			ieq	r59.x,r11.x,cb0[1].w\n"
"			if_logicalnz r59.x\n"
"				;solution found\n"
"				ior	r101.x,r101.x,l29.w\n"
"				break\n"
"			endif\n"
"		endif\n"
"		ieq	r55.x,r10.y,cb0[1].z\n"
"		if_logicalnz	r55.x		;key #1\n"
"			;CMC increment\n"
"			iadd	r101.x,r101.x,l26.y\n"
"			iadd	r101.y,r50.x,l26.y\n"
"			mov	r101.z,r100.y\n"
"			mov	r101.w,r100.z\n"
"			ieq	r59.x,r11.y,cb0[1].w\n"
"			if_logicalnz r59.x\n"
"				;solution found\n"
"				ior	r101.x,r101.x,l29.w\n"
"				break\n"
"			endif\n"
"		endif\n"
"		ieq	r55.x,r10.z,cb0[1].z\n"
"		if_logicalnz	r55.x		;key #2\n"
"			;CMC increment\n"
"			iadd	r101.x,r101.x,l26.y\n"
"			iadd	r101.y,r50.x,l26.z\n"
"			mov	r101.z,r100.y\n"
"			mov	r101.w,r100.z\n"
"			ieq	r59.x,r11.z,cb0[1].w\n"
"			if_logicalnz r59.x\n"
"				;solution found\n"
"				ior	r101.x,r101.x,l29.w\n"
"				break\n"
"			endif\n"
"		endif\n"
"		ieq	r55.x,r10.w,cb0[1].z\n"
"		if_logicalnz	r55.x		;key #3\n"
"			;CMC increment\n"
"			iadd	r101.x,r101.x,l26.y\n"
"			iadd	r101.y,r50.x,l26.w\n"
"			mov	r101.z,r100.y\n"
"			mov	r101.w,r100.z\n"
"			ieq	r59.x,r11.w,cb0[1].w\n"
"			if_logicalnz r59.x\n"
"				;solution found\n"
"				ior	r101.x,r101.x,l29.w\n"
"				break\n"
"			endif\n"
"		endif\n"
"	endloop\n"
"mov	o0,r101\n"
"end\n";
