	'Benchmarking', na Computação, é o ato de medir o desempenho de um sistema, seja ele de 'hardware' ou de 'software'. Para tanto, faz-se o uso de monitoramento das execuções de testes em cima do sistema a ser avaliado, capturando dados tais como número de falhas de 'cache' e de más especulações de instruções. O 'benchmarking' de um sistema pode ser feito através de 4 metodologias: hardware on-chip, hardware off-chip, software e instrumentação microprogramada.

# Hardware on-chip
	Neste método, usamos os dados gravados pelo próprio processador, dados estes compostos principalmente de contadores de eventos. A captura de dados é feita através de instruções especiais, que atualmente são descritas pelos fabricantes dos processadores, em registradores de controle especiais . A principal vantagem é a baixa interferência da medição de eventos na taxa de processamento, mas apesar das possíveis centenas de dados capturados, cerca de apenas 2 a 10 medições podem ser feitas simultaneamente, devido à baixa disponibilidade desses registradores.

# Hardware off-chip
	Este método é parecido com o on-chip, mas utiliza hardware exterior à CPU. Dessa forma, a capacidade de armazenamento de medições aumenta de forma significativa; entretanto, a necessidade de disparar interrupções na CPU para reter os dados torna-o mais invasivo, diminuindo o uso da CPU próprio para processamento.

# Benchmarking por software
	O uso de software para realizar o benchmarking de um sistema apresenta a grande vantagem de ser mais fácil de ser realizado do que os por hardware. No entanto, também é o método mais invasivo, além de comumente realizar-se medições apenas em processos do usuário, ignorando os processos do sistema operacional. Este método entrou em declínio de uso após o advento dos contadores especiais on-chip, por este ser menos invasivo e mais preciso.

# Instrumentação microprogramada
	Uma forma de conciliar os métodos vistos até agora é a utilização da microprogramação de instruções no conjunto de instruções do sistema. Assim, tais instruções de medição podem ser executadas periodicamente pelo processador para retornar os dados de medição disponibilizados pela CPU em uma parte reservada da memória, apresentando assim traços do método por hardware (através de interrupções) e por software (usando as instruções). Este método, porém, é muito invasivo, podendo desacelerar a CPU em até 10 vezes, excluindo o tempo de operações de entrada e saída, e fazendo-se necessária a adição das microinstruções no hardware, o que pode não ser trivial.

	Além disso, uma ferramenta de benchmarking pode ser categorizada, em sua essência, como sintética ou aplicada.

# Benchmarking sintético
	Programa usado para medição de desempenho de um sistema ou componente de sistema particulares. Chama-se "sintético" porque a carga de trabalho realizada pelo programa é projetada para testar algo específico do sistema. Um exemplo é o benchmark Whetstone, que é composto de vários loops com aritmética de ponto flutuante, para testar a capacidade de um processador de lidar com tal aritmética de forma eficiente. Um fato curioso sobre esse tipo de benchmark é que em algumas linguagens compiladas, tais como C/C++, partes dos códigos de ferramentas dessa categoria podem ser vistas como "código morto" pelo compilador, sendo , por padrão, retiradas em tempo de compilação para melhorar a eficiência de execução; dessa forma, a ferramenta acaba não sendo fielmente executada e a qualidade da medição realizada acaba sendo altamente não-confiável.

# Benchmarking aplicado
	O problema do benchmark sintético é que ele é ideal, ou seja, ele não condiz com a complexidade das cargas de trabalho de aplicações do mundo real. Em contrapartida, benchmarks aplicados são programas com cargas de trabalhos mais realistas, que poderiam surgir em uma aplicação real. Um dos melhores exemplos é o famoso Linpack, um pacote de resolução de sistemas lineares programado em FORTRAN, utilizado como um dos benchmarks das máquinas do TOP500.

