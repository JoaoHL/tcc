## Resumo (elaborar melhor)

O presente trabalho visa o estudo e experimentação do uso de ferramentas de síntese de alto nível para o design de circuitos. O intuito é destacar tecnologias emergentes de hardware, como as FPGAs, assim como aproximar engenheiros de software do desenvolvimento de hardware.

Para tanto, foi usado o LegUp, um arcabouço de código aberto para síntese de alto nível em FPGAs. Logo, o estudo do funcionamento interno e uso dessa ferramenta foi primordial para a elaboração do projeto. Com ele, algoritmos foram desenvolvidos na linguagem de programação C para processamento em software e em hardware e, dessa forma, efetuar-se a avaliação de desempenho nos dois tipos de processamento.

Como efeito secundário, foi criada uma referência em português para o estudo e uso de FPGAs e síntese de alto nível usando o sistema operacional Ubuntu, a placa SoC FPGA Cyclone V, da Altera, e o arcabouço LegUp High-Level Synthesis.

## Introdução (terminar e elaborar melhor)

# tópicos (nessa ordem)

 1 - breve história da computação, com foco no desenvolvimento de hardware e citar lei de Moore

 2 - Falar sobre a procura de formas de melhorar o desempenho de processamento de dados (multicore, GPUs, **FPGA** como hardware dedicado a certas tarefas)

 3 - falar sobre a situação atual do desenvolvimento de hardware, problemas do método de desenvolvimento atual, citar FPGA como solução de alguns desses problemas e citar o problema de incluir engenheiros de software no dev de hardware

 4 - introdução à HLS como solução pra integrar o dev de algoritmos em hardware, falar o que é e citar um pouco do processo, desde uma linguagem tipo C até um verilog/VHDL da vida

 5 - citar o LegUp, motivos de se ter escolhido ele como ferramenta etc

 A melhoria do desempenho dos computadores sempre foi uma constante na história da Computação. Das válvulas à vácuo até os nanotransístores, por muito tempo o desenvolvimento de *hardware* foi regido pela famosa Lei de Moore, dizendo que a cada 18 meses a quantidade de transístores em um *chip* de silício dobraria e, por consequência, seu desempenho. Atualmente, tal lei chega aos limites da Física Moderna, onde um nanotransístor de 1 nanômetro de comprimento já foi inventado [(ref)](http://science.sciencemag.org/content/354/6308/99). Novas técnicas estão sendo estudadas e aplicadas na melhoria da fabricação de *chip*s, como a manipulação de novos tipos de partículas físicas [(ref)](https://www.nature.com/articles/nnano.2017.178) e de propriedades quânticas de partículas já existentes, como o *spin* [(ref)](https://arxiv.org/abs/1212.3362), mas a observação feita por Gordon E. Moore está atingindo seus limites.

Para impulsionar o desempenho computacional sem envolver diretamente a quantidade de transístores em um *chip* ou as propriedades das partículas envolvidas na fabricação, novas metodologias computacionais foram adotadas. Por exemplo, a paralelização do processamento de dados a partir do trabalho conjunto entre *hardwares* dedicados e de propósito geral tem sido amplamente empregada em aplicações que demandam baixa latência de resposta, como processamento gráfico [(ref)](https://link.springer.com/chapter/10.1007/3-540-63508-4_107) e gerenciamento de memória [(ref)](https://patents.google.com/patent/US9652230). Um bom exemplo desses *hardwares* dedicados é a *GPU* (*Graphics Processing Unit*), criada com o intuito de paralelizar o processamento gráfico de computadores de uso geral a fim de acelerar a visualização das interfaces gráficas destes.

Apesar do desempenho adquirido no uso de *hardwares* dedicados, é necessário um grande esforço para inventar ou otimizar dispositivos, 







Apenas o uso de ferramentas de síntese de alto nível, por si só, não é um atrativo suficiente para despertar interesse no desenvolvimento de hardware pelos engenheiros de software. Ainda há o empecilho de se implementar o design do hardware, o que pode ser custoso e demorado. Atualmente, fabricar uma única peça de hardware customizado pode custar na ordem de milhares de reais, bem como demorar meses entre o pedido e a entrega no Brasil [colocar ref]. Não só o custo e o tempo são chaves nesse processo, como também a reusabilidade: cada circuito ainda pode apresentar defeitos de fabricação que inviabilizam seu uso, acarretando em um novo pedido, com mais dinheiro e tempo consumidos.