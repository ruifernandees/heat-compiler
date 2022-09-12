
![Heat logo](https://drive.google.com/uc?export=view&id=1jSdALYdBNKCD7v58Agq7vudpq1CDBK_K)

## 🔥 Descrição
Heat é um compilador para a linguagem Ruby, feito em C++, como projeto da disciplina de Compiladores da Professora Roberta Lopes e desenvolvido por:
- Hélder Lima
- Jonathan Yuri
- Rui Fernandes
- Vinícius Maia

## ⚙️ Autômato
Foi criado um diagrama próximo a um autômato finito determinístico, que pode ser acessado [clicando aqui.](https://drive.google.com/file/d/1EMTIUh7hOaKoeuM9uYVHJXXXKT9gV56Y/view?usp=sharing)

## 📜 BNF
A BNF da linguagem Ruby (modificada) utilizada pelo Heat pode ser acessada [clicando aqui.](https://docs.google.com/document/d/1Y4f-NTmy9mC73_5wLWOZwTmeYvXB-PxQUfYysfg6S0c/edit?usp=sharing)

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