# Resumo (elaborar melhor)

O presente trabalho visa o estudo e experimentação do uso de ferramentas de síntese de alto nível para o design de circuitos. O intuito é destacar tecnologias emergentes de hardware, como as FPGAs, assim como aproximar engenheiros de software do desenvolvimento de hardware.

Para tanto, foi usado o LegUp, um arcabouço de código aberto para síntese de alto nível em FPGAs. Logo, o estudo do funcionamento interno e uso dessa ferramenta foi primordial para a elaboração do projeto. Com ele, algoritmos foram desenvolvidos na linguagem de programação C para processamento em software e em hardware e, dessa forma, efetuar-se a avaliação de desempenho nos dois tipos de processamento.

Como efeito secundário, foi criada uma referência em português para o estudo e uso de FPGAs e síntese de alto nível usando o sistema operacional Ubuntu, a placa SoC FPGA Cyclone V, da Altera, e o arcabouço LegUp High-Level Synthesis.

# Introdução (terminar e elaborar melhor)

O desenvolvimento e pesquisa em hardware sofrem atualmente com um déficit de profissionais em relação aos de software. O número de engenheiros de software ultrapassa o de engenheiros de hardware numa proporção de quase 10 pra 1 [colocar ref]. [colocar mais coisas aqui]

Apenas o uso de ferramentas de síntese de alto nível, por si só, não é um atrativo suficiente para despertar interesse no desenvolvimento de hardware pelos engenheiros de software. Ainda há o empecilho de se implementar o design do hardware, o que pode ser custoso e demorado. Atualmente, fabricar uma única peça de hardware customizado pode custar na ordem de milhares de reais, bem como demorar meses entre o pedido e a entrega no Brasil [colocar ref]. Não só o custo e o tempo são chaves nesse processo, como também a reusabilidade: cada circuito ainda pode apresentar defeitos de fabricação que inviabilizam seu uso, acarretando em um novo pedido, com mais dinheiro e tempo consumidos.

---

# FPGAs

*FPGA*s (do inglês *Field programmable gate array*) são dispositivos de silício que podem ser programados após sua fabricação, permitindo que quase qualquer *design* de circuito digital possa ser implementado nele. Essa maleabilidade de implementação torna-os atrativos para tarefas que envolvam a produção e alteração de *designs* de circuitos lógicos, pois o custo e tempo de execução dessas atividades são muito reduzidos em comparação ao tradicional ciclo de desenvolvimento com o uso de dispositivos *ASIC*s (do inglês *Application-specific integrated circuit*). Como consequência, *FPGA*s permitem que o *design* seja concluído em um menor tempo para poder ser lançado no mercado (o dito *time to market*).


## Programabilidade de uma FPGA

A flexibilidade do *FPGA* se deve à sua capacidade de ser reprogramada após sua fabricação. Para tal, há o uso de *switch*s programáveis em suas rotas de interconexão, isto é, podemos conectar ou desconectar as rotas de comunicação da forma que quiseremos. Assim, usam-se certas tecnologias de programação de circuitos que guardam os estados desses *switch*s. Este fato é o que faz com que cerca de 90% da área útil do *FPGA* seja destinado apenas para a implementação das rotas de intercomunicação do circuito.

É preciso algum tipo de tecnologia para poder reprogramar tais rotas de comunicação, mais precisamente, memórias, e de preferências as que sejam não-voláteis, infinitamente reprogramáveis, baratas e que consumam pouca energia. Atualmente, os três métodos mais utilizados são as tecnologias de *SRAM*, de memórias *flash* e de fusíveis, todas com suas vantagens e desvantagens.

[Resumir as tecnologias de programabilidade em parágrafos ao invés de seções]

### SRAM

A *SRAM* ('Static Random Access Memory', ou 'memória estáticas de acesso aleatório') são um tipo de memória volátil que utiliza uma combinação de 6 transistores para guardar um *bit* de informação. O termo 'estático' refere-se à falta de necessidade de *refresh*s em seu circuito. Note que isso não significa que, na ausência de corrente elétrica, o estado se manterá: caso haja uma queda de energia, a memória perderá o dado nela contido.

