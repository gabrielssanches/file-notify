#include "file_notify.h"

#include <glib.h>
#include <sys/inotify.h>

static void config_notify_handler(struct inotify_event *event,
                                        const char *ident)
{
    g_message(">>> %s:%d", ident, event->mask); 
#if 0
    char *ext;

    if (!ident)
        return;

    if (!g_str_has_suffix(ident, ".config"))
        return;

    ext = g_strrstr(ident, ".config");
    if (!ext)
        return;

    *ext = '\0';

    if (!validate_ident(ident)) {
        connman_error("Invalid config ident %s", ident);
        return;
    }    

    if (event->mask & (IN_CREATE | IN_MOVED_TO))
        create_config(ident);

    if (event->mask & (IN_MODIFY | IN_MOVED_TO)) {
        struct connman_config *config;

        config = g_hash_table_lookup(config_table, ident);
        if (config) {
            int ret; 

            g_hash_table_remove_all(config->service_table);
            load_config(config);
            ret = __connman_service_provision_changed(ident);
            if (ret > 0) { 
                /*   
                 * Re-scan the config file for any
                 * changes
                 */
                g_hash_table_remove_all(config->service_table);
                load_config(config);
                __connman_service_provision_changed(ident);
            }    
        }    
    }    

    if (event->mask & (IN_DELETE | IN_MOVED_FROM))
        g_hash_table_remove(config_table, ident);
#endif
}

int main(int argc, char **argv) {
    __connman_inotify_init();

    connman_inotify_register("tmp", config_notify_handler);

    GMainLoop *loop;
    loop = g_main_loop_new(NULL, FALSE);

    g_message("Running");

    g_main_loop_run(loop);

    g_message("Done");

    return 0;
}
