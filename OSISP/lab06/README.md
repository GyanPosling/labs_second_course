# Lab 6

## Описание

Кооперация потоков для обработки больших индексных файлов с использованием `mmap()` и барьеров.

Утилиты:

- `gen` — генерация файла
- `view` — просмотр файла
- `sort_index` — многопоточная сортировка

## Сборка

```sh
make
make MODE=release
make clean
```

## Запуск

```sh
./build/debug/gen filename records
./build/debug/view filename
./build/debug/sort_index memsize blocks threads filename
```
