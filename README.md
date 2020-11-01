<<<<<<< HEAD
# ExoControl **v0.1**
Este respositorio foi feito para o trabalho de mentrado do aluno Yecid Moreno.
O objetivo principal é criam uma GUI intuitiva que seja programavel usamdo blocos para o controle do exoesquelo de rehabilitação robótica.

## Mudançãs de versão 

- ### Versão v0.1 (GUI) **\***
    1. Se apresenta um rascunho da GUI    
    2. Concerto de alguns erros

- ### Versão v0.2 
    1. Proximanente ...


=======
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
>>>>>>> master-blocks
