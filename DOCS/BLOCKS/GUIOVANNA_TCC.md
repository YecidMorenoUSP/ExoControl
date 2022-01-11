## GIOVANNA_TCC

### Propiedades



                |----------------|
    POS_ANKLE >-|                |-> FES
    TORQUE    >-|  GIOVANNA_TCC  |
         EMG1 >-|                |-> K do ROBO
         EMG2 >-|----------------|


1. Salvar os dados das EMG
1. Salvar os dados das EMG
1. Salvar os dados das POsição
2. Salvar os dados do Torque
3. Salvar os dados da impedancia


----
Dados do Cliente_TCP: POS_ANKLE , Torque e impedancia
Dados para o Cliente_TCP, Impedancia do Robô

interface:
Nome do usuario
Impedância do robô -> N_input 
Amplitude das FES  -> N_input
Botão TEST 1 -> 
Botão TEST 2 -> 
Botão TEST 3 -> 
Botão TEST 4 -> 

Text_input para a impedancia do robô

## ROBÔ
IP: 192.168.0.66 </br>
PORT: 8000

### Protocolo
0. Configurar as FES  -> Fora do aplicativo 
   1. Frequência
   2. Amplitude

1. Teste só a pessoa, K = 0 , FES = 0
   1. Sõ salvar dados
   2. Pegar os dados de posição para estimar o tempo de reposta do usuario

2. TEste K = 0 , FES = 1
   1. Sõ salvar dados

3. TEste K = K , FES = 0
   1. Sõ salvar dados
   
4. TEste K = K , FES = 1
   1. Sõ salvar dados
   
   
22/nov/2021
   Salvar dados do Anklebot para analizar os tempos depois do flanco de descida. (MatLab)
   Colocar us 4 botoes para cada etapa do teste







