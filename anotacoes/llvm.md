# LLVM

LLVM (Acrônimo para "Low-level virtual machine") é um projeto de código aberto que dispobiliza ferramentas de compilação e otimização para diversas linguagens. Tais ferramentas conseguem compilar códigos de diferentes linguagens e otimizá-los em tempo de compilação, provido de um *front-end* e um *back-end* do usuário. Por *front-end* entende-se um *parser* e um *lexer* da linguagem de programação a qual se deseja compilar, enquanto que por *back-end* entende-se uma lógica de transformação do código próprio da LLVM em código de máquina. Um exemplo de uma ferramenta famosa pertencente ao projeto LLVM é o [Clang](http://clang.llvm.org/), um compilador de C/C++/Objective-C alternativo ao GCC, que pode apresentar perfomances superiores a este [adicionar ref].

Nesta seção, falaremos sobre o projeto de forma direcionada ao entendimento do LegUp.

## Estrutura da LLVM

![Estrutura de três fases de um compilador](http://www.aosabook.org/images/llvm/SimpleCompiler.png)

A estrutura da LLVM segue o padrão trifásico de construção de compiladores, apresentando um *front-end*, um otimizador de código, e um *back-end*