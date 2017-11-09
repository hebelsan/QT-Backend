#ifndef LENKRAD_HPP
#define LENKRAD_HPP
//#pragma once


extern "C" {
  //#include <config.h>
  #include "../config.h"
  //#include <libevdev.h>
  #include "../libevdev/libevdev.h"
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <linux/input.h>
}


#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <assert.h>

#include <pthread.h>
#include <iostream>
#include "datentypen.hpp"


//PThread Prototyp

void *lenkrad_lesen (void* val);


#endif