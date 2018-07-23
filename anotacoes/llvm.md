Referência: http://www.aosabook.org/en/llvm.html

Nome do livro: The Architecture of Open-Source Applications

autor do capítulo: Chris Lattner

# LLVM

LLVM (antigo acrônimo para "Low-level virtual machine") é um projeto de código aberto que dispobiliza ferramentas de compilação e otimização para diversas linguagens. Tais ferramentas conseguem compilar códigos de diferentes linguagens e otimizá-los em tempo de compilação, provido de um *front-end* e um *back-end* do usuário. Por *front-end* entende-se um *parser* e um *lexer* da linguagem de programação a qual se deseja compilar, enquanto que por *back-end* entende-se uma lógica de transformação do código próprio da LLVM em código de máquina. Um exemplo de uma ferramenta famosa pertencente ao projeto LLVM é o [Clang](http://clang.llvm.org/), um compilador de C/C++/Objective-C alternativo ao GCC, que pode [apresentar perfomances superiores a este](http://clang.llvm.org/features.html#performance).

Nesta seção, falaremos sobre o projeto de forma direcionada ao entendimento do LegUp.

## Estrutura da LLVM

![Estrutura de três fases de um compilador](http://www.aosabook.org/images/llvm/SimpleCompiler.png)

A arquitetura mais utilizada na construção de um compilador é a chamada *arquitetura trifásica*, apresentando um *front-end*, um otimizador de código, e um *back-end*, como mostra a figura acima. O *front-end* é responsável pela transformação do arquivo de entrada em algum tipo de representação que permita sua leitura e otimização como, por exemplo, os *bytecodes* da linguagem Java. O otimizador recebe uma representação de um programa e realiza otimizações no código, que podem diminuir seu tempo de execução e/ou reduzir a quantidade de memória utilizada em sua execução. Por fim, o *back-end* converte o código otimizado na representação final desejada (também chamada de "*target*" ou "alvo"), que pode consistir em diversas representações, tais como um arquivo de texto simples que descreve o programa, ou um arquivo binário compatível com processadores da arquitetura x86. A LLVM também adota esse tipo de arquitetura, como visto na figura abaixo.

![Estrutura trifásica da LLVM](https://github.com/JoaoHL/tcc/blob/master/imgs/llvm-implementation-big.PNG?raw=true)

A principal vantagem de se adotar esse tipo de estrutura é a modularização do sistema, resultando na possibilidade de se reutilizar partes do sistema para novas aplicações. Por exemplo: se existir uma aplicação cujo *front-end* recebe um código em Python, com um otimizador do código gerado pelo *front-end*, e um *back-end* que gera o código equivalente em Java, e houvesse a necessidade de mudar o alvo de Java para Haskell, não seria necessário reescrever todo o sistema apenas para mudar o *back-end*: bastaria mudar apenas a geração do código em Haskell, sem precisar repensar o resto do código.

A LLVM, além de adotar essa arquitetura, também apresenta uma forte modularização em seu código, através da orientação a objetos da linguagem C++. Isso porque aplicações como o GCC, ainda que sigam a arquitetura trifásica, possuem módulos altamente acoplados, tal que o desenvolvimento do *back-end* necessita do conhecimento do *front-end* e vice-versa. Esses tipos de aplicações são chamadas de *monolíticas*, ou seja, aplicações que na prática, são muito acoplados, com dependências difíceis de serem desfeitas sem alterar partes críticas do sistema.

## Representação intermediária da LLVM

As implementações e detalhes de ambos *front-end* e *back-end* dependem muito da aplicação para qual a LLVM está sendo usada. O *front-end* pode consistir de um *parser* e *lexer* de uma linguagem totalmente nova, cuja sintaxe siga um padrão bem diferente das linguagens já existentes, ou até um novo paradigma. O *back-end*, por sua vez, pode transformar o código em instruções, em [Scratch](https://scratch.mit.edu/about), destinadas a robôs feitos de peças Lego. Como as possibilidades são muitas, o projeto adotou um tipo de representação de código utilizado em sua arquitetura, a chamada *representação intermediária da LLVM*, mais conhecida como *LLVM IR* ("LLVM intermediate representation"). Esta é enviada do *front-end* ao otimizador, onde é modificada de acordo com as regras descritas pelos desenvolvedores da aplicação e, depois, encaminhada para o *back-end* construir a saída apropriada para o alvo da aplicação. Um exemplo da LLVM IR pode ser visto abaixo.

```
define i32 @add1(i32 %a, i32 %b) {
entry:
  %tmp1 = add i32 %a, %b
  ret i32 %tmp1
}
```

O código acima é a *representação textual* da LLVM IR, uma vez que ela também pode ser serializada em *bitcode*, isto é, código binário. O código define uma função chamada ```add1```, que recebe dois inteiros ```a``` e ```b``` e retorna a soma deles. Como é possível perceber para quem já estudou ou viu códigos de alguma linguagem de montagem, a LLVM IR se assemelha a esse tipo de linguagem, de uma arquitetura RISC. O equivalente da função, em C, seria:

```
unsigned int add1(unsigned int a, unsigned int b) {
	unsigned int tmp1 = a + b;
	return tmp1;
}
```

O uso dessa representação intermediária facilita o desenvolvimento de uma aplicação ao padronizar a saída do *front-end* e a entrada do *back-end*, bem como essas partes do otimizador. Assim, ao criar um novo *front-end* para a LLVM, por exemplo, um programador deve saber apenas as características da entrada e da LLVM IR. Como o otimizador e o *back-end* utilizam a LLVM IR de forma independente, não é necessário saber sobre eles para a execução de seu trabalho.

## LLVM Pass Framework

No meio do processo de compilação, considerando a arquitetura trifásica, encontra-se o otimizador do código. Ele é responsável por realizar modificações que melhorem, por exemplo, o tempo de execução do programa e o uso de espaço de memória do computador. No caso da LLVM, o otimizador recebe um código descrito pela LLVM IR e altera as instruções ao reconhecer determinados padrões. Por exemplo, se houver uma instrução onde atribuimos a uma variável a subtração de um número inteiro por ele mesmo:
```
...
%tmp1 = sub i32 %a, %a
...
```

Podemos simplesmentre atribuir ```0``` à variável:
```
%tmp1 = i32  0
```

Ou seja, reconhecendo um padrão na instrução (e.g. subtração de um inteiro por ele mesmo), podemos substituí-la por outro mais eficiente (e.g. atribuir ```0``` à variável).

O mecanismo empregado na LLVM para realizar essas otimizações são os chamados *passes*, do arcabouço *LLVM Pass Framework*, pertencente ao projeto. Em termos práticos, os passes são etapas, possivelmente independentes entre si, pelas quais o código (ou parte dele) passa por uma análise e possível alteração, ocorrendo aí a otimização; em termos técnicos, os passes são classes derivadas da superclasse ```Pass``` direta ou indiretamente, que indicam o escopo mínimo pelo qual o passe é responsável (e.g. escopo global, de função, de bloco básico, de *loop*) que sobrescrevem métodos abstratos usados pelo arcabouço para realizar as otimizações. Cada passe é, assim, responsável por identificar padrões de instrução dentro do seu escopo e otimizar o padrão observado. A alteração retratada acima, onde temos a subtração de um inteiro por ele mesmo trocada pela atribuição da variável pelo valor ```0```, poderia ser colocada dentro de um passe junto de outras otimizações em cima de aritmética de inteiros como, por exemplo, transformar ```x - 0``` em ```x```.