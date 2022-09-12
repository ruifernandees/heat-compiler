
![Heat logo](https://drive.google.com/uc?export=view&id=1jSdALYdBNKCD7v58Agq7vudpq1CDBK_K)

## 🔥 Descrição
Heat é um compilador para a linguagem Ruby, feito em C++, como projeto da disciplina de Compiladores da Professora Roberta Lopes e desenvolvido por:
- Hélder Lima
- Jonathan Yuri
- Rui Fernandes
- Vinícius Maia

## 🚀 Como rodar
A execução pode ser feita de duas formas.
### Manualmente
```sh
# Limpar cache
make clean

# Compilar
make main

# Executar
./dist/main.out ./src/mocks/hello-world.rb
```


### Via Shell Script
```sh
./compile.sh
./run.sh ./src/mocks/hello-world.rb
```

## 🧪 Testes automatizados
O projeto possui testes automatizados, que podem ser rodados de duas formas.
### Manualmente
```sh
make clean
make test
./dist/test.out
```

### Via Shell Script
```sh
./test.sh
```