#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#define DefineBLOCKS BlockSUM_INIT();       \
                     BlockPOW_INIT();       \
                     BlockMULTI_INIT();       \
                     BlockNUMK_INIT();       \
                     BlockFUNGEN_INIT();    \
                     BlockSCOPE_INIT();     \
                     BlockDELSYS_INIT();     \
                     BlockREHAMOVE_INIT();     \
                     
                     //Entradas novas de iniciação

                     
                    
#define name_of_object SUM
#include "BLOCKS/BLOCK_SUM.h"

#define name_of_object POW
#include "BLOCKS/BLOCK_POW.h"

#define name_of_object MULTI
#include "BLOCKS/BLOCK_MULTI.h"

#define name_of_object FUNGEN
#include "BLOCKS/BLOCK_FUNGEN.h"

#define name_of_object SCOPE
#include "BLOCKS/BLOCK_SCOPE.h"

#define name_of_object DELSYS
#include "BLOCKS/BLOCK_DELSYS.h"

#define name_of_object REHAMOVE
#include "BLOCKS/BLOCK_REHAMOVE.h"

#define name_of_object NUMK
#include "BLOCKS/BLOCK_NUMK.h"

//Começo  ->  Códigos  novos

//Fim     ->  Códigos  novos

namespace BLOCKS{
    /*
      .   .   .   .
      .   .   .   .
          Códigos de definição em BLOCKS.cpp
      .   .   .   .   
      .   .   .   .   
    */
}