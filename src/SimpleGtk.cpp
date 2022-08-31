//============================================================================
// Name        : SimpleGtk.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <gtk/gtk.h>

// callback function which is called when button is clicked
static void on_button_clicked(GtkButton *btn, gpointer data) {
    // change button label when it's clicked
    gtk_button_set_label(btn, "Hello World");
}

static void init_gui(GApplication * app)
{
    // create a new application window for the application
    // GtkApplication is sub-class of GApplication
    // downcast GApplication* to GtkApplication* with GTK_APPLICATION() macro
	GtkWidget * window = gtk_application_window_new(GTK_APPLICATION(app));
	GtkWidget * hpaned_container = gtk_hpaned_new();
	GtkWidget * text_view = gtk_text_view_new ();
	GtkWidget * notebook  = gtk_notebook_new();

    gtk_container_add (GTK_CONTAINER (GTK_WIDGET(window)), GTK_WIDGET(hpaned_container));
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK(notebook), GTK_POS_TOP);

    gtk_paned_add1 (GTK_PANED(hpaned_container), text_view);
    gtk_paned_add2 (GTK_PANED(hpaned_container), notebook);

    gtk_widget_set_size_request(GTK_WIDGET(text_view), 300, 100);

    // page 1
    GtkWidget * page1 = gtk_fixed_new();
	GtkWidget * label = gtk_label_new ("test1");
    gtk_notebook_append_page (GTK_NOTEBOOK(notebook), page1, label);

    GtkWidget * btn1 = gtk_button_new_with_label("Click Me!");
    GtkWidget * btn2 = gtk_button_new_with_label("Click Me!");
    GtkWidget * btn3 = gtk_button_new_with_label("Click Me!");

    g_signal_connect(btn1, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn2, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn3, "clicked", G_CALLBACK(on_button_clicked), NULL);

    gtk_fixed_put(GTK_FIXED(page1), GTK_WIDGET(btn1), 10, 10);
    gtk_fixed_put(GTK_FIXED(page1), GTK_WIDGET(btn2), 10, 50);
    gtk_fixed_put(GTK_FIXED(page1), GTK_WIDGET(btn3), 10, 90);

    // page 2
    GtkWidget * page2 = gtk_fixed_new();
	GtkWidget * label2 = gtk_label_new ("test2");
    gtk_notebook_append_page (GTK_NOTEBOOK(notebook), page2, label2);

    GtkWidget * btn4 = gtk_button_new_with_label("Click Me!");
    GtkWidget * btn5 = gtk_button_new_with_label("Click Me!");

    g_signal_connect(btn4, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(btn5, "clicked", G_CALLBACK(on_button_clicked), NULL);

    gtk_fixed_put(GTK_FIXED(page2), GTK_WIDGET(btn4), 50, 10);
    gtk_fixed_put(GTK_FIXED(page2), GTK_WIDGET(btn5), 10, 100);

    // display the window
    gtk_widget_show_all(GTK_WIDGET(window));
}

// callback function which is called when application is first started
static void on_app_activate(GApplication *app, gpointer data) {
    init_gui(app);
}

int main(int argc, char *argv[]) {
    // create new GtkApplication with an unique application ID
    GtkApplication *app = gtk_application_new(
        "org.gtkmm.example.HelloApp",
        G_APPLICATION_FLAGS_NONE
    );
    // connect the event-handler for "activate" signal of GApplication
    // G_CALLBACK() macro is used to cast the callback function pointer
    // to generic void pointer
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
    // start the application, terminate by closing the window
    // GtkApplication* is upcast to GApplication* with G_APPLICATION() macro
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    // deallocate the application object
    g_object_unref(app);
    return status;
}