Devido à sua característica estática, as *SRAM*s são mais rápidas e consomem menos energia que as *DRAM*s. Entretanto, como as *SRAM*s necessitam de 6 transistores e muito mais espaço que as *DRAM*s, que utilizam apenas 1 transistor e 1 capacitor, aquelas são muito mais caras e demandam mais espaço no circuito para serem implementadas, além de ambas serem voláteis.

### Memórias *flash*

As memórias *flash* ou baseadas em EEPROMs ('Electrally Erasable-Programmable Read-Only Memory', ou 'memória exclusiva para leitura eletricamente programável e apagável') são memórias não-voláteis que podem ser reconfiguradas através do uso de luz ultravioleta e descargas elétricas. Além de não-voláteis, também são estáticas e portanto consomem pouca energia, enquanto também necessitam de menos área de implementação que as *SRAM*s; no entanto, são mais caras e só podem ser programadas um número finito de vezes antes de pararem de funcionar adequadamente. 

### Memória baseada em fusíveis

É o tipo de memória com menor área de implementação dentre as citadas. Essa tecnologia utiliza fusíveis como *switches*: uma vez queimados, eles implementarão as rotas desejadas no FPGA, o que explica sua natureza não-volátil e sua rapidez. Porém o uso de fusíveis tem desvantagens notáveis, como a programabilidade única da placa.

Dentre as tecnologias de programação citadas, todas possuem suas vantagens e desvantagens. O uso mais comum, atualmente, é de FPGAs que utilizam SRAMs para sua programabilidade, pois além de todas as vantagens citadas e apesar das desvantagens, as SRAMs seguem o padrão *CMOS* ('Complementary Metal-oxyde semiconductor', ou 'semicondutor de metal-óxido complementar') de processo de fabricação de circuitos, o que barateia sua produção e sua predominancia no mercado de semicondutores.


## Componentes de um *FPGA*

Os *FPGA*s são compostos, basicamente, por:

- Blocos lógicos
- Rotas de interconexão
- Blocos de E/S (entrada e saída)

Os blocos lógicos são configuráveis e implementam funções lógicas e armazenamento de dados (i.e. memória). Os blocos de E/S recebem e enviam dados para fora do *chip*. Por fim, as rotas de interconexão conectam os blocos lógicos entre si e entre os blocos de E/S. Uma forma de visualizar esses componentes é através de uma matriz, onde os blocos lógicos estão dispostos bidimensionalmente, numa grade, e conectados pelas rotas de interconexão. Nas bordas dessa matriz se encontram os blocos de E/S, integrados à matriz pelas rotas de interconexão, servindo para a comunicação do *FPGA* com dispositivos exteriores a ele.


### Blocos lógicos de um FPGA

Os blocos lógicos configuráveis (BLCs) são as unidades que provêem capacidade lógica e de armazenamento para o FPGA. BLCs podem ser implementados de diversas maneiras, desde simples transistores até processadores inteiros, e essa implementação define sua granularidade. BLCs com granularidade muito pequena, como transistores, acabam se utilizando de espaço demais e torna os ineficientes. Por outro lado, os de granularidade muito grande, como processadores, podem representar um desperdício de recurso quando tratamos de funções mais simples.
Entre esses máximos, temos um espectro de implementações de BLCs. 

Os BLCs são compostos blocos lógicos básicos (BLBs), que podem ser usados em conjunto ou de forma isolada para formar um BLC (isto é, um BLC pode ser composto de um único BLB ou de um conjunto deles). As componentes usadas nesses BLBs podem variar, mas a fabricante da placa que será usada neste trabalho, a Altera (fabricante da SoC FPGA Cyclone V) utiliza *lookup tables* e *flip-flops* para armazenamento. *Lookup tables* (LUTs) são unidades parecidas com multiplexadores, onde temos uma entrada de *k* bits e um código de configuração de *2^k* bits, formando uma LUT chamada k-LUT. A depender do código de configuração usado, a entrada de *k* bits retorna uma possível saída também de *k* bits, ou seja, uma k-LUT pode retornar qualquer valor de uma determinada função booleana f tal que ```f: {0, 1}^k => {0, 1}^k```. A vantagem do uso de LUTs reside em não ter uma granularidade nem muito pequena, nem muito grande, permitindo o uso em conjunto para implementações mais complexas.

