#pragma once

#define DISALLOW_COPY_AND_ASSIGN(name) \
  private: \
    name(const name&); \
    name(const name&&); \
    name& operator=(const name&); \
    name& operator=(const name&&)
