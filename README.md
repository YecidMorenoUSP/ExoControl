# ExoControl **v0.2**
Este respositorio foi feito para o trabalho de mentrado do aluno Yecid Moreno.
O objetivo principal é criam uma GUI intuitiva que seja programavel usamdo blocos para o controle do exoesquelo de rehabilitação robótica.

## Mudançãs de versão 

- ### Versão v0.1 (GUI)
    1. Se apresenta um rascunho da GUI    
    2. Concerto de alguns erros 
    3. Implementação de subprocesos nos blocos

- ### Versão v0.2 
    1. Bloco SPAR, plataforma robotica de tornozelo
    2. ExoRobot atualizado
    3. Leitura de EPOS en RT, analogicas e digitais
    4. Protocolo CAN-Open e USB

- ### Versão v0.3
    1. Arduino Protocol
    2. ESP-32 
    3. Realidade Virtual, HTC VIVE
    4. Server, para DB e opçoes remotas



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


## GIF

### Test con EMGs en el brazo
![Alt Text](https://github.com/YecidMorenoUSP/PublicFiles/blob/master/ExoControl/GIF/EMG1.gif?raw=true)

### Test con EMGs en las piernas
![Alt Text](https://github.com/YecidMorenoUSP/PublicFiles/blob/master/ExoControl/GIF/EMG2.gif?raw=true)

### Test con Rehamove3, FES en el brazo
![Alt Text](https://github.com/YecidMorenoUSP/PublicFiles/blob/master/ExoControl/GIF/FES1.gif?raw=true)