Apesar do uso de LUTs ou outros métodos para implementar BLBs, como NANDs, esses métodos são mais usados para criar a parte programável do FPGA. Uma parte dele pode vir já programada com blocos lógicos especializados, como processadores de sinais digitais (conhecidos como DSPs, ou *digital signals processor*), multiplicadores, somadores, ALUs inteiras, todos criados de forma otimizada para suas tarefas. Estes são chamados de blocos rígidos, pois não podem ser reprogramados, apenas usados como estão no FPGA. Isso implica em um possível desperdício de espaço e recursos no caso desses blocos não serem utilizados pelo circuito, mas também traz a vantagem de se usar blocos feitos especialmente para determinadas tarefas.

### Rede de interconexão

Como dito anteriormente, a flexibilidade de um FPGA vem da capacidade de ter sua rede de interconexão reprogramada. Essa rede precisa ser flexível não só em termos de configuração de rotas, mas também de tipos de fios presentes no dispositivo para poder implementar uma grande variedade de circuitos. Apesar da maior parte das componentes de um circuito apresentar localidade (isto é, se localizarem perto umas das outras), há conexões que podem necessitar de fios mais longos.
Cerca de 85% da área de um FPGA consiste da rede de interconexão entre os blocos lógicos. Visando otimizar a comunicação de acordo com a finalidade do circuito, essa rede pode ser construída usando arquiteturas diferentes. Duas destas são notáveis: a baseada em malha e a hierárquica.

[explicar resumidamente sobre redes em malha e hierárquica. Tinha escrito com detalhes mas tirei]

## Desvantagens

A maior vantagem de *FPGA*s - sua flexibilidade - também é a causa de sua maior desvantagem. Tal característica das *FPGA*s baseia-se principalmente na reprogramação das rotas de intercomunicação entre os blocos lógicos e blocos de E/S. Entretanto, a área usada por tais rotas para ocupa a maior parte do dispositivo, chengando a quase 90% da área útil do dispositivo, para permitir a sua reprogramação. Além de maiores que os *ASIC*s, as *FPGA*s são mais lentas e consomem mais energia, também por conta da sua fabricação visando a flexibilidade de implementações.

---

# Síntese de alto-nível 

## Definição

Síntese de alto nível ('High level synthesis', ou HLS) é o processo de transformação linguagens de programação de alto nível para sintetizar arquiteturas RTL ('*Register-transfer level*' ou 'nível de registrador e transferência'), isto é, sintetizar arquiteturas de circuitos digitais síncronos a partir de descrições comportamentais (ou algorítmicas) do *hardware*. As saídas geradas são, em sua maioria, arquivos em linguagens HDL ('*Hardware description language*' ou linguagem de descrição de *hardware*), que são usadas para configurar o *hardware*. Tais ferramentas realizam o mesmo fluxo básico na sintetização dos circuitos, desde a especificação comportamental desejada até a geração dos arquivos em HDLs.

## Fluxo de síntese

O fluxo de síntese das ferramentas de HLS segue o mesmo padrão, que envolve:

1. Modelagem (ou especificação)
2. Compilação
3. Alocação \*
4. Escalonamento \*
5. emparelhamento \*
6. Geração


## Modelagem

