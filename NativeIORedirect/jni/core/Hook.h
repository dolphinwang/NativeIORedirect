#pragma once
#include "hooklib/elf_hooker.h"
/**
 * 得到原始函数的函数指针变量名
 */
#define ORIGNAME(fn) __##fn##_Proxy

/**
 * 得到hook函数名
 */
#define HOOKNAME(fn) __##fn##_Hook

/**
 * 得到原始函数的函数指针的完整形式
 */
#define _ORIGVAR(ret, fn, arg...) \
  ret(*ORIGNAME(fn))(arg)

/**
 * 得到hook函数的完整形式
 */
#define _HOOKFUNC(ret, fn, arg...) \
  ret HOOKNAME(fn)(arg)

/**
 * 声明一个被hook的函数
 */
#define HOOKDEF(ret, fn, arg...) \
  extern _ORIGVAR(ret, fn, ##arg); \
  extern _HOOKFUNC(ret, fn, ##arg)

/**
 * 定义一个被hook的函数
 */
#define HOOK(ret, fn, arg...) \
  _ORIGVAR(ret, fn, ##arg); \
  _HOOKFUNC(ret, fn, ##arg)

/**
 * 调用原始的函数
 */
#define ORIGCALL(fn, arg...) \
  ORIGNAME(fn)(arg)

static elf_hooker __hooker;
/**
 * 调用Hooklib实现GotHook的包装
 */
#define inlineHook(fn, soname) \
   __hooker.hook_all_modules(#fn, (void*) HOOKNAME(fn), (void**) &ORIGNAME(fn))
