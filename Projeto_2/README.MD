# Projeto 2 - Cronômetro Digital com Timer e Interrupções

## Cronometro usando PIC e linguagem C

### Integrantes:
|                          Nome | Nº USP   |
|------------------------------:|----------|
|    Gabriela Passos de Andrade | 12625142 |
|              João Pedro Gomes | 13839069 |
| Luana Hartmann Franco da Cruz | 13676350 |
|     Rafael Cunha Bejes Learth | 13676367 |

## Estrutura do Projeto
O arquivo principal deste projeto é `cronometro.c`, que contém o código em linguagem C para o microcontrolador PIC18F4550, acompanhado de comentários explicativos.

Este repositório também inclui:
- Documento PDF com a especificação do projeto fornecida pelo professor.
- Este arquivo README com explicações detalhadas sobre o funcionamento do código.

## Execução do Programa
O programa pode ser compilado no compilador **MikroC PRO for PIC** e testado no simulador **SimulIDE**, utilizando um esquemático com o PIC18F4550, botões e um display de 7 segmentos. Após a simulação bem-sucedida, o projeto pode ser implementado no kit **EasyPIC v7**, carregando o arquivo `.hex` gerado.

## Funcionamento do Programa
O projeto faz uso do Timer0 com interrupções para controlar a temporização do cronômetro. O display de 7 segmentos começa desligado e só inicia a contagem quando um dos botões (RB0 ou RB1) é pressionado.

### Lógica de Temporização
- **Botão RB0**: Inicia a contagem no display de 0 a 9 em loop, com período de 1 segundo por número.
- **Botão RB1**: Altera a base de contagem para 0,25 segundos, mantendo a contagem de 0 a 9 em loop.
- **Interrupção do Timer0**: Disparada a cada overflow do timer, incrementando um contador e controlando a exibição do display. O Timer0 é reiniciado com valores específicos para manter a precisão necessária.

## Implementação do Código
### Configuração Inicial
O código inicializa as portas de I/O, configura o Timer0 e habilita as interrupções.

### Lógica de Interrupção
A função de interrupção `void __interrupt()` gerencia a atualização do display e o ajuste das contagens, reiniciando o Timer0 com os valores apropriados para o próximo ciclo.

### Funções Utilizadas
- **update_display(int number)**: Converte o número a ser exibido em um padrão de bits e envia o sinal para a Porta D, onde está conectado o display.
- **Configurações de Temporizador e Interrupções**: Incluem a definição de prescaler e o modo de operação do Timer0.

## Considerações Importantes
- **Clock**: O microcontrolador é configurado com um cristal externo HS de 8 MHz.
- **Configuração de Pull-up/Pull-down**: As chaves do kit EasyPIC v7 devem ser ajustadas de acordo com a necessidade (jumper J17 em VCC para pull-down ou GND para pull-up).
- **Simulação no SimulIDE**: Devido a uma falha no Timer0 do SimulIDE, recomenda-se utilizar o menor prescaler possível para valores de simulação mais precisos.

## Procedimentos de Teste
1. **Desenvolvimento e Compilação**: Escrever e compilar o código em **MikroC PRO for PIC**.
2. **Simulação**: Montar o circuito no **SimulIDE** e carregar o arquivo `.hex` para testar.
3. **Implementação Prática**: Implementar o projeto no **EasyPIC v7** após testes bem-sucedidos.

## Recursos
- **Botões**: Utilizados para iniciar e mudar a base de tempo da contagem.
- **Display de 7 segmentos**: Conectado à Porta D para exibir a contagem.
- **Temporizador TMR0**: Configurado para interrupções periódicas.

## Notas Finais
Este projeto permite comparações entre a implementação em C e Assembly, além de explorar as diferenças entre as arquiteturas CISC e RISC em microcontroladores de 8 bits.
