/* =========================================================================*
 * RK6748_DSP.cmd - Linker Command File for Linking tms320c6748 DSP Programs	*
 * 																			*
 * These linker options are for command line linking only. For IDE linking, *
 * you should set your linker options in Project Properties.				*
 * 		-c					Link Using C Conventions						*
 *		-stack 	0x1000		Software Stack Size								*
 *		-heap	0x1000		Heap Area Size									*
 * =========================================================================*/

 MEMORY
{
#ifdef DSP_CORE
/****************************************************************************/
/*                                                                          */
/*              DSP 专有内存区域                                            */
/*                                                                          */
/****************************************************************************/
    DSPL2ROM     o = 0x00700000  l = 0x00100000  /* 1MB   L2 DSP 本地 ROM (DSP ROM Bootloader) */
    DSPL2RAM     o = 0x00800000  l = 0x00040000  /* 256kB L2 DSP 本地 RAM */
    DSPL1PRAM    o = 0x00E00000  l = 0x00008000  /* 32kB  L1 DSP 本地程序 RAM */
    DSPL1DRAM    o = 0x00F00000  l = 0x00008000  /* 32kB  L1 DSP 本地数据 RAM */
#endif

/****************************************************************************/
/*                                                                          */
/*              公共内存区域                                                */
/*                                                                          */
/****************************************************************************/
    SHDSPL2ROM   o = 0x11700000  l = 0x00100000  /* 1MB   L2 共享内置 ROM */
    SHDSPL2RAM   o = 0x11800000  l = 0x00040000  /* 256KB L2 共享内置 RAM */
    SHDSPL1PRAM  o = 0x11E00000  l = 0x00008000  /* 32KB  L1 共享内置程序 RAM */
    SHDSPL1DRAM  o = 0x11F00000  l = 0x00008000  /* 32KB  L1 共享内置数据 RAM */

    EMIFACS0     o = 0x40000000  l = 0x20000000  /* 512MB SDRAM (CS0) */
    EMIFACS2     o = 0x60000000  l = 0x02000000  /* 32MB  异步          (CS2) */
    EMIFACS3     o = 0x62000000  l = 0x02000000  /* 32MB  异步          (CS3) */
    EMIFACS4     o = 0x64000000  l = 0x02000000  /* 32MB  异步          (CS4) */
    EMIFACS5     o = 0x66000000  l = 0x02000000  /* 32MB  异步          (CS5) */

    SHRAM        o = 0x80000000  l = 0x00020000  /* 128KB 共享 RAM */
    DDR2         o = 0xC0001000  l = 0x08000000  /* 128MB  DDR2 分配给 DSP */

	EntryPoint   o = 0xC0000000  l = 0x00000800  /* 2 KB  C 语言入口点 */
	Vector       o = 0xC0000800  l = 0x00000800  /* 2 KB  中断向量表 */

/****************************************************************************/
/*                                                                          */
/*              外设内存区域                                                */
/*                                                                          */
/****************************************************************************/
    SYSCFG0      o = 0x01C14000  l = 0x00001000  /* 4K    SYSCFG0 */
    uPP          o = 0x01E16000  l = 0x00001000  /* 4K    uPP */
    GPIO         o = 0x01E26000  l = 0x00001000  /* 4K    GPIO */
    McBSP1       o = 0x01D11000  l = 0x00000800  /* 2K    McBSP1 */

#ifndef DSP_CORE
/****************************************************************************/
/*                                                                          */
/*              ARM 专有内存区域                                            */
/*                                                                          */
/****************************************************************************/
    ARMROM       o = 0xFFFD0000  l = 0x00010000  /* 64kB  ARM 本地 ROM (ARM ROM Bootloader) */
    ARMRAM       o = 0xFFFF0000  l = 0x00002000  /* 8kB   ARM 本地 RAM */
#endif
}

SECTIONS
{
    .text:_c_int00	>  EntryPoint 				 /* 可执行代码 C 程序入口点*/
    .text			>  DDR2 				     /* 可执行代码 */
    .stack			>  DDR2 				     /* 软件系统栈 */
    .bss			>  DDR2 				     /* 未初始化全局及静态变量 */
    .cio			>  DDR2                      /* C 输入输出缓存 */
    ".vectors"		>  Vector    				 /* 中断向量表 */
    .const			>  DDR2                      /* 常量 */
    .data			>  DDR2                      /* 已初始化全局及静态变量 */
    .switch			>  DDR2                      /* 跳转表 */
    .sysmem			>  DDR2                      /* 动态内存分配区域 */
    .far			>  DDR2                      /* 远程全局及静态变量 */
    .args			>  DDR2
    .ppinfo			>  DDR2
    .ppdata			>  DDR2

    /* TI-ABI 或 COFF */
    .pinit			>  DDR2                      /* C++ 结构表 */
    .cinit			>  DDR2                      /* 初始化表 */

    /* EABI */
    .binit			>  DDR2
    .init_array		>  DDR2
    .neardata		>  DDR2
    .fardata		>  DDR2
    .rodata			>  DDR2
    .c6xabi.exidx	>  DDR2
    .c6xabi.extab	>  DDR2

	/* DDR2 */
    .buffer			>  DDR2

	/* 外设  */
	.Reg_SYSCFG0	>  SYSCFG0
	.Reg_uPP		>  uPP
	.Reg_GPIO		>  GPIO
	.Reg_McBSP1		>  McBSP1
}

//-stack 0x100000
// -heap 0x1000
//-e fix_start
/* =========================================================================*
 * 						Specify the System Memory Map						*
 * =========================================================================*/
  /*
MEMORY
{
    L1P:    o = 0x11E00000        l = 0x00008000
    L1D:    o = 0x11F00000        l = 0x00008000
    L2:     o = 0x11800000        l = 0x00040000
    DDR2:   o = 0xC0000000        l = 0x08000000
}

// ============================================================================
//                 Specify the Sections Allocation into Memory
// ============================================================================


SECTIONS
{
    .cinit        >        DDR2               // Initialization Tables
    .pinit        >        DDR2               // Constructor Tables
    .init_array   >        DDR2               //
    .binit        >        DDR2               // Boot Tables
    .const        >        DDR2               // Constant Data
    .switch       >        DDR2               // Jump Tables
    .text         >        DDR2               // Executable Code
    .text:_c_int00: align=1024 > DDR2         // Entrypoint

    GROUP (NEARDP_DATA)                       // group near data
    {
       .neardata
       .rodata
       .bss                                   // note: removed fill = 0
    }             >        DDR2
    .far: fill = 0x0, load > DDR2             // Far Global & Static Variables
    .fardata      >        DDR2               // Far RW Data
    .stack        >        DDR2               // Software System Stack
    .sysmem       >        DDR2               // Dynamic Memory Allocation Area

    .cio          >        DDR2               // C I/O Buffer
    .vecs         >        DDR2               // Interrupt Vectors
}
*/

