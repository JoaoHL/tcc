## O que é?

[LegUp](http://legup.eecg.utoronto.ca/) é um arcabouço de síntese de alto nível open-source desenvolvido na Universidade de Toronto (Canadá). O LegUp converte códigos em C para Verilog, usando algumas ferramentas comerciais como o Quartus Prime II, da Intel, e o Tiger MIPS Processor, da Universidade de Cambridge (Reino Unido). 

Atualmente em sua versão 4.0, seu uso é simples e versátil, além de apresentar uma arquitetura que permite alterações em seus algoritmos, como os de escalonamento e emparelhamento, de maneira descomplicada. Como sua arquitetura usa uma compilação em escopo de funções para implementação em hardware - isto é, ele usa funções como unidade básica para síntese de hardware -, é possível especificar funções para aceleração em hardware enquanto o resto do programa é executado em software; tal técnica é chamada de "fluxo híbrido" pelos criadores da ferramenta.

## Visão geral

[INSERIR FIGURA 'legup-flow.png' AQUI]

A figura acima representa o fluxo geral do arcabouço. No passo (1), um programa em C desenvolvido pelo usuário é compilado para executar em um processador pelo LegUp. O binário resultante é executado em (2) enquanto é analisado dinamicamente pelo próprio processador por partes do código que podem se beneficiar consideravelmente de uma aceleração por hardware (*self-profiling*). Após a etapa de *self-profiling*, os dados da análise são disponibilizados para o usuário no passo (3), onde ele deve escolher quais funções serão executadas convertidas para hardware. Feitas as escolhas do usuário, a ferramenta cria a representação em hardware das funções marcadas no passo (4) e, no passo (5), recompila o programa do usuário usando funções embrulhadas (*wrapper functions*) que chamam o acelerador de hardware correspondente à função sintetizada pelo LegUp.

# Compilação

O código de entrada utilizado pelo arcabouço deve ser escrito em C e possui limitações. A versão gratuita mais recente da ferramenta não suporta recursão, aritmética de ponto flutuante ou alocação dinâmica de memória; entretanto, o LegUp consegue sintetizar estruturas, controles de fluxo, aritmética de inteiros, manipulação de ponteiros (inclusive de funções), dentre outras características da linguagem. A compilação do código é feita usando o projeto LLVM, descrito no capítulo anterior.

[explicar melhor sobre a LLVM numa seção ou capítulo a parte, ela merece]

# Processador

O processador utilizado pelo arcabouço é o [Tiger MIPS Soft Processor](https://www.cl.cam.ac.uk/teaching/0910/ECAD+Arch/mips.html), um processador que pode ser implementado usando síntese lógica, isto é, seu comportamento pode ser descrito por uma linguagem de descrição de hardware (e.g. Verilog) e posteriormente convertido em um design de hardware. 

A vantagem de se usar o Tiger é seu código aberto e sua arquitetura RISC, que permitem a adição de novas instruções no processador. Essas características são usadas para criar os instrumentos de *self-profiling*, resultando em uma análise extremamente precisa, uma vez que ela é feita através das instruções do processador. Outra vantagem é na análise por parte dos usuários, já que o Tiger possui uma documentação de fácil leitura. Isso dá oportunidade ao usuário de verificar as instruções resultantes da compilação do código em C e otimizá-las manualmente.

Apesar da utilização do Tiger, que é um *soft processor*, a versão mais recente do LegUp open-source também dá suporte aos processadores *hard processor* da Altera e da Xilinx. Um *hard processor* não pode ser descrito simplesmente por uma HDL e, por isso, seu design é construído de forma rígida no *chip*. Isso tira a flexibilidade de customização do processador, mas aumenta sua eficiência em termos de energia, latência e área.

**Nota: a versão mais recente do LegUp, a 5.0, tornou-se comercial. Veja mais [aqui](https://www.legupcomputing.com/main/about#about)**