#ifndef STATUS_H
#define STATUS_H

#include <list>
#include <string>

struct Status {
  std::string cmdline;
  double budget;
  bool stdout, stderr;
  struct timeval launch;
  Status(const std::string &cmdline_, double budget_, const struct timeval &launch_)
   : cmdline(cmdline_), budget(budget_),
     stdout(true), stderr(true),
     launch(launch_) { }
};

extern bool refresh_needed;
extern std::list<Status> status_state;

void status_init();
void status_write(int fd, const char *data, int len);
void status_refresh();
void status_finish();

#endif
