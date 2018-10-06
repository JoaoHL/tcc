## Resumo (elaborar melhor)

O presente trabalho visa o estudo e experimentação do uso de ferramentas de síntese de alto nível para o design de circuitos. O intuito é destacar tecnologias emergentes de hardware, como as FPGAs, assim como aproximar engenheiros de software do desenvolvimento de hardware.

Para tanto, foi usado o LegUp, um arcabouço de código aberto para síntese de alto nível em FPGAs. Logo, o estudo do funcionamento interno e uso dessa ferramenta foi primordial para a elaboração do projeto. Com ele, algoritmos foram desenvolvidos na linguagem de programação C para processamento em software e em hardware e, dessa forma, efetuar-se a avaliação de desempenho nos dois tipos de processamento.

Como efeito secundário, foi criada uma referência em português para o estudo e uso de FPGAs e síntese de alto nível usando o sistema operacional Ubuntu, a placa SoC FPGA Cyclone V, da Altera, e o arcabouço LegUp High-Level Synthesis.

## Introdução (terminar e elaborar melhor)

A pesquisa e desenvolvimento em hardware sofrem atualmente com um déficit de profissionais em relação aos de software. O número de engenheiros de software ultrapassa o de engenheiros de hardware numa proporção que pode chegar a 10 pra 1 em alguns países [colocar ref]. Causas possíveis para tal situação são o hardware usado atualmente, muito mais potente do que o usado a uma ou duas décadas atrás, o que pode trazer a falsa sensação de dispensabilidade quanto ao desenvolvimento de hardware; e a alta demanda de desenvolvedores de software para a criação e manutenção de serviços de software (conhecido como 'SaaS', ou 'Software as a Service').

Um grande empecilho no *design* de *hardware* é a quantidade de recursos para a fabricação de uma única peça de hardware customizado. Esses recursos incluem custos na ordem de milhares de reais, bem como a demora meses entre o pedido e a entrega no Brasil [colocar ref]. Não só o custo e o tempo são chaves nesse processo, como também a reusabilidade deve ser considerada: cada circuito ainda pode apresentar defeitos de fabricação que inviabilizam seu uso, acarretando em um novo pedido, levando ao gasto de ainda mais recursos e tempo.


##COLOCAR NA CONCLUSÃO:
Apesar da existência de ferramentas de síntese de alto nível tentar cobrir essa lacuna entre as duas áreas, a sua mera existência não é um atrativo suficiente para despertar interesse no desenvolvimento de hardware por parte de engenheiros de software. Faz-se necessária uma base de conhecimento sobre o processo realizado por essas ferramentas, para permitir otimizações no algoritmo e no hardware gerado. 
