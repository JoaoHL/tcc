# Introdução

*FPGA*s (do inglês *Field programmable gate array*) são dispositivos de silício que podem ser programados após sua fabricação, permitindo que quase qualquer *design* de circuito digital possa ser implementado nele. Essa maleabilidade de implementação torna-os atrativos para tarefas que envolvam a produção e alteração de *designs* de circuitos lógicos, pois o custo e tempo de execução dessas atividades são muito reduzidos em comparação ao tradicional ciclo de desenvolvimento com o uso de dispositivos *ASIC*s (do inglês *Application-specific integrated circuit*). Como consequência, *FPGA*s permitem que o *design* seja concluído em um menor tempo para poder ser lançado no mercado (o dito *time to market*).

# Componentes de um *FPGA*

Os *FPGA*s são compostos, basicamente, por:

- Blocos lógicos programáveis
- Rotas de interconexão programáveis
- Blocos de E/S (entrada e saída)

Os blocos lógicos são configuráveis e implementam funções lógicas e armazenamento de dados (i.e. memória). Os blocos de E/S recebem e enviam dados para fora do *chip*. Por fim, as rotas de interconexão também são configuráveis e conectam os blocos lógicos entre si e entre os blocos de E/S. Uma forma de visualizar esses componentes é através de uma matriz, onde os blocos lógicos estão dispostos bidimensionalmente, numa grade, e conectados pelas rotas de interconexão. Nas bordas dessa matriz se encontram os blocos de E/S, integrados à matriz pelas rotas de interconexão, servindo para a comunicação do *FPGA* com dispositivos exteriores a ele.

# Programabilidade de uma FPGA

A flexibilidade do *FPGA* se deve à sua capacidade de ser reprogramada após sua fabricação. Para tal, há o uso de *switch*s programáveis em suas rotas de interconexão, isto é, podemos conectar ou desconectar as rotas de comunicação da forma que quiseremos. Assim, usam-se certas tecnologias de programação de circuitos que guardam os estados desses *switch*s. Este fato é o que faz com que cerca de 90% da área útil do *FPGA* seja destinado apenas para a implementação das rotas de intercomunicação do circuito.

É preciso algum tipo de tecnologia para poder reprogramar tais rotas de comunicação, mais precisamente, memórias, e de preferências as que sejam não-voláteis, infinitamente reprogramáveis, baratas e que consumam pouca energia. Atualmente, os três métodos mais utilizados são as tecnologias de *SRAM*, de memórias *flash* e de fusíveis, todas com suas vantagens e desvantagens.

## SRAM

A *SRAM* ('Static Random Access Memory', ou 'memória estáticas de acesso aleatório') são um tipo de memória volátil que utiliza uma combinação de 6 transistores para guardar um *bit* de informação. O termo 'estático' refere-se à falta de necessidade de *refresh*s em seu circuito. Note que isso não significa que, na ausência de corrente elétrica, o estado se manterá: caso haja uma queda de energia, a memória perderá o dado nela contido.

Devido à sua característica estática, as *SRAM*s são mais rápidas e consomem menos energia que as *DRAM*s. Entretanto, como as *SRAM*s necessitam de 6 transistores e muito mais espaço que as *DRAM*s, que utilizam apenas 1 transistor e 1 capacitor, aquelas são muito mais caras e demandam mais espaço no circuito para serem implementadas, além de ambas serem voláteis.

## Memórias *flash*

As memórias *flash* ou baseadas em *EEPROM*s ('Electrally Erasable-Programmable Read-Only Memory', ou 'memória exclusiva para leitura eletricamente programável e apagável') são memórias não-voláteis que podem ser reconfiguradas através do uso de luz ultravioleta e descargas elétricas. Além de não-voláteis, também são estáticas e portanto consomem pouca energia, enquanto também necessitam de menos área de implementação que as *SRAM*s; no entanto, são mais caras e só podem ser programadas um número finito de vezes antes de pararem de funcionar adequadamente. 

## Memória baseada em fusíveis

É o tipo de memória com menor área de implementação dentre as citadas. Essa tecnologia utiliza fusíveis como *switch*s: uma vez queimados, eles implementarão as rotas desejadas no *FPGA*, o que explica sua natureza não-volátil e sua rapidez. Porém o uso de fusíveis tem desvantagens notáveis, como a programabilidade única da placa.

Dentre as tecnologias de programação citadas, todas possuem suas vantagens e desvantagens. O uso mais comum, atualmente, é de *FPGA*s que utilizam *SRAM*s para sua programabilidade, pois além de todas as vantagens citadas e apesar das desvantagens, as *SRAM*s seguem o padrão *CMOS* ('Complementary Metal-oxyde semiconductor', ou 'semicondutor de metal-óxido complementar') de processo de fabricação de circuitos, o que barateia sua produção e sua predominancia no mercado de semicondutores.

# Blocos lógicos de um *FPGA*



# Desvantagens

A maior vantagem de *FPGA*s - sua flexibilidade - também é a causa de sua maior desvantagem. Tal característica das *FPGA*s baseia-se principalmente na reprogramação das rotas de intercomunicação entre os blocos lógicos e blocos de E/S. Entretanto, a área usada por tais rotas para ocupa a maior parte do dispositivo, chengando a quase 90% da área útil do dispositivo, para permitir a sua reprogramação. Além de maiores que os *ASIC*s, as *FPGA*s são mais lentas e consomem mais energia, também por conta da sua fabricação visando a flexibilidade de implementações.