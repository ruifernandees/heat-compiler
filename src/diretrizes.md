## Organizacao
- Separar os tipos de lexemas da BNF, deixar organizados em blocos separados

        Palavras reservadas
            - if
            - then
            - else
            ...
    
        Operadores
            - ==
            - >
            - <
            ...

- Retornar uma lista de tokens <(palavra, tipo)> junto com os erros, caso haja. 
- O delimitador de linha da nossa linguagem deve ser o `\n`
- Destacar o delimitador de atribuicao `=`
- Reconhecedores de numeros e idenfiticadores
    - Exemplo de erro no reconhecimento de numero - 100a (nao pode ser numero por causa do a, nao pode ser identificador porque comeca com digito)
    - Separar o primeiro digito do resto?
- 