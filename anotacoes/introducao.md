## Resumo

O presente trabalho visa o estudo e experimentação do uso de ferramentas de síntese de alto nível para o design de circuitos. O intuito é destacar tecnologias emergentes de hardware, como as FPGAs, assim como aproximar engenheiros de software do desenvolvimento de hardware.

Para tanto, foi usado o LegUp, um arcabouço de código aberto para síntese de alto nível em FPGAs. Logo, o estudo do funcionamento interno e uso dessa ferramenta foi primordial para a elaboração do projeto. Com ele, algoritmos foram desenvolvidos na linguagem de programação C para processamento em software e em hardware e, dessa forma, efetuar-se a avaliação de desempenho nos dois tipos de processamento.

Como efeito secundário do presente trabalho, foi criada uma referência em português para o estudo e uso de FPGAs e síntese de alto nível usando o sistema operacional Ubuntu, placa SoC Cyclone V FPGA, da Altera, e o arcabouço LegUp High-Level Synthesis.

## Introdução


O desenvolvimento e pesquisa em hardware sofrem atualmente com um déficit de profissionais em relação aos de software. O número de engenheiros de software ultrapassa o de engenheiros de hardware numa proporção de quase 10 pra 1. Uma maneira de contornar tal situação é aproximar seus trabalhos, usando linguagens de programação de alto nível para criar o design de um hardware.