## Resumo (elaborar melhor)

O presente trabalho visa o estudo e experimentação do uso de ferramentas de síntese de alto nível para o design de circuitos. O intuito é destacar tecnologias emergentes de hardware, como as FPGAs, assim como aproximar engenheiros de software do desenvolvimento de hardware.

Para tanto, foi usado o LegUp, um arcabouço de código aberto para síntese de alto nível em FPGAs. Logo, o estudo do funcionamento interno e uso dessa ferramenta foi primordial para a elaboração do projeto. Com ele, algoritmos foram desenvolvidos na linguagem de programação C para processamento em software e em hardware e, dessa forma, efetuar-se a avaliação de desempenho nos dois tipos de processamento.

Como efeito secundário, foi criada uma referência em português para o estudo e uso de FPGAs e síntese de alto nível usando o sistema operacional Ubuntu, a placa SoC FPGA Cyclone V, da Altera, e o arcabouço LegUp High-Level Synthesis.

## Introdução (terminar e elaborar melhor)

O desenvolvimento e pesquisa em hardware sofrem atualmente com um déficit de profissionais em relação aos de software. O número de engenheiros de software ultrapassa o de engenheiros de hardware numa proporção de quase 10 pra 1 [colocar ref]. [colocar mais coisas aqui]

Apenas o uso de ferramentas de síntese de alto nível, por si só, não é um atrativo suficiente para despertar interesse no desenvolvimento de hardware pelos engenheiros de software. Ainda há o empecilho de se implementar o design do hardware, o que pode ser custoso e demorado. Atualmente, fabricar uma única peça de hardware customizado pode custar na ordem de milhares de reais, bem como demorar meses entre o pedido e a entrega no Brasil [colocar ref]. Não só o custo e o tempo são chaves nesse processo, como também a reusabilidade: cada circuito ainda pode apresentar defeitos de fabricação que inviabilizam seu uso, acarretando em um novo pedido, com mais dinheiro e tempo consumidos.