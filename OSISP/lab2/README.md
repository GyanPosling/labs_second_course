# Lab 2

## Сборка

```sh
make
```

## Запуск

Из каталога `lab2`:

```sh
export CHILD_PATH="$(pwd)/build"
./build/parent
```

Если `CHILD_PATH` не задан, программа ищет `child` в текущем каталоге.
Файл окружения по умолчанию: `env.txt`. При необходимости можно переопределить путь:

```sh
export ENV_PATH=/путь/к/env.txt
```
