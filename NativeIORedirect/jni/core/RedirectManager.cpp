#include "RedirectManager.h"
#include "IOHook.h"

#include <string.h>

#include <algorithm>

#include "../Logger.h"


namespace kiva
{

static bool startsWith(const std::string &str, const std::string &pattern)
{
  return pattern.length() <= str.length() && strncmp(str.c_str(), pattern.c_str(), pattern.length()) == 0;
}

RedirectManager::RedirectManager()
  :needInit(true)
{
}

RedirectManager::~RedirectManager()
{
}

RedirectManager& RedirectManager::getInstance()
{
  static RedirectManager mgr;
  return mgr;
}

void RedirectManager::init()
{ 
  if (needInit) {
    phraseProcMaps();
    initPreHook();
    LOGD("[+] RedirectManager => onCreate");
    needInit = false;
  }
}



void RedirectManager::set(const K &oldPath, const V &newPath, const bool isFullReplace)
{
  redirects.insert(std::pair<K, V>(oldPath, newPath));
  full_replaces.insert(std::pair<K, bool>(oldPath, isFullReplace));
}

void RedirectManager::remove(const K &oldPath)
{
  redirects.erase(oldPath);
}

void RedirectManager::remove(const std::function<bool(const K&, const V&)> &filter)
{
  foreach([&] (const K &o, const V &n) {
    if (filter(o, n)) {
      remove(o);
      return true;
    }
    return false;
  });
}

void RedirectManager::foreach(const std::function<bool(const K&, const V&)> &cb) const
{
  if (!cb) {
    return;
  }
  LOGD(" --- foreach size=%d\n", redirects.size());
  auto it = redirects.begin();
  for (; it != redirects.end(); ++it) {
    if (cb((*it).first, (*it).second)) {
      break;
    }
  }
}

void RedirectManager::redirect(std::string &path) const
{ 
  foreach([&] (const K &o, const V &n) {
    if (startsWith(path, o)) {
      LOGD("[+++] An IO Redirect Hit.");
      auto isFullReplacePointer = full_replaces.find(o);
      if(isFullReplacePointer != full_replaces.end()) {
        bool isFullReplace = isFullReplacePointer->second;
        if(isFullReplace) {
          path = std::move(n);
        }else {
          path = std::move(path.replace(0, o.length(), n));
        }
      }else {
        LOGE("[---] No Flag with this IO Redirect, ignore.");
      }

      return true;
    }
  
    return false;
  });
}

}
