#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int read_buff(int fd, char* data, int size) {
    char* cdata = data;
    while (1) {
        size_t read_bytes = read(fd, cdata, size);
        if (read_bytes == 0) { // если read вернул 0, значит файловый дескриптор закрыт с другого конца
            // или конец файла
            return cdata - data;
        }
        if (read_bytes < 0) { // если возвращено значение < 0, то это ошибка
            if (errno == EAGAIN || errno == EINTR) { // она может быть retryable
                continue;
            } else { // а может быть критичной, и нет смысла пытаться повторить попытку чтения
                return -1;
            }
        }
        // если возвращенное значение > 0, значит успешно прочитано столько байт
        cdata += read_bytes;
        size -= read_bytes;
        if (size == 0) {
            return cdata - data;
        }
    }
}

int main() {
    const size_t BUFF_SIZE = 4096;
    char buffer[BUFF_SIZE];
    int read_count = read_buff(0, buffer, BUFF_SIZE);
    printf("Read %d", read_count);
    return 0;
}
