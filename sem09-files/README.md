# Файловый ввод-вывод

## Файловые дескрипторы

Файловый дескриптор это абстракция для ввода/вывода (это может быть файл, пайп или сокет). Это число, которое адресует файл в рамках одного процесса. Внутри ядра содержится структура содержит адрес файла и позицию курсора.
Стандартные файловые дескрипторы вам уже знакомы: 0 stdin, 1 stdout, 2 stderr.

## Open/Close

Системный вызов open преднозначен для создания файлового дескриптора из файла.

```
int open(const char *path, int flags, ... /* mode_t mode */);
// путь к файлу
// flags O_RDONLY, O_WRONLY, ..., O_CREAT
```

Основные параметры открытия файлов:
 * `O_RDONLY` - только для чтения;
 * `O_WRONLY` - только на запись;
 * `O_RDWR` - чтение и запись;
 * `O_APPEND` - запись в конец файла;
 * `O_TRUNC`- обнуление файла при открытии;
 * `O_CREAT` - создание файла, если не существует;
 * `O_EXCL` - создание файла только если он не существует.

В случае успеха возвращается неотрицательное число - дескриптор, в случае ошибки - значение `-1`.

Третий аргумент отвечает за права.

В случае создания файла, обязательным параметром является набор POSIX-аттрибутов доступа к файлу. Как правило, они кодируются в восьмиричной системе исчисления в виде `0ugo`, где `u` - права доступа для владельца файла, `g` - права доступа для всех пользователей группы файла, `o` - для остальных.

В восьмеричной записи значения от 0 до 7 соответствуют комбинации трёх бит:
```
00: ---
01: --x
02: -w-
03: -wx
04: r--
05: r-x
06: rw-
07: rwx
```

## Read/Write

Чтение и запись осуществляются с помощью системных вызовов:

```
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
// count максимальне количесто байт, должно быть меньше размера буффера.
```

Возвращают они количество прочитанных/записанных байт. Это число может быть меньше `count`, поэтому нужно вызывать их в цикле.

## Seek

Иногда полезно сдвигать курсор по файлу.

```
off_t lseek(int fd, off_t offset, int whence);
// offset from whence
// whence = SEEK_SET|SEEK_CUR|SEEK_END (begin of file/current offset/end of file)
```

Возвращает системный вызов текущее смещение. Для 64-битных отступов:

```
#define _FILE_OFFSET_BITS 64
```

## Атрибуты файлов

### Жёсткие и символические ссылки

Ссылки на файлы бывают двух типов:

* Жёсткие - ещё одно имя для файла
* Мягкий - ссылка на файл по конкретному пути. Это означает, что они инвалидируются при переименовании.

Создавать их можно, например, с помощью команды `ln`. По-умолчанию создаётся жёсткая ссылка, с опцией `-s` -- мягкая. Например:

```
ln -s in.txt in_soft.txt
```

Есть и системные вызовы для работы с ними `link`, `unlink`, `symlink`, `readlink`.

### Метаинформация о файле. Структура stat.

С каждым файлом связана метаинформация, представимая структурой `stat`:

```
struct stat {
   dev_t     st_dev;         /* ID of device containing file */
   ino_t     st_ino;         /* Inode number */
   mode_t    st_mode;        /* File type and mode */
   nlink_t   st_nlink;       /* Number of hard links */
   uid_t     st_uid;         /* User ID of owner */
   gid_t     st_gid;         /* Group ID of owner */
   dev_t     st_rdev;        /* Device ID (if special file) */
   off_t     st_size;        /* Total size, in bytes */
   blksize_t st_blksize;     /* Block size for filesystem I/O */
   blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

   struct timespec st_atim;  /* Time of last access */
   struct timespec st_mtim;  /* Time of last modification */
   struct timespec st_ctim;  /* Time of last status change */

   /* Backward compatibility */
   #define st_atime st_atim.tv_sec      
   #define st_mtime st_mtim.tv_sec
   #define st_ctime st_ctim.tv_sec
};
```

Получить её можно с помощью систмных вызовов

```
int (l)stat(const char *file_name, struct stat *stat_buffer)
```

Версия с `l` не переходит по символическим ссылкам.

Есть ещё версия для работы с файловыми дескрипторами. Она хороша тем, что пока файл открыт, он не удаляется с диска.

```
int fstat(int fd, struct stat *stat_buffer)
```

В `st_mode` кроме разрешений закодирован тип файла. Проверить его можно с помощью макросов:
* `S_ISREG` регулярный
* `S_ISDIR` папка
* `S_ISLNK` символическая ссылка

Проверить уровень доступ текущего пользователя к файлу можно с помощью `access`.

```
int access(const char *path_name, int mode);
// mode = R_OK | W_OK | X_OK
```

Он возвращает 0, если у пользователя есть доступ.

Примеры использования этих системных вызовов можно найти в `count_filetypes.c`.
