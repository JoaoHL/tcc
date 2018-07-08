# Definição

Síntese de alto nível ('High level synthesis', ou HLS) é o processo de transformação linguagens de programação de alto nível para sintetizar arquiteturas RTL ('*Register-transfer level*' ou 'nível de registrador e transferência'), isto é, sintetizar arquiteturas de circuitos digitais síncronos a partir de descrições comportamentais (ou algorítmicas) do *hardware*. As saídas geradas são, em sua maioria, arquivos em linguagens HDL ('*Hardware description language*' ou linguagem de descrição de *hardware*), que são usadas para configurar o *hardware*. Tais ferramentas realizam o mesmo fluxo básico na sintetização dos circuitos, desde a especificação comportamental desejada até a geração dos arquivos em HDLs.

# Fluxo de síntese

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