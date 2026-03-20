#ifndef CONTROLLER_H
#define CONTROLLER_H

struct Controller {
  int transmitterPin;
  unsigned long buckets[8];
  unsigned long id;
};

#endif
