#ifndef FILE_NOTIFY_H_
#define FILE_NOTIFY_H_

#include <sys/inotify.h>
#include <glib.h>

struct inotify_event;

typedef void (* inotify_event_cb) (struct inotify_event *event,
                    const char *ident);

int connman_inotify_register(const char *path, inotify_event_cb callback);
void connman_inotify_unregister(const char *path, inotify_event_cb callback);
int __connman_inotify_init(void);
void __connman_inotify_cleanup(void);

#endif // FILE_NOTIFY_H_
