#include "IOHook.h"
#include "RedirectManager.h"
#include "../Logger.h"

#define NEWPATHNAME __new_path1
#define NEWPATH (NEWPATHNAME.c_str())

#define NEWPATHNAME2 __new_path2
#define NEWPATH2 (NEWPATHNAME2.c_str())

#define REDIRECT(var) \
  std::string NEWPATHNAME(var); \
  RedirectManager::getInstance().redirect(NEWPATHNAME); \
  LOGD("%s: [%s] -> [%s]\n", __FUNCTION__, var, NEWPATH);

#define REDIRECT2(var1, var2) \
  std::string NEWPATHNAME(var1); \
  std::string NEWPATHNAME2(var2); \
  auto &r = RedirectManager::getInstance(); \
  r.redirect(NEWPATHNAME); \
  r.redirect(NEWPATHNAME2); \
  LOGD("%s: [%s] -> [%s]\n", __FUNCTION__, var1, NEWPATH); \
  LOGD("%s: [%s] -> [%s]\n", __FUNCTION__, var2, NEWPATH2);

namespace kiva
{

HOOK(int, chdir, const char *file)
{
  REDIRECT(file);
  return ORIGCALL(chdir, NEWPATH);
}

HOOK(int, openat,int fd, const char *file, int flag)
{
  REDIRECT(file);
  return ORIGCALL(openat, fd, NEWPATH, flag);
}

HOOK(int, open, const char *file, int flag)
{
  REDIRECT(file);
  return ORIGCALL(open, NEWPATH, flag);
}

HOOK(int, link, const char *path1, const char *path2)
{
  REDIRECT2(path1, path2);
  return ORIGCALL(link, NEWPATH, NEWPATH2);
}

HOOK(int, linkat, int efd, const char * path1, int nfd, const char * path2)
{
  REDIRECT2(path1, path2);
  return ORIGCALL(linkat, efd, NEWPATH, nfd, NEWPATH2);
}

HOOK(int, symlink, const char *path1, const char *path2)
{
  REDIRECT2(path1, path2);
  return ORIGCALL(symlink, NEWPATH, NEWPATH2);
}

HOOK(int, symlinkat, const char * path1,int fd,const char * path2)
{
  REDIRECT2(path1, path2);
  return ORIGCALL(symlinkat, NEWPATH, fd, NEWPATH2);
}

HOOK(int, readlink, const char *path, char *buf, size_t bufsz)
{
  REDIRECT(path);
  return ORIGCALL(readlink, NEWPATH, buf, bufsz);
}

HOOK(ssize_t, readlinkat, int dirfd, const char *path,
                          char *buf, size_t bufsiz)
{
  REDIRECT(path);
  return ORIGCALL(readlinkat, dirfd, NEWPATH, buf, bufsiz);
}

HOOK(int, unlink, const char *path)
{
  REDIRECT(path);
  return ORIGCALL(unlink, NEWPATH);
}

HOOK(int, rmdir, const char *path)
{
  REDIRECT(path);
  return ORIGCALL(rmdir, NEWPATH);
}

HOOK(int, mkdir, const char *path, mode_t mode)
{
  REDIRECT(path);
  return ORIGCALL(mkdir, NEWPATH, mode);
}

HOOK(int, creat, const char *path, mode_t mode)
{
  REDIRECT(path);
  return ORIGCALL(creat, NEWPATH, mode);
}

HOOK(int, rename, const char *path1, const char *path2)
{
  REDIRECT2(path1, path2);
  return ORIGCALL(rename, NEWPATH, NEWPATH2);
}

HOOK(int, renameat, int olddirfd, const char *path1,
                    int newdirfd, const char *path2)
{
  REDIRECT2(path1, path2);
  return ORIGCALL(renameat, olddirfd, NEWPATH, newdirfd, NEWPATH2);
}

HOOK(int, stat, const char *path, struct stat *buf)
{
  REDIRECT(path);
  return ORIGCALL(stat, NEWPATH, buf);
}

HOOK(int, lstat, const char *path, struct stat *buf)
{
  REDIRECT(path);
  return ORIGCALL(lstat, NEWPATH, buf);
}

HOOK(int, chmod, const char *path, mode_t mode)
{
  REDIRECT(path);
  return ORIGCALL(chmod, NEWPATH, mode);
}

HOOK(int, access, const char *path, int flag)
{
  REDIRECT(path);
  return ORIGCALL(access, NEWPATH, flag);
}

HOOK(int, faccessat, int dirfd, const char *path, int mode, int flags)
{
  REDIRECT(path);
  return ORIGCALL(faccessat, dirfd, NEWPATH, mode, flags);
}

HOOK(int, mknod, const char *path, mode_t mode, dev_t dev)
{
  REDIRECT(path);
  return ORIGCALL(mknod, NEWPATH, mode, dev);
}

HOOK(void*, dlopen, const char *path, int flag)
{
  REDIRECT(path);
  return ORIGCALL(dlopen, NEWPATH, flag);
}

HOOK(int, chown, const char *path, uid_t owner, gid_t group)
{
  REDIRECT(path);
  return ORIGCALL(chown, NEWPATH, owner, group);
}

HOOK(int, fchownat, int fd, const char *path, uid_t u, gid_t g, int f)
{
  REDIRECT(path);
  return ORIGCALL(fchownat, fd, NEWPATH, u, g, f);
}

HOOK(int, fstatat, int fd, const char *path, struct stat* buf, int f)
{
  REDIRECT(path);
  return ORIGCALL(fstatat, fd, NEWPATH, buf, f);
}

HOOK(int, fchmodat, int fd, const char *path, mode_t mode, int f)
{
  REDIRECT(path);
  return ORIGCALL(fchmodat, fd, NEWPATH, mode, f);
}

HOOK(int, truncate, const char * path,off_t length)
{
  REDIRECT(path);
  return ORIGCALL(truncate, NEWPATH, length);
}

HOOK(int, execve, const char * path,char * const argv[],char * const envp[])
{
  REDIRECT(path);
  return ORIGCALL(execve, NEWPATH, argv, envp);
}

HOOK(int, unlinkat, int dirfd, const char *path, int flags)
{
  REDIRECT(path);
  return ORIGCALL(unlinkat, dirfd, NEWPATH, flags);
}

static bool needInitPreHook = true;

static bool __prehook(const char* module_name, const char* func_name)
{
    // LOGD(">>>>>>>>>>> Module Name : %s, Function Name : %s.", module_name, func_name);
  if(strstr(module_name, "libc.so") != NULL 
    || strstr(module_name, "libdl.so") != NULL) {
    return true;
  }
    return false;
}

void initPreHook()
{
  if (needInitPreHook) {
    needInitPreHook = false;
    __hooker.set_prehook_cb(__prehook);
#   include "prehook.h"
  }
}

void phraseProcMaps() {
  __hooker.phrase_proc_maps();
}

}
