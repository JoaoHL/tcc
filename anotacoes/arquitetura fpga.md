# Introdução

*FPGA*s (do inglês *Field programmable gate array*) são dispositivos de silício que podem ser programados após sua fabricação, permitindo que quase qualquer *design* de circuito digital possa ser implementado nele. Essa maleabilidade de implementação torna-os atrativos para tarefas que envolvam a produção e alteração de *designs* de circuitos lógicos, pois o custo e tempo de execução dessas atividades são muito reduzidos em comparação ao tradicional ciclo de desenvolvimento com o uso de dispositivos *ASIC*s (do inglês *Application-specific integrated circuit*). Como consequência, *FPGA*s permitem que o *design* seja concluído em um menor tempo para poder ser lançado no mercado (o dito *time to market*).


# Programabilidade de uma FPGA

A flexibilidade do *FPGA* se deve à sua capacidade de ser reprogramada após sua fabricação. Para tal, há o uso de *switch*s programáveis em suas rotas de interconexão, isto é, podemos conectar ou desconectar as rotas de comunicação da forma que quiseremos. Assim, usam-se certas tecnologias de programação de circuitos que guardam os estados desses *switch*s. Este fato é o que faz com que cerca de 90% da área útil do *FPGA* seja destinado apenas para a implementação das rotas de intercomunicação do circuito.

É preciso algum tipo de tecnologia para poder reprogramar tais rotas de comunicação, mais precisamente, memórias, e de preferências as que sejam não-voláteis, infinitamente reprogramáveis, baratas e que consumam pouca energia. Atualmente, os três métodos mais utilizados são as tecnologias de *SRAM*, de memórias *flash* e de fusíveis, todas com suas vantagens e desvantagens.

## SRAM

A *SRAM* ('Static Random Access Memory', ou 'memória estáticas de acesso aleatório') são um tipo de memória volátil que utiliza uma combinação de 6 transistores para guardar um *bit* de informação. O termo 'estático' refere-se à falta de necessidade de *refresh*s em seu circuito. Note que isso não significa que, na ausência de corrente elétrica, o estado se manterá: caso haja uma queda de energia, a memória perderá o dado nela contido.

Devido à sua característica estática, as *SRAM*s são mais rápidas e consomem menos energia que as *DRAM*s. Entretanto, como as *SRAM*s necessitam de 6 transistores e muito mais espaço que as *DRAM*s, que utilizam apenas 1 transistor e 1 capacitor, aquelas são muito mais caras e demandam mais espaço no circuito para serem implementadas, além de ambas serem voláteis.

## Memórias *flash*

As memórias *flash* ou baseadas em EEPROMs ('Electrally Erasable-Programmable Read-Only Memory', ou 'memória exclusiva para leitura eletricamente programável e apagável') são memórias não-voláteis que podem ser reconfiguradas através do uso de luz ultravioleta e descargas elétricas. Além de não-voláteis, também são estáticas e portanto consomem pouca energia, enquanto também necessitam de menos área de implementação que as *SRAM*s; no entanto, são mais caras e só podem ser programadas um número finito de vezes antes de pararem de funcionar adequadamente. 

## Memória baseada em fusíveis

É o tipo de memória com menor área de implementação dentre as citadas. Essa tecnologia utiliza fusíveis como *switches*: uma vez queimados, eles implementarão as rotas desejadas no FPGA, o que explica sua natureza não-volátil e sua rapidez. Porém o uso de fusíveis tem desvantagens notáveis, como a programabilidade única da placa.

Dentre as tecnologias de programação citadas, todas possuem suas vantagens e desvantagens. O uso mais comum, atualmente, é de FPGAs que utilizam SRAMs para sua programabilidade, pois além de todas as vantagens citadas e apesar das desvantagens, as SRAMs seguem o padrão *CMOS* ('Complementary Metal-oxyde semiconductor', ou 'semicondutor de metal-óxido complementar') de processo de fabricação de circuitos, o que barateia sua produção e sua predominancia no mercado de semicondutores.


# Componentes de um *FPGA*

Os *FPGA*s são compostos, basicamente, por:

- Blocos lógicos
- Rotas de interconexão
- Blocos de E/S (entrada e saída)

Os blocos lógicos são configuráveis e implementam funções lógicas e armazenamento de dados (i.e. memória). Os blocos de E/S recebem e enviam dados para fora do *chip*. Por fim, as rotas de interconexão conectam os blocos lógicos entre si e entre os blocos de E/S. Uma forma de visualizar esses componentes é através de uma matriz, onde os blocos lógicos estão dispostos bidimensionalmente, numa grade, e conectados pelas rotas de interconexão. Nas bordas dessa matriz se encontram os blocos de E/S, integrados à matriz pelas rotas de interconexão, servindo para a comunicação do *FPGA* com dispositivos exteriores a ele.


