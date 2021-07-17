#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/thomasfelix/Downloads";
static const char *needle = "/Jago_";
static const char *replacement = "/";

static void str_replace(char *target) {
    char buffer[1000] = {0};
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);

    while (1) {
        const char *p = strstr(tmp, needle);

        //Walked past last occurrence of needle; copy remaining part
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }

        //Copy part before needle
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;

        //Copy replacement string
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;

        //Adjust pointers, move on
        tmp = p + needle_len;
    }

    strcpy(target, buffer);
}

static int xmp_getattr(const char *path, struct stat *stbuf) {
    int res;
    char fpath[1000];

    str_replace(path);
    sprintf(fpath, "%s%s", dirpath, path);

    res = lstat(fpath, stbuf);

    if (res == -1) {
        return -errno;
    }

    return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    char fpath[1000], temp[1000];
    
    if (strcmp(path, "/") == 0) {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }

    else {
        str_replace(path);
        sprintf(fpath, "%s%s", dirpath, path);
    }

    int res = 0;

    DIR *dp;
    struct dirent *de;
    (void) offset;
    (void) fi;

    dp = opendir(path);

    if (dp == NULL) {
        return -errno;
    }

    while ((de = readdir(dp)) != NULL) {
        struct stat st;

        memset(&st, 0, sizeof(st));

        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;

        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") && de->d_type == DT_REG) {
            strcpy(temp, de->d_name);
            sprintf(de->d_name, "Jago_%s", temp);
        }

        res = (filler(buf, de->d_name, &st, 0));

        if (res != 0) {
            break;
        }
    }

    closedir(dp);

    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[1000];

    if (strcmp(path, "/") == 0) {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }

    else {
        str_replace(path);
        sprintf(fpath, "%s%s", dirpath, path);
    }
    
    int fd = 0;
    int res = 0;
    (void) fi;

    fd = open(fpath, O_RDONLY);

    if (fd == -1) {
        return -errno;
    }

    res = pread(fd, buf, size, offset);

    if (res == -1) {
        res = -errno;
    }

    close(fd);

    return res;
}

static struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .readdir = xmp_readdir,
    .read = xmp_read,
};

int main(int argc, char *argv[]) {
    umask(0);

    printf("Readdir: tes/n/n");
    return fuse_main(argc, argv, &xmp_oper, NULL);
}