A etapa de modelagem consiste em descrever o comportamento desejado do *hardware* em questão, onde as entradas, saídas e forma de processamento dos dados são especificadas através do uso de linguagens programação de alto nível. As ferramentas de HLS, tais como o [OpenCL](https://www.khronos.org/opencl/) e o [LegUp](http://legup.eecg.utoronto.ca/), comumente usam linguagens com sintaxes baseadas em C.
A descrição é dita comportamental ou atemporal, onde o comportamento descrito recebe todos os dados de entrada simultaneamente, realiza seu processamento de forma instantânea, e retorna todos os dados de saída de uma vez. Esse tipo de descrição não é condizente com a forma como um sistema de *hardware* funciona, então há a necessidade de conversão do tipo atemporal para temporal.
É importante ressaltar que nem todos os algoritmos podem ser descritos diretamente em *hardware*. Um bom exemplo são algoritmos recursivos, que não são convertidos para formas iterativas de maneira automatizada.

## Compilação

A modelagem atemporal deve ser compilada em outra temporal, onde os ciclos de *clock* do circuito são levados em consideração na execução das operações descritas. Para tanto, um modelo formal do comportamento do circuito é criado para visualizar melhor as dependências de dados e de controle de fluxo do algoritmo.

O modelo é representado por um grafo direcionado, chamado DFG ('*Data flow graph*' ou grafo de fluxo de dados) onde os arcos são valores constantes ou de variáveis e os vértices são operações que usam os valores. Essa forma de representação explicita o paralelismo intrínseco ao algoritmo descrito, facilitando as fases seguintes da síntese. Como os DFGs representam apenas fluxos de dados, há dificuldades em utilizá-los para representar *loops* limitados por variáveis ao invés de constantes (i.e `for (int i = 0; i < n; i++)`) ou trechos condicionais (`if-else`s). Para tanto, seria necessária transformações no grafo que, dependendo da complexidade da implementação, poderia gastar muito mais memória para armazenamento e muito mais processamento.

Pensando nisso, uma versão estendida do DFG foi criada, chamada CDFG ('*Control and Data Flow Graph*' ou grafo de fluxo de controle e dados), onde os arcos são controles de fluxo (como `if-else`s e `goto`s) e os nós são chamados de *blocos básicos*. Blocos básicos são blocos de código sequenciais sem pontos de saída (por exemplo, um `return` ou `goto` no meio do código) ou ramificações (causadas por fluxos condicionais, por exemplo) (podemos dizer que blocos básicos são os blocos de código entre um `jump target` e um `jump`). Os CDFGs são mais expressivos por conseguirem representar tanto o fluxo de dados quanto o de controle; entretando, faz-se necessária uma análise mais profunda para explorar o paralelismo dentro dos blocos básicos e expor o parelelismo entre os blocos.


## Alocação

A compilação do modelo comportamental explicita as operações feitas no algoritmo e em qual ordem devem ser feitas. Após essa etapa, é preciso transformar essas representações abstratas no modelo lógico/físico do circuito.

Na fase de alocação, ocorre a identificação dos recursos de *hardware* necessários para implementar o circuito desejado. Dentre esses recursos, podemos citar as unidades funcionais, unidades de memória, de transferência etc. A alocação destes é feita usando a biblioteca RTL das ferramenta de HLS. A biblioteca contém os recursos disponíveis para cada modelo de *hardware*, bem como dados sobre esses recursos (e.g. área necessária, consumo de energia, latência), necessários para outras fases da síntese.

Vale lembrar que certas componentes a serem alocadas, principalmente as de comunicação (como os barramentos), podem ser deixadas para serem alocadas posteriormente a fim de otimização, como depois da fase de emparelhamento (para otimizar as comunicações entre as unidades funcionais) ou da fase de escalonamento (para não introduzir restrições de paralelismo entre as operações das unidades funcionais).

## Escalonamento

Como apontado anteriormente, o processo de HLS transforma uma descrição atemporal para uma temporal, ou seja, que considera os ciclos de *clock* do sistema de *hardware*. A fase de escalonamento se encarrega de planejar o processamento dos dados de entrada a cada um desses ciclos, levando em consideração os dados especificados, as operações, as restrições desejadas do modelo (tais como área ou consumo de energia máximos) e os componentes alocados.

Durante essa fase, a representação do modelo em um CDFG é de extrema valia. Isso porque com o CDFG, evidencia-se o paralelismo entre blocos básicos (e, dependendo da profundidade da análise, o paralelismo dentro deles), e este é aproveitado pelo escalonador para otimizar o processamento de dados dentro das restrições estabelecidas. Aproveitam-se possíveis falta de dependência entre  dados para realizar múltiplas operações por ciclo de *clock*, sob a restrição de haver unidades funcionais suficientes para tal (vê-se aí, por exemplo, a relação entre aumentar a área implementada de circuito implementada, número de recursos alocados e energia consumida, e diminuir o consumo de tempo e aumentar a taxa de processamento de dados). Dessa forma, uma operação pode ser escalonada pra ser executada ao longo de um ou mais ciclos de *clock*.

É também durante essa fase que pode ocorrer a comunicação entre a alocação e o emparelhamento para otimizar aspectos do *layout* do circuito digital, pois estas 3 fases estão intimamente ligadas por lidarem com o circuito de fato (diferente da modelagem e compilação, que lidam com o comportamento de forma ainda abstrata).

## 2.5 emparelhamento

Para cada operação que nosso algoritmo descreve, precisamos não só alocar os recursos necessários para efetuar a operação como também ligar tanto as operações quanto as variáveis aos recursos alocados. A fase de emparelhamento (do inglês *binding*) é a responsável por essa tarefa, utilizando-se dos resultados das outras fases para fazer tais ligações. Nela, podem ocorrer mais otimizações (usufruindo da comunicação com as fases de escalonamento e alocação, como já citado) para diminuir a área utilizada, por exemplo: se uma mesma operação é feita em ciclos diferentes, pode-se reutilizar a unidade funcional daquela operação. Da mesma forma, unidades de memória podem guardar valores de variáveis que possuem um tempo de vida diferente.

## 2.6 Geração

Finalmente, após o algoritmo de síntese ter realizado todas as suas operações, é gerado um arquivo com uma arquitetura RTL representando o comportamento descrito pelo modelo. O arquivo de saída pode ser de diversos formatos, tais como SystemC, Verilog e VHDL. Vale ressaltar que cada *framework* geralmente trabalha com um número limitado de modelos de placa FPGA, uma vez que estão cada vez mais frequentes o uso de FPGAs em placas integradas, tornando-se uma SoC FPGA (do inglês "*System-on-a-Chip FPGA*"). Um pouco mais será dito sobre SoC FPGAs e sistemas RTL nas anotações sobre arquitetura FPGA.

\*: Não necessariamente nessa ordem. Vide parte 2.7 para melhores explicações

## 2.7 Alocação, Escalonamento e emparelhamento: considerações especiais

Essas três fases estão intimamente ligadas, como já reforçado ao longo da parte 2. O motivo principal é o fato delas serem o centro da síntese, que leva a descrição abstrata para a arquitetura RTL. Devido a essa importância, a ordem de execução delas estabelece qual o foco de uma ferramenta na hora de confecionar o circuito. Alguns exemplos são:

- A alocação pode ocorrer antes quando há restrição de recursos. Dessa forma, a ferramenta otimiza a latência e o *throughput* (isto é, a quantidade de dados processados por unidade de tempo) do circuito;
- Em contrapartida, o escalonamento pode tomar lugar antes da alocação quando há restrição de tempo. Assim, o algoritmo de síntese tenta otimizar a quantidade de recursos alocados e área utilizada dada a restrição.
- Por último, a execução das três fases podem ocorrer de forma simultânea e intercomunicativa, mas isso acarreta em um modelo complexo demais, que acaba não sendo possível aplicar o algoritmo de síntese em exemplos realistas.

Em geral, aplicações com restrições diferentes exigem ordens de execução diferentes. Restrições de recurso (*e.g.* área de implementação, quantidade de unidades funcionais etc) rodam primeiro a alocação, para estabelecer o máximo de recursos e área que o circuito poderá utilizar e, a partir disso, otimizar sua geração nos outros passos. Por outro lado, restrições de tempo exigem o uso prévio do escalonador para estabelecer a latência máxima do processamento dos dados e, em seguida, ocorrem as otimizações possíveis em cima desse primeiro resultado.

---
# LegUp High-Level Synthesis

## O que é?

[LegUp](http://legup.eecg.utoronto.ca/) é um arcabouço de síntese de alto nível open-source desenvolvido na Universidade de Toronto (Canadá). O LegUp converte códigos em C para Verilog, usando algumas ferramentas comerciais como o Quartus Prime II, da Intel, e o Tiger MIPS Processor, da Universidade de Cambridge (Reino Unido). 

Atualmente em sua versão 4.0, seu uso é simples e versátil, além de apresentar uma arquitetura que permite alterações em seus algoritmos, como os de escalonamento e emparelhamento, de maneira descomplicada. Como sua arquitetura usa uma compilação em escopo de funções para implementação em hardware - isto é, ele usa funções como unidade básica para síntese de hardware -, é possível especificar funções para aceleração em hardware enquanto o resto do programa é executado em software; tal técnica é chamada de "fluxo híbrido" pelos criadores da ferramenta.

## Visão geral

[INSERIR FIGURA 'legup-flow.png' AQUI]

A figura acima representa o fluxo geral do arcabouço. No passo (1), um programa em C desenvolvido pelo usuário é compilado para executar em um processador pelo LegUp. O binário resultante é executado em (2) enquanto é analisado dinamicamente pelo próprio processador por partes do código que podem se beneficiar consideravelmente de uma aceleração por hardware (*self-profiling*). Após a etapa de *self-profiling*, os dados da análise são disponibilizados para o usuário no passo (3), onde ele deve escolher quais funções serão executadas convertidas para hardware. Feitas as escolhas do usuário, a ferramenta cria a representação em hardware das funções marcadas no passo (4) e, no passo (5), recompila o programa do usuário usando funções embrulhadas (*wrapper functions*) que chamam o acelerador de hardware correspondente à função sintetizada pelo LegUp.

# Compilação

O código de entrada utilizado pelo arcabouço deve ser escrito em C e possui limitações. A versão gratuita mais recente da ferramenta não suporta recursão, aritmética de ponto flutuante ou alocação dinâmica de memória; entretanto, o LegUp consegue sintetizar estruturas, controles de fluxo, aritmética de inteiros, manipulação de ponteiros (inclusive de funções), dentre outras características da linguagem.

A compilação do código é feita usando a LLVM. LLVM (Acrônimo para "Low-level virtual machine") é um projeto de código aberto que dispobiliza ferramentas de compilação para diversas linguagens. Tais ferramentas conseguem otimizar o código em tempo de compilação e ligamento do código, provido de um *front-end* e um *back-end* do usuário. Por *front-end* entende-se um *parser* e um *lexer* da linguagem de programação a qual se deseja compilar, enquanto que por *back-end* entende-se uma lógica que converte o código próprio da LLVM (como um "bytecode" de uma JVM) em código de máquina. No caso do LegUp, o *front-end* é igual ao do GCC para o processamento do código de entrada, e o *back-end* foi substituído pelo algoritmo de síntese de hardware do arcabouço. Um exemplo de uma ferramenta famosa pertencente ao projeto LLVM é o [Clang](http://clang.llvm.org/), um compilador de C/C++/Objective-C alternativo ao GCC, que pode apresentar perfomances superiores a este.

[explicar melhor sobre a LLVM numa seção ou capítulo a parte, ela merece]

# Processador

O processador utilizado pelo arcabouço é o [Tiger MIPS Soft Processor](https://www.cl.cam.ac.uk/teaching/0910/ECAD+Arch/mips.html), um processador que pode ser implementado usando síntese lógica, isto é, seu comportamento pode ser descrito por uma linguagem de descrição de hardware (e.g. Verilog) e posteriormente convertido em um design de hardware. 

A vantagem de se usar o Tiger é seu código aberto e sua arquitetura RISC, que permitem a adição de novas instruções no processador. Essas características são usadas para criar os instrumentos de *self-profiling*, resultando em uma análise extremamente precisa, uma vez que ela é feita através das instruções do processador. Outra vantagem é na análise por parte dos usuários, já que o Tiger possui uma documentação de fácil leitura. Isso dá oportunidade ao usuário de verificar as instruções resultantes da compilação do código em C e otimizá-las manualmente.

Apesar da utilização do Tiger, que é um *soft processor*, a versão mais recente do LegUp open-source também dá suporte aos processadores *hard processor* da Altera e da Xilinx. Um *hard processor* não pode ser descrito simplesmente por uma HDL e, por isso, seu design é construído de forma rígida no *chip*. Isso tira a flexibilidade de customização do processador, mas aumenta sua eficiência em termos de energia, latência e área.

**Nota: a versão mais recente do LegUp, a 5.0, tornou-se comercial. Veja mais [aqui](https://www.legupcomputing.com/main/about#about)**

---

# Benchmarking 

'Benchmarking', na Computação, é o ato de medir o desempenho de um sistema, seja ele de 'hardware' ou de 'software'. Para tanto, faz-se o uso de monitoramento das execuções de testes em cima do sistema a ser avaliado, capturando dados tais como número de falhas de 'cache' e de más especulações de instruções. O 'benchmarking' de um sistema pode ser feito através de 4 metodologias: hardware on-chip, hardware off-chip, software e instrumentação microprogramada.

## Hardware on-chip

Neste método, usamos os dados gravados pelo próprio processador, dados estes compostos principalmente de contadores de eventos. A captura de dados é feita através de instruções especiais, que atualmente são descritas pelos fabricantes dos processadores, em registradores de controle especiais . A principal vantagem é a baixa interferência da medição de eventos na taxa de processamento, mas apesar das possíveis centenas de dados capturados, cerca de apenas 2 a 10 medições podem ser feitas simultaneamente, devido à baixa disponibilidade desses registradores.

## Hardware off-chip

Este método é parecido com o on-chip, mas utiliza hardware exterior à CPU. Dessa forma, a capacidade de armazenamento de medições aumenta de forma significativa; entretanto, a necessidade de disparar interrupções na CPU para reter os dados torna-o mais invasivo, diminuindo o uso da CPU próprio para processamento.

## Benchmarking por software

O uso de software para realizar o benchmarking de um sistema apresenta a grande vantagem de ser mais fácil de ser realizado do que os por hardware. No entanto, também é o método mais invasivo, além de comumente realizar-se medições apenas em processos do usuário, ignorando os processos do sistema operacional. Este método entrou em declínio de uso após o advento dos contadores especiais on-chip, por este ser menos invasivo e mais preciso.

## Instrumentação microprogramada

Uma forma de conciliar os métodos vistos até agora é a utilização da microprogramação de instruções no conjunto de instruções do sistema. Assim, tais instruções de medição podem ser executadas periodicamente pelo processador para retornar os dados de medição disponibilizados pela CPU em uma parte reservada da memória, apresentando assim traços do método por hardware (através de interrupções) e por software (usando as instruções). Este método, porém, é muito invasivo, podendo desacelerar a CPU em até 10 vezes, excluindo o tempo de operações de entrada e saída, e fazendo-se necessária a adição das microinstruções no hardware, o que pode não ser trivial.

Além disso, uma ferramenta de benchmarking pode ser categorizada, em sua essência, como sintética ou aplicada.

## Benchmarking sintético

Programa usado para medição de desempenho de um sistema ou componente de sistema particulares. Chama-se "sintético" porque a carga de trabalho realizada pelo programa é projetada para testar algo específico do sistema. Um exemplo é o benchmark Whetstone, que é composto de vários loops com aritmética de ponto flutuante, para testar a capacidade de um processador de lidar com tal aritmética de forma eficiente. Um fato curioso sobre esse tipo de benchmark é que em algumas linguagens compiladas, tais como C/C++, partes dos códigos de ferramentas dessa categoria podem ser vistas como "código morto" pelo compilador, sendo , por padrão, retiradas em tempo de compilação para melhorar a eficiência de execução; dessa forma, a ferramenta acaba não sendo fielmente executada e a qualidade da medição realizada acaba sendo altamente não-confiável.

## Benchmarking aplicado

O problema do benchmark sintético é que ele é ideal, ou seja, ele não condiz com a complexidade das cargas de trabalho de aplicações do mundo real. Em contrapartida, benchmarks aplicados são programas com cargas de trabalhos mais realistas, que poderiam surgir em uma aplicação real. Um dos melhores exemplos é o famoso Linpack, um pacote de resolução de sistemas lineares programado em FORTRAN, utilizado como um dos benchmarks das máquinas do TOP500.

