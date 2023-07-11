#include <gtk/gtk.h>

#include "misc/logger.h"
#include "topbar/core.h"

#define BH 45

static void load_css(void) {
    GError *error = NULL;
    GResource *resource = g_resource_load("/org/aurora/shell/resources.gresource", &error);
    if (error) {
        g_error("Failed to load resources: %s", error->message);
        g_error_free(error);
        return;
    }

    GBytes *bytes = g_resource_lookup_data(resource, "/org/aurora/shell/src/topbar/style.css", 0, NULL);
    if (bytes == NULL) {
        g_error("Failed to load CSS resource");
        return;
    }

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, g_bytes_get_data(bytes, NULL), g_bytes_get_size(bytes), NULL);
    g_object_unref(bytes);

    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(provider);
}

static void load_widgets(GtkWidget *w) {
    GtkWidget *button = gtk_button_new_with_label("This is a test button");
    gtk_container_set_border_width(GTK_CONTAINER(w), 4);
    gtk_container_add(GTK_CONTAINER(w), button);
}

void activate_topbar(GtkApplication *app, gpointer data) {
    info("Loading top bar");

    GtkWidget *w = gtk_application_window_new(app);
    GdkScreen *s = gdk_screen_get_default();

    int sh = gdk_screen_get_height(s);
    int sw = gdk_screen_get_width(s);

    gtk_window_set_wmclass(GTK_WINDOW(w), "Aurora-Shell-Bar",
                           "Aurora-Shell-Bar");

    gtk_window_set_type_hint(GTK_WINDOW(w), GDK_WINDOW_TYPE_HINT_DOCK);
    gtk_window_set_gravity(GTK_WINDOW(w), GDK_GRAVITY_NORTH_WEST);
    gtk_window_set_decorated(GTK_WINDOW(w), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(w), TRUE);
    gtk_widget_set_size_request(w, sw, BH);

    gtk_window_set_geometry_hints(
        GTK_WINDOW(w), NULL,
        &(GdkGeometry){sw, 40, -1, -1, -1, -1, -1, -1, -1, -1},
        GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE);

    gtk_window_move(GTK_WINDOW(w), 0, sh - BH);

    load_css();
    load_widgets(w);

    gtk_widget_show_all(w);
}
