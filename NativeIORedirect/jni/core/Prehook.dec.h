HOOKDEF(int, creat, const char *, mode_t);

HOOKDEF(int, link, const char *, const char *);

HOOKDEF(int, linkat, int, const char*, int, const char*);

HOOKDEF(int, symlink, const char *, const char *);

HOOKDEF(int, symlinkat, const char *,int, const char *);

HOOKDEF(int, readlink, const char*, char*, size_t);

HOOKDEF(ssize_t, readlinkat, int, const char *,
                          char *, size_t);

HOOKDEF(int, unlink, const char*);

HOOKDEF(int, unlinkat, int, const char *, int);

HOOKDEF(int, rmdir, const char*);

HOOKDEF(int, mkdir, const char*, mode_t);

HOOKDEF(int, rename, const char*, const char*);

HOOKDEF(int, renameat, int, const char *,
                    int, const char *);

HOOKDEF(int, stat, const char*, struct stat*);

HOOKDEF(int, lstat, const char*, struct stat*);

HOOKDEF(int, chmod, const char*, mode_t);

HOOKDEF(int, access, const char*, int);

HOOKDEF(int, faccessat, int, const char *, int, int);

HOOKDEF(int, open, const char*, int);

HOOKDEF(int, openat, int, const char*, int);

HOOKDEF(int, chdir, const char *);

HOOKDEF(int, mknod, const char*, mode_t, dev_t);

HOOKDEF(void*, dlopen, const char*, int);

HOOKDEF(int, chown, const char*, uid_t, gid_t);

HOOKDEF(int, fchownat, int, const char*, uid_t, gid_t, int);

HOOKDEF(int, fstatat, int, const char*, struct stat*, int);

HOOKDEF(int, fchmodat, int, const char*, mode_t, int);

HOOKDEF(int, truncate, const char *, off_t);

HOOKDEF(int, execve, const char *,char * const [],char * const []);