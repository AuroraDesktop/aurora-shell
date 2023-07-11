#include <gtk/gtk.h>

#include "topbar/core.h"
#include "misc/logger.h"

#define BH 40

void activate_topbar(GtkApplication *app, gpointer data) {
    info("Loading top bar");

    GtkWidget *w = gtk_application_window_new(app);
    GdkScreen *s = gdk_screen_get_default();

    int sh = gdk_screen_get_height(s);
    int sw = gdk_screen_get_width(s);

    gtk_window_set_wmclass(GTK_WINDOW(w), "Aurora-Shell-Bar", "Aurora-Shell-Bar");
    gtk_window_set_type_hint(GTK_WINDOW(w), GDK_WINDOW_TYPE_HINT_DOCK);
    gtk_window_set_gravity(GTK_WINDOW(w), GDK_GRAVITY_NORTH_WEST);
    gtk_window_set_decorated(GTK_WINDOW(w), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(w), TRUE);
    gtk_widget_set_size_request(w, sw, BH);
    gtk_window_set_geometry_hints(GTK_WINDOW(w), NULL, &(GdkGeometry) {
        sw, 40, -1, -1, -1, -1, -1, -1, -1, -1
    }, GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE);
    gtk_window_move(GTK_WINDOW(w), 0, sh - BH);

    // TODO: Add widgets here.

    gtk_widget_show_all(w);
}
