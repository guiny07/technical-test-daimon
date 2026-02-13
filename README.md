# technical-test-daimon
Projeto desenvolvido para o teste prático para o processo seletivo de estágio na Daimon Engenharia e Sistemas.

## Introdução do problema 

Sistemas de armazenamento de energia em baterias (em inglês, Battery Energy Storage Systems - BEES) surgem como solução para problemas de demanda de energia em sistemas eólicos ou fotovoltaicos, onde a energia excedente é armazenada para que em um instante de baixa geração e alta demanda esta energia armazenada seja despachada, suprindo a demanda que antes era baseada em usinas térmicas por exemplo. 

## O que foi solicitado

Dado o funcionamento de um BESS, o problema exigia que, a partir de uma tabela e uma figura que representam a curva de carga diária de um consumidor, fosse desenvolvido uma ferramenta para simular os efeitos do armazenamento de energia neste consumidor. 

De acordo com a problemática, foram solicitadas as seguintes atividades: 

1. Desenvolver um código em qualquer linguagem (C, C++, C# ou Java) que tenha uma classe chamada BESS, com os seguintes requisitos:
- Estrutura de dados para armazenar a curva do consumidor informada na tabela;
- Get com energia diária armazenada em kWh pelo BESS (soma dos instantes negativos em módulo da curva);
- Get com energial mensal armazenada em kWh pelo BESS (valor do item anterior multiplicado pelo número de dias do mês, considerar 30 dias);
- Set do intervalo inicial e final do despacho da bateria (não deve ser possível definir intervalo onde há geração);
- Método para criar uma estrutura de dados que faz a "descarga" da bateria nos instantes setados no item acima (a ideia é criar um método que distribuisse proporcionalmente a energia armazenada nos instantes onde há consumo de energia);
- Get dos pontos da curva resultante em um instante t passado como parâmetro. 

2. Transformar o código do item 1 em uma DLL e fazer a leitura dos métodos em um notebook ou script Python.

3. No notebook/script criado, deve ser possível analisar os impactos do BESS com a biblioteca:
- Definir e plotar a curva inicial em Python;
- Utilizar a DLL criada para realizar estudos no BESS;
- Setar a curva inicial no objeto criado;
- Informar ao usuário a potência armazenada diariamente e mensalmente pelo BESS;
- Setar o intervalo de despacho do objeto BESS entre os instantes das 17h às 05h (utilizando a energia armazenada para ser consumida a noite e na madrugada);
- Plotar a curva resultante deste consumidor com a BESS.

## O que foi desenvolvido

O projeto foi desenvolvido com as linguagens C++ e Python, sendo que C++ foi utilizado para a criação da classe BESS e dos métodos solicitados, uma vez que seu uso facilitaria a criação da DLL com CTypes. Por fim, o consumo da DLL e toda a análise de dados foi realizada em Python como solicitado no teste. 

### Detalhes da implementação 

A classe em C++ e a API para exportação ao Python se encontram no diretório build-DLL em bess-core. 
Utilização de uma biblioteca intermediária entre o código orientado à objetos em C++ (mais complexo) e a Ctypes do Python que só identifica C puro. Também é por meio dela que é realizada a captura das exceções lançadas em C++. 

No diretório bess_api em bess-python se encontram _bess_c.py, o qual define as assinaturas dos métodos a serem lidos pelo Python, e bess.py, que é uma classe "wrapper" para encapsular os métodos com assinaturas mais "baixo-nível", tornando a utilização da DLL mais intuitiva e simples (do ponto de vista do usuário é como se fosse uma simples classe Python). 

Por fim, o uso da DLL pode ser feita simplesmente fazendo a importação da classe BESS em algum script ou notebook Python. 

## Como compilar e executar

Dentro do diretório bess-core execute o comando abaixo para compilar a DLL em C++: 

```bash
g++ -fPIC -shared     BESS.cpp     build-DLL/bess_c_api.cpp     -I.     -Ibuild-DLL     -o build-DLL/libbess.so
```

Isso irá gerar o arquivo libbess.so em build-DLL/. 

Por fim, no diretório bess-python, certifique-se de que no diretório bess_api se encontram os arquivos __init__.py, _bess_c.py e bess.py. Daí é só importar em um arquivo .py ou notebook: 

```python
from bess import BESS
```
