# 🛣️ Estrada de Wakanda

## 🎯 Contexto e Objetivo
Este projeto foi desenvolvido como atividade avaliativa para a disciplina de **Estruturas de Dados (ED)** da **Universidade Católica de Brasília (UCB)**, ministrada pelo Prof. Marcelo Eustáquio.

O objetivo do algoritmo é auxiliar o Rei T'Challa a calcular os custos de manutenção de uma nova estrada que cruza Wakanda da fronteira oeste à leste. O programa tem como função calcular a **menor vizinhança** de estrada — definida como os pontos mais próximos do centro de uma cidade do que de qualquer outra — entre as cidades pelas quais a estrada passa, além de identificar qual cidade possui essa menor vizinhança.

## 💻 Tecnologias Utilizadas
- **C** (Linguagem Padrão)
- GCC (Compilador)

## 🗂️ Estrutura do Projeto
O código foi estruturado respeitando o Tipo Abstrato de Dados (TAD) fornecido nas instruções:

- `cidades.h`: Arquivo de cabeçalho imutável contendo a definição das estruturas de dados (`Cidade` e `Estrada`) e os protótipos das funções.
- `cidades.c`: Arquivo contendo a implementação da solução e das regras de negócio:
  - `getEstrada()`: Lê os dados do arquivo de texto de entrada, valida as restrições matemáticas e de fronteira ($3 \le T \le 10^6$ e $2 \le N \le 10^4$) e inicializa as estruturas em uma lista. Em caso de violação das regras, retorna `NULL`.
  - `calcularMenorVizinhanca()`: Processa as distâncias e retorna o valor numérico da menor vizinhança.
  - `cidadeMenorVizinhanca()`: Retorna o nome da cidade responsável pelo menor trecho de manutenção.
- `main.c`: Arquivo de testes automatizados para validar a correção das funções implementadas utilizando casos de teste (ex: `Teste01.txt`).

## 🚀 Como Executar

Para rodar o projeto localmente, certifique-se de ter um compilador compatível com C (como o GCC) instalado e siga os passos abaixo:

1. Clone este repositório:
    git clone https://github.com/SEU-USUARIO/estrada-wakanda.git

2. Acesse a pasta do projeto:
    cd estrada-wakanda

3. Compile os arquivos usando o GCC:
    gcc main.c cidades.c -o cidades.exe

4. Execute o programa gerado:
    ./cidades.exe

*Os resultados da execução e a contagem de acertos dos testes de validação serão gerados automaticamente dentro do arquivo `Resultado.txt`.*
