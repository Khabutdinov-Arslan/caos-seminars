#include <errno.h>
#include <stdio.h>
#include <string.h>
#define FUSE_USE_VERSION 30
#include <fuse.h>
#include <stddef.h>
#include <zconf.h>
#include <stdlib.h>


typedef struct {
    char* src;
    int help;
} my_options_t;

struct my_file {
    char filename[PATH_MAX];
    int filesize;
    char* content_ptr;
};

#define BUFF_SIZE 1000000
char raw_data[BUFF_SIZE];
int file_count;
struct my_file* my_fs;

int read_buff(FILE* fd, char* buff, size_t buff_size)
{
    size_t read_buff_size = 0;
    for (; read_buff_size < buff_size;) {
        size_t read_during_iteration =
            fread(buff + read_buff_size, 1, buff_size - read_buff_size, fd);
        read_buff_size += read_during_iteration;
        if (read_during_iteration == 0) {
            return read_buff_size;
        }
    }
    return read_buff_size;
}

void open_filesystem(char* src)
{
    FILE* fd = fopen(src, "r");

    fscanf(fd, "%d\n", &file_count);
    my_fs = malloc(sizeof(struct my_file) * file_count);
    for (int i = 0; i < file_count; i++) {
        fscanf(
            fd, "%s %d\n", my_fs[i].filename, &my_fs[i].filesize);
    }

    read_buff(fd, raw_data, sizeof(raw_data));
    char* contents_ptr = raw_data;
    for (int i = 0; i < file_count; i++) {
        my_fs[i].content_ptr = contents_ptr;
        contents_ptr += my_fs[i].filesize;
    }

    fclose(fd);
}

int my_stat(const char* path, struct stat* st, struct fuse_file_info* fi)
{
    memset(st, 0, sizeof(struct stat));

    if (0 == strcmp("/", path)) {
        st->st_mode = S_IFDIR | 0755;
        st->st_nlink = 2;
        return 0;
    }

    for (int i = 0; i < file_count; i++) {
        if (strcmp(my_fs[i].filename, path + 1) == 0) {
            st->st_mode = S_IFREG | 0444;
            st->st_nlink = 1;
            st->st_size = my_fs[i].filesize;
            return 0;
        }
    }

    return -ENOENT;
}

int my_readdir(
    const char* path,
    void* out,
    fuse_fill_dir_t filler,
    off_t off,
    struct fuse_file_info* fi,
    enum fuse_readdir_flags flags)
{
    if (0 != strcmp(path, "/")) {
        return -ENOENT;
    }

    filler(out, ".", NULL, 0, 0);
    filler(out, "..", NULL, 0, 0);

    for (int i = 0; i < file_count; i++) {
        filler(out, my_fs[i].filename, NULL, 0, 0);
    }

    return 0;
}

int my_open(const char* path, struct fuse_file_info* fi)
{
    if (O_RDONLY != (fi->flags & O_ACCMODE)) {
        return -EACCES;
    }

    for (int i = 0; i < file_count; i++) {
        if (strcmp(my_fs[i].filename, path + 1) == 0) {
            fi->fh = (uint64_t)&my_fs[i];
            return 0;
        }
    }

    return -ENOENT;
}

int my_read(
    const char* path,
    char* out,
    size_t size,
    off_t off,
    struct fuse_file_info* fi)
{
    struct my_file *cur_file = (struct my_file*)fi->fh;

    if (off >= cur_file->filesize) {
        return 0;
    }

    if (off + size > cur_file->filesize) {
        size = cur_file->filesize - off;
    }

    const void* data = cur_file->content_ptr + off;
    memcpy(out, data, size);

    return size;
}

void my_destroy(void* private_data){
    free(my_fs);
}

struct fuse_operations operations = {
    .readdir = my_readdir,
    .getattr = my_stat,
    .open = my_open,
    .read = my_read,
    .destroy = my_destroy
};

int main(int argc, char* argv[])
{
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    my_options_t my_options;
    memset(&my_options, 0, sizeof(my_options));
    struct fuse_opt opt_specs[] = {
        {"--src %s", offsetof(my_options_t, src), 0},
        {NULL, 0, 0}};
    fuse_opt_parse(&args, &my_options, opt_specs, NULL);

    if (my_options.src) {
        open_filesystem(my_options.src);
    }

    int return_code = fuse_main(args.argc, args.argv, &operations, NULL);
    return return_code;
}
