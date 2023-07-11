#include <gtk/gtk.h>
#include <stdlib.h>

#include "misc/info.h"
#include "topbar/core.h"

static void activate_app(GtkApplication *app, gpointer data) {
    activate_topbar(app, data);
}

int main(int argc, char **argv) {
    printf("Welcome to Aurora Shell %s!\n", AURORA_SHELL_VERSION);

    GtkApplication *app =
        gtk_application_new("org.aurora.shell", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate_app), NULL);

    if (g_application_run(G_APPLICATION(app), argc, argv) != 0)
        exit(EXIT_FAILURE);

    g_object_unref(app);

    return 0;
}