## Blocos lógicos de um FPGA

Os blocos lógicos configuráveis (BLCs) são as unidades que provêem capacidade lógica e de armazenamento para o FPGA. BLCs podem ser implementados de diversas maneiras, desde simples transistores até processadores inteiros, e essa implementação define sua granularidade. BLCs com granularidade muito pequena, como transistores, acabam se utilizando de espaço demais e torna os ineficientes. Por outro lado, os de granularidade muito grande, como processadores, podem representar um desperdício de recurso quando tratamos de funções mais simples.
Entre esses máximos, temos um espectro de implementações de BLCs. 

Os BLCs são compostos blocos lógicos básicos (BLBs), que podem ser usados em conjunto ou de forma isolada para formar um BLC (isto é, um BLC pode ser composto de um único BLB ou de um conjunto deles). As componentes usadas nesses BLBs podem variar, mas a fabricante da placa que será usada neste trabalho, a Altera (fabricante da SoC FPGA Cyclone V) utiliza *lookup tables* e *flip-flops* para armazenamento. *Lookup tables* (LUTs) são unidades parecidas com multiplexadores, onde temos uma entrada de *k* bits e um código de configuração de *2^k* bits, formando uma LUT chamada k-LUT. A depender do código de configuração usado, a entrada de *k* bits retorna uma possível saída também de *k* bits, ou seja, uma k-LUT pode retornar qualquer valor de uma determinada função booleana f tal que ```f: {0, 1}^k => {0, 1}^k```. A vantagem do uso de LUTs reside em não ter uma granularidade nem muito pequena, nem muito grande, permitindo o uso em conjunto para implementações mais complexas.

Apesar do uso de LUTs ou outros métodos para implementar BLBs, como NANDs, esses métodos são mais usados para criar a parte programável do FPGA. Uma parte dele pode vir já programada com blocos lógicos especializados, como processadores de sinais digitais (conhecidos como DSPs, ou *digital signals processor*), multiplicadores, somadores, ALUs inteiras, todos criados de forma otimizada para suas tarefas. Estes são chamados de blocos rígidos, pois não podem ser reprogramados, apenas usados como estão no FPGA. Isso implica em um possível desperdício de espaço e recursos no caso desses blocos não serem utilizados pelo circuito, mas também traz a vantagem de se usar blocos feitos especialmente para determinadas tarefas.

## Rede de interconexão

Como dito anteriormente, a flexibilidade de um FPGA vem da capacidade de ter sua rede de interconexão reprogramada. Essa rede precisa ser flexível não só em termos de configuração de rotas, mas também de tipos de fios presentes no dispositivo para poder implementar uma grande variedade de circuitos. Apesar da maior parte das componentes de um circuito apresentar localidade (isto é, se localizarem perto umas das outras), há conexões que podem necessitar de fios mais longos.
Cerca de 85% da área de um FPGA consiste da rede de interconexão entre os blocos lógicos. Visando otimizar a comunicação de acordo com a finalidade do circuito, essa rede pode ser construída usando arquiteturas diferentes. Duas destas são notáveis: a baseada em malha e a hierárquica.

### Redes baseadas em malha

As redes baseadas em malha (do inglês '*mesh-based*', também conhecida como '*island-style*' ou '*estilo de ilha*') são organizadas em formato matricial, com blocos lógicos (BLs) cercados de fios de conexão - daí o termo 'estilo de ilha', onde os BLs parece estar "ilhados" em um mar de fios. Nas extremidades se encontram os blocos de E/S, e na rede de conexão encontramos concentrações de *switches* que chamaremos de "caixas de *switches*", ou CSs. Soma-se a essas componentes as conexões entre os blocos lógicos e a rede de comunicação, que serão chamadas de caixas de comunicação, ou CCs.

# Desvantagens

A maior vantagem de *FPGA*s - sua flexibilidade - também é a causa de sua maior desvantagem. Tal característica das *FPGA*s baseia-se principalmente na reprogramação das rotas de intercomunicação entre os blocos lógicos e blocos de E/S. Entretanto, a área usada por tais rotas para ocupa a maior parte do dispositivo, chengando a quase 90% da área útil do dispositivo, para permitir a sua reprogramação. Além de maiores que os *ASIC*s, as *FPGA*s são mais lentas e consomem mais energia, também por conta da sua fabricação visando a flexibilidade de implementações.