//******************************************************************************
//*                               InitSysVar.c                                 *
//******************************************************************************
//*           Copyright (c) 2020 SKONDA ELECTRONIC LTD                        *
//******************************************************************************
//* FILE NAME  : InitSysPara.c
//* DESCRIPTION:
//* ORIGINATOR : Sven
//* DATE       : 11/07/2022
//* VERSION    : 1.0.0
//******************************************************************************

#include "Includes.h"


static void InituPPPara(void);

void InitSysPara(void)
{
    InituPPPara();
}

static void InituPPPara(void)
{
    uPPRxTx_Init();
}


