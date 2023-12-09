#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    int print_inode = 0;
    int print_info = 0;
    int print_comma = 0;

    if (argc == 1) {
        dir = ".";
    } else if (argc == 2 && strcmp(argv[1], "-i") == 0) {
        dir = ".";
        print_inode = 1;
    } else if (argc == 2 && strcmp(argv[1], "-r") == 0) {
        dir = ".";
        print_info = 1;
    } else if (argc == 2 && strcmp(argv[1], "-m") == 0) {
        dir = ".";
        print_comma = 1;
    } else if (argc == 3 && strcmp(argv[1], "-r") == 0) {
        dir = argv[2];
        print_info = 1;
    } else if (argc == 3 && strcmp(argv[1], "-m") == 0) {
        dir = argv[2];
        print_comma = 1;
    } else if (argc == 2) {
        dir = argv[1];
    } else {
        printf("Error:%s [-i | -r | -m]\n", argv[0]);
        exit(1);
    }

    if ((dp = opendir(dir)) == NULL) 
        perror(dir);

    int file_count = 0;
    while ((d = readdir(dp)) != NULL) {
        file_count++;
    }

    char **files = malloc(sizeof(char*) * file_count);
    rewinddir(dp);

    int idx = 0;
    while ((d = readdir(dp)) != NULL) { 
        sprintf(path, "%s/%s", dir, d->d_name); 
        if (lstat(path, &st) < 0) 
            perror(path);
        else if (!print_info || (print_info && strcmp(argv[1], "-r") == 0)) {
            files[idx] = strdup(d->d_name);
            idx++;
        }
    }

    closedir(dp);

    if (print_comma) {
        for (int i = 0; i < file_count; ++i) {
            printf("%s", files[i]);
            if (i != file_count - 1) {
                printf(", ");
            }
            free(files[i]);
        }
        printf("\n");
    } else {
        if (print_info && strcmp(argv[1], "-r") == 0) {
            for (int i = file_count - 1; i >= 0; --i) {
                sprintf(path, "%s/%s", dir, files[i]);
                lstat(path, &st);
                printStat(path, files[i], &st, print_inode);
                free(files[i]);
            }
        } else {
            for (int i = 0; i < file_count; ++i) {
                sprintf(path, "%s/%s", dir, files[i]);
                lstat(path, &st);
                printStat(path, files[i], &st, print_inode);
                free(files[i]);
            }
        }
    }
    free(files);

    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, int print_inode) 
{
    if (print_inode) {
        printf("%ld ", st->st_ino);
    }

    printf("%5ld ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name,
              getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime)+4);
    printf("%s\n", file);
}

char type(mode_t mode) {
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
       return('s');
}

char* perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------");

    for (int i=0; i < 3; i++) {
        if (mode & (S_IRUSR >> i*3))
            perms[i*3] = 'r';
        if (mode & (S_IWUSR >> i*3))
           perms[i*3+1] = 'w';
        if (mode & (S_IXUSR >> i*3))
           perms[i*3+2] = 'x';
    }
    return(perms);
}
