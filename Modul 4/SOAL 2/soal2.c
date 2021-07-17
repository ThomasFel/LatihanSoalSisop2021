#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>

static const char *dirpath = "/home/thomasfelix/Documents";
static const char *logpath = "/home/thomasfelix/logging.log";

void fileLog(char *cmd, int lenDesc, const char *desc[]) {
    FILE *file = fopen(logpath, "a");
    time_t t;
    struct tm *temp;
    char timeBuffer[100];

    time(&t);
    temp = localtime(&t);

    strftime(timeBuffer, sizeof(timeBuffer), "%d%m%Y-%H:%M:%S", temp);
	
    fprintf(file, "%s:%s", timeBuffer, cmd);
  	
    for (int i = 0; i < lenDesc; i++) {
        fprintf(file, "::%s", desc[i]);
    }

    fprintf(file, "\n");

    fclose(file);
}

static int xmp_getattr(const char *path, struct stat *stbuf) {
    char fpath[1000];
    int res;

    sprintf(fpath, "%s%s", dirpath, path);
    res = lstat(fpath, stbuf);

    if (res == -1) {
	return -errno;
    }

    return 0;
}

static int xmp_access(const char *path, int mask) {  	
    char fpath[1000];
    int res;

    sprintf(fpath, "%s%s", dirpath, path);
    res = access(fpath, mask);

    if (res == -1) {
	return -errno;
    }

    return 0;
}

static int xmp_readlink(const char *path, char *buf, size_t size) {
    char fpath[1000];
    int res;

    sprintf(fpath, "%s%s", dirpath, path);
    res = readlink(fpath, buf, size - 1);

    if (res == -1) {
	return -errno;
    }

    buf[res] = '\0';
	
    return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    char fpath[1000];

    if (strcmp(path, "/") == 0) {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }

    else {
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
          
        res = (filler(buf, de->d_name, &st, 0));

        if (res != 0) {
            break;
        }
    }

    closedir(dp);
	
    return 0;
}

static int xmp_mkdir(const char *path, mode_t mode) {
    char fpath[1000];
    int res;

    sprintf(fpath, "%s%s", dirpath, path);
    res = mkdir(fpath, mode);

    const char *desc[] = {path};
    fileLog("MKDIR", 1, desc);

    if (res == -1) {
	return -errno;
    }

    return 0;
}

static int xmp_unlink(const char *path) {
    char fpath[1000];
    int res;

    sprintf(fpath, "%s%s", dirpath, path);
    res = unlink(fpath);

    if (res == -1) {
    	return -errno;
    }

    return 0;
}

static int xmp_rmdir(const char *path) {
    char fpath[1000];
    int res;

    sprintf(fpath, "%s%s", dirpath, path);
    res = rmdir(fpath);

    const char *desc[] = {path};
    fileLog("RMDIR", 1, desc);

    if (res == -1) {
	return -errno;
    }

    return 0;
}

static int xmp_rename(const char *from, const char *to) {
    char ffrom[1000];
    char fto[1000];
    int res;

    sprintf(ffrom, "%s%s", dirpath, from);
    sprintf(fto, "%s%s", dirpath, to);
    res = rename(ffrom, fto);

    const char *desc[] = {from, to};
    fileLog("RENAME", 2, desc);

    if (res == -1) {
	return -errno;
    }

    return 0;
}

static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    char fpath[1000];
    int res;

    sprintf(fpath, "%s%s", dirpath, path);
    res = open(fpath, fi->flags, mode);

    const char *desc[] = {path};
    fileLog("CREAT", 1, desc);

    if (res == -1) {
	return -errno;
    }

    fi->fh = res;

    return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi) {
    char fpath[1000];
    int res;

    sprintf(fpath, "%s%s", dirpath, path);
    res = open(fpath, fi->flags);

    const char *desc[] = {path};
    fileLog("OPEN", 1, desc);

    if (res == -1) {
	return -errno;
    }

    fi->fh = res;
	
    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[1000];

    if (strcmp(path, "/") == 0) {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }

    else {
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

static int xmp_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[1000];
    int fd;
    int res;
    (void) fi;

    sprintf(fpath, "%s%s", dirpath, path);
    
    if (fi == NULL) {
  	fd = open(fpath, O_WRONLY);
    }
	
    else {
  	fd = fi->fh;
    }

    if (fd == -1) {
	return -errno;
    }

    res = pwrite(fd, buf, size, offset);
	
    if (res == -1) {
        res = -errno;
    }

    if (fi == NULL) {
        close(fd);
    }
    
    return res;
}

static int xmp_release(const char *path, struct fuse_file_info *fi) {
    (void) path;
	
    close(fi->fh);
	
    return 0;
}


static const struct fuse_operations _oper = {
    .getattr	= xmp_getattr,
    .access	= xmp_access,
    .readlink	= xmp_readlink,
    .readdir	= xmp_readdir,
    .mkdir	= xmp_mkdir,
    .unlink	= xmp_unlink,
    .rmdir	= xmp_rmdir,
    .rename	= xmp_rename,
    .open	= xmp_open,
    .create 	= xmp_create,
    .read	= xmp_read,
    .write	= xmp_write,
    .release	= xmp_release,
};

int main(int argc, char *argv[]) {
    umask(0);
	
    return fuse_main(argc, argv, &_oper, NULL);
}
