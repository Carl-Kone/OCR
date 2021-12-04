#include <gtk/gtk.h>
#include <err.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../display.h"
#include "../preprocessing.h"

typedef struct UserInterface
{
    GtkWindow *window;
    SDL_Surface *image;
    GtkButton* load;
    GtkButton* prepro;
    GtkButton* solver;
    GtkButton* result;
    GtkImage *display;
}UserInterface;
/*
SDL_Surface *loadImage(char *path)
{
    SDL_Surface *image = NULL;
    image = IMG_Load(path);
    if (!image)
        errx(3, "can't load %s: %s", path, IMG_GetError());
    return image;
 }*/

gboolean load_image(GtkWidget *widget, gpointer user_data)
{
    UserInterface *ui = user_data;
    GtkWindow *window = ui->window;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new ("Open File",
                                      window,
                                      action,
                                      ("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      ("_Open"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        gchar *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        if(SDL_Init(SDL_INIT_VIDEO) == -1)
            errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
        ui->image = loadImage(filename);
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, 600, 400, TRUE, NULL);
        gtk_image_set_from_pixbuf(ui->display,pixbuf);
    }
    gtk_widget_destroy(dialog);
    return TRUE;
}

gboolean prepro(GtkWidget *widget, gpointer user_data)
{
    UserInterface *ui = user_data;
    const char *filename = preprocess(ui->image);
    ui->image = loadImage((char*)filename);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, 600, 400, TRUE, NULL);
    gtk_image_set_from_pixbuf(ui->display,pixbuf);
    return TRUE;
}

gboolean solve_sudoku(GtkWidget *widget, gpointer user_data)
{
    // solve sudoku
    return TRUE;
}

gboolean displayy(GtkWidget *widget, gpointer user_data)
{
    // display image
    return TRUE;
}

int main(int argc, char *argv[])
{
    gtk_init(NULL, NULL);
    GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "OCRui.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }
    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "OCR.ui"));
    GtkButton* load = GTK_BUTTON(gtk_builder_get_object(builder, "button_load"));
    GtkButton* pre = GTK_BUTTON(gtk_builder_get_object(builder, "pre_button"));
    GtkButton* solver = GTK_BUTTON(gtk_builder_get_object(builder, "solver_button"));
    GtkButton* result = GTK_BUTTON(gtk_builder_get_object(builder, "result_button"));
    GtkImage* display = GTK_IMAGE(gtk_builder_get_object(builder, "image"));

    UserInterface ui =
    {
        .image = NULL,
        .window = window,
        .load = load,
        .solver = solver,
        .result = result,
        .display = display,
    };

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(load, "clicked", G_CALLBACK(load_image), &ui);
    g_signal_connect(pre, "clicked", G_CALLBACK(prepro), &ui);
    g_signal_connect(solver, "clicked", G_CALLBACK(solve_sudoku), NULL);
    g_signal_connect(result, "clicked", G_CALLBACK(displayy), NULL);

    gtk_main();

    // Exits
    return 0;
}
