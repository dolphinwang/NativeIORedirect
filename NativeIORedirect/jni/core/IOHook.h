#pragma once

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>

#include "Hook.h"

extern "C" {
  extern int linkat(int, const char*, int, const char*, int);
  extern int symlinkat(const char*, int, const char*);
  extern int faccessat(int, const char*, int, int);
  extern int mknodat(int, const char*, mode_t, dev_t);
}

namespace kiva
{

void initPreHook();
void phraseProcMaps();

/**
 * 声明所有预定义的hook
 * 定义在 IOHook.cc
 */
#include "prehook.dec.h"

}
