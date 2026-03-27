# Lab 8

## Описание

Многопоточный TCP-сервер и клиент с учебным протоколом команд:

- `ECHO`
- `INFO`
- `LIST`
- `CD`
- `QUIT`
- `@file` (выполнение команд из файла)

## Сборка

```sh
make
make MODE=release
make clean
```

## Запуск

Сервер:

```sh
./build/debug/myserver <root_dir> <port>
```

Клиент:

```sh
./build/debug/myclient <host> [port]
```

Пример:

```sh
./build/debug/myserver ./testroot 23456
./build/debug/myclient 127.0.0.1 23456
```
