#pragma once

#include <string>
#include <functional>
#include <map>

#include "Utils.h"

namespace kiva
{

class RedirectManager
{
  // This is not a template
  // just for saving time.
  using K = std::string;
  using V = std::string;

private:
  DISALLOW_COPY_AND_ASSIGN(RedirectManager);
  
  bool needInit;
  std::map<K, V> redirects;
  std::map<K, bool> full_replaces;
  
  RedirectManager();
  ~RedirectManager();

public:
  static RedirectManager& getInstance();
  
  void init();
  void set(const K &oldPath, const V &newPath, const bool isFullReplace);
  void remove(const K &oldPath);
  void remove(const std::function<bool(const K&, const V&)> &filter);
  void foreach(const std::function<bool(const K&, const V&)> &cb) const;
  void redirect(std::string &path) const;
  
  inline bool contains(const K &oldPath) const
  {
    return redirects.find(oldPath) != redirects.end();
  }
  
  // inline V& operator[](const K &oldPath)
  // {
  //   return redirects[oldPath];
  // }
};

}
