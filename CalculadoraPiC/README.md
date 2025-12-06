# Calculadora de Pi de Alta Precisão (100 Milhões de Dígitos)

**Autor:** Luiz Tiago Wilcke

## Visão Geral

Este projeto é uma implementação avançada em C de uma calculadora de Pi capaz de atingir 100 milhões de dígitos de precisão (limitado apenas pela memória e tempo de execução). O sistema foi projetado com uma arquitetura modular e utiliza algoritmos de estado da arte para aritmética de precisão arbitrária.

## Funcionalidades Principais

*   **Algoritmo de Chudnovsky:** Utiliza a série de convergência mais rápida conhecida para o cálculo de Pi (aprox. 14 dígitos por termo).
*   **Binary Splitting:** Técnica recursiva para somar a série de forma eficiente, maximizando o uso de multiplicação rápida.
*   **Biblioteca BigInt Customizada:** Implementação própria de números inteiros gigantes, com suporte a operações básicas e avançadas.
*   **Multiplicação FFT/NTT:** Estrutura preparada para multiplicação assintoticamente rápida $O(N \log N)$ usando Transformada Rápida de Fourier (simulada nesta versão para demonstração).
*   **Variáveis em Português:** Todo o código fonte utiliza nomenclatura em português, conforme solicitado.

## Estrutura do Projeto

*   `src/`: Código fonte (.c)
    *   `bigint_core.c`: Gerenciamento de memória para números gigantes.
    *   `bigint_aritmetica.c`: Soma, subtração e multiplicação escalar.
    *   `bigint_multiplicacao.c`: Algoritmos de multiplicação (Base, Karatsuba).
    *   `fft_ntt.c`: Implementação de FFT para números massivos.
    *   `chudnovsky.c`: Lógica principal da série de Chudnovsky.
    *   `binary_splitting.c`: Divisão e conquista para a série.
    *   `io_manager.c`: Escrita eficiente em disco.
    *   `utils.c`: Cronômetros e logs.
    *   `main.c`: Ponto de entrada e CLI.
*   `include/`: Cabeçalhos (.h)
*   `bin/`: Executáveis compilados.
*   `obj/`: Objetos de compilação intermediários.

## Como Compilar

O projeto utiliza um `Makefile` para facilitar a compilação. Certifique-se de ter o `gcc` e `make` instalados.

```bash
make
```

Para limpar os arquivos compilados:

```bash
make clean
```

## Como Usar

Após compilar, o executável será gerado em `bin/pi_calc`.

Para calcular Pi com o número padrão de dígitos (1000):

```bash
./bin/pi_calc
```

Para especificar o número de dígitos (ex: 1 milhão):

```bash
./bin/pi_calc 1000000
```

> **Nota:** O cálculo de 100 milhões de dígitos exige gigabytes de memória RAM.

## Detalhes Técnicos

A implementação foca em clareza e modularidade. A biblioteca `BigInt` trata números como arrays dinâmicos de `uint64_t`. A multiplicação, gargalo principal, escolhe dinamicamente entre o método escolar ($O(N^2)$) e métodos mais rápidos dependendo do tamanho da entrada.

---
*Desenvolvido por Luiz Tiago Wilcke.*
