# Дублирование файловых дескрипторов. Каналы

## Дублирование файловых дескрипторов

Для того, чтобы копировать файловые дескрипторы, есть 2 системных вызова: `dup` и `dup2`.

```
/* Возвращает копию нового файлового дескриптора, при этом, по аналогии
   с open, численное значение нового файлового дескриптора - минимальный
   не занятый номер. */
int dup(int old_fd);

/* Создаёт копию нового файлового дескриптора с явно указанным номером new_fd и в случае успеха его возвращает.
   Если ранее файловый дескриптор new_fd был открыт, то закрывает его. */
int dup2(int old_fd, int new_fd);
```

С помощью `dup2` можно сделать, например, перенаправление вывода нашей программы в файл (см. `freopen.c`).

А если скомбинировать его с `fork` и `exec`, можно перенаправлять вывод произольной программ в файл (см. `redirect.c`).

## Неименованные каналы

Канал -- это пара связанных между собой файловых дескрипторов, один из которых предназначен для только для чтения, а другой -- только для записи.
```
/* Создаёт канал и записывает файловый дескриптор читающего конца в 0 элемент массива, а пишущего -- в 1. */
int pipe(int pipefd[2]);
```

Канал буферизован, размер буффера, как правило, 65K. Запись происходит в буфер, если в нём не хватает места, то блокируемся. Если при этом читающий конец закрыт, `write` завершится с ошибкой `Broken pipe`. При чтении если буфер непуст, читаем из него, иначе блокируемся. Если пишущий конец закрыт, `read` вернёт 0.

Используя `pipe` можно перенаправить вывод произвольной программы себе на ввод (см. `pipe.c`). Если закомментировать в этом примере 23 строку, то программа зависнет. Почему?

## Именованные каналы

Для взаимодействия неродственных процессов можно использовать именованные каналы `FIFO`.

```
/* Создаёт файл канала по заданому пути и с задаными флагами доступа */
int mkfifo(const char *pathname, mode_t mode);
```

После создания такой канал можно открыть как обычный файл, но с режимом только на чтение или только на запись. Перед началом использования именного канала и пишущий, и читающий концы должны быть открыты. В остальном отличий от обычных каналов нет (пример использования можно увидеть в `fifo.c`).