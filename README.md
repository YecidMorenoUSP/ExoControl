# ExoControl

Si desea adicionar un bloque necesita modificar : 
1. Clonar el archivo BLOCKS/BLOCK_**DEFAULT**.h

2. Ir al archivo BLOCKS.cpp y adicionar
    - #define DefineBLOCKS Block**DEFAULT**_INIT(); \
    - #define name_of_object **DEFAULT**
    - #include "BLOCKS/BLOCK_**DEFAULT**.h"

3. Ir al archivo BLOCKS.h y adicionar
    -  BLKType_**DEFAULT**,  NOTA : debe ser antes del *BLKType_COUNT*

## LINES
Si desea ver la salida de un bloque sólo necesita ubicar el mouse y presionar control
