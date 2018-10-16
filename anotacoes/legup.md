## O que é?

[LegUp](http://legup.eecg.utoronto.ca/) é um arcabouço de síntese de alto nível open-source desenvolvido na Universidade de Toronto (Canadá). O LegUp converte códigos em C para Verilog, usando algumas ferramentas comerciais como o Quartus Prime II, da Intel, e o Tiger MIPS Processor, da Universidade de Cambridge (Reino Unido). 

Atualmente em sua versão 4.0, seu uso é simples e versátil, além de apresentar uma arquitetura que permite alterações em seus algoritmos, como os de escalonamento e emparelhamento, de maneira descomplicada. Como sua arquitetura usa uma compilação em escopo de funções para implementação em hardware - isto é, ele usa funções como unidade básica para síntese de hardware -, é possível especificar funções para aceleração em hardware enquanto o resto do programa é executado em software; tal técnica é chamada de "fluxo híbrido" pelos criadores da ferramenta.

## Visão geral

[INSERIR FIGURA 'legup-flow.png' AQUI]

A figura acima representa o fluxo geral do arcabouço. No passo (1), um programa em C desenvolvido pelo usuário é compilado para executar em um processador. O binário resultante é executado em (2) enquanto é analisado dinamicamente pelo próprio processador por partes do código que podem se beneficiar consideravelmente de uma aceleração por hardware (*self-profiling*). Após a etapa de *self-profiling*, os dados da análise são disponibilizados para o usuário no passo (3), onde ele deve escolher quais funções serão executadas em hardware dedicado. Feitas as escolhas do usuário, a ferramenta cria a representação em hardware das funções marcadas no passo (4) e, no passo (5), recompila o programa do usuário usando funções embrulhadas ("*wrapper functions*") que chamam o aceleradores de hardware correspondentes às funções sintetizadas pelo LegUp.

# Compilação

O código usada como entrada do arcabouço deve ser escrito em C e possui limitações. A versão gratuita mais recente da ferramenta não suporta funções recursivas, aritmética de ponto flutuante ou alocação dinâmica de memória; entretanto, o LegUp consegue sintetizar estruturas, controles de fluxo, aritmética de inteiros, manipulação de ponteiros (inclusive de funções), dentre outras características da linguagem.

A compilação é feita no *front-end* da LLVM usando o Clang 3.5, pertencente ao projeto LLVM, e cria um arquivo de *bytecode* contendo a LLVM IR correspondente ao programa de entrada. Algumas funções em C que lidam com o manejo da memória (como `memset` e `memcopy`, da biblioteca `<string.h>`) são compiladas em funções já implementadas pela LLVM, chamadas *funções intrínsecas*. Para contornar a situação, passes do otimizador são executados no código para substituir as funções intrínsecas para funções implementadas manualmente pelo arcabouço, gerando um *bytecode* composto apenas de LLVM IR, sem funções intrínsecas.

# Processador

O processador utilizado pelo arcabouço é o [Tiger MIPS Soft Processor](https://www.cl.cam.ac.uk/teaching/0910/ECAD+Arch/mips.html), um processador que pode ser implementado usando síntese lógica, isto é, seu comportamento pode ser descrito por uma linguagem de descrição de hardware (e.g. Verilog HDL) e posteriormente convertido em um design de hardware. Tal tipo de processador é denominado *softprocessor*. Ele é usado na elaboração do circuito apenas nos fluxos híbrido e puro *software*, onde há a necessidade de um módulo central que comande o funcionamento do circuito. A vantagem de se usar o Tiger é seu código aberto e sua arquitetura RISC, que permitem a adição de novas instruções no processador de maneira muito menos complexa que a arquitetura CISC.

A possibilidade de modificação do processador do circuito é a característica chave do processo de *self-profiling* que o LegUp realiza em seu fluxo de execução. Ao adicionar instrumentações para observar a execução do programa, é possível dizer quais instruções são mais utilizadas e por quais funções elas são mais chamadas. Isso permite uma análise extremamente precisa, uma vez que ela é feita a nível de instrução. Outra vantagem é na análise por parte dos usuários, já que o Tiger possui uma documentação de fácil leitura, dada a complexidade do seu funcionamento. Isso dá oportunidade ao usuário de verificar as instruções resultantes da compilação do código em C e otimizá-las manualmente, de acordo com suas necessidades.

Apesar da utilização do Tiger, que é um *softprocessor*, a versão mais recente do LegUp open-source também dá suporte aos processadores *hard processor* da Altera e da Xilinx. Um *hard processor* não pode ser descrito simplesmente por uma HDL e, por isso, seu design é construído de forma rígida no *chip*, como propriedade intelectual. Isso tira a flexibilidade de customização do processador, mas aumenta sua eficiência em termos de energia, latência e área.

**Nota: a versão mais recente do LegUp, a 5.0, tornou-se comercial. Veja mais [aqui](https://www.legupcomputing.com/main/about#about)**