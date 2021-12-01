#include <gtk/gtk.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../display.h"

typedef struct UserInterface
{
    SDL_Surface *image;
    GtkWindow *window;
    GtkButton* load;
    GtkButton* prepro;
    GtkButton* solver;
    GtkButton* result;
}UserInterface;

SDL_Surface *loadImage(char *path)
{
    SDL_Surface *image = NULL;
    image = IMG_Load(path);
    if (!image)
        errx(3, "can't load %s: %s", path, IMG_GetError());
    return image;
}

gboolean load_image(GtkWidget *widget, gpointer user_data)
{
    g_print("load fonction\n");
    /*
    elements *ele = user_data;
    GtkWindow *window = ele->window;
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
        ele->image = loadImage(filename);
    }
    gtk_widget_destroy (dialog);*/
    return TRUE;
}

gboolean prepro(gpointer user_data) // need parameter pointer to an image
{
    return TRUE;
}

gboolean solve_sudoku()
{
    // solve sudoku
    return TRUE;
}

gboolean display()
{
    // display image
    return TRUE;
}

int main(int argc, char *argv[])
{
    gtk_init(NULL, NULL);
    GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "OCR.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }
    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "OCR.ui"));
    GtkButton* load = GTK_BUTTON(gtk_builder_get_object(builder, "button_load"));
    GtkButton* prepro = GTK_BUTTON(gtk_builder_get_object(builder, "pre_button"));
    GtkButton* solver = GTK_BUTTON(gtk_builder_get_object(builder, "solver_button"));
    GtkButton* result = GTK_BUTTON(gtk_builder_get_object(builder, "result_button"));

    UserInterface ui =
    {
        .image = NULL,
        .window = window,
        .load = load,
        .solver = solver,
        .result = result,
    };
    g_print("elements init\n");

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(load, "clicked", G_CALLBACK(load_image), &ui);
    g_signal_connect(prepro, "clicked", G_CALLBACK(prepro), NULL);
    g_signal_connect(solver, "clicked", G_CALLBACK(solve_sudoku), NULL);
    g_signal_connect(result, "clicked", G_CALLBACK(display), NULL);

    gtk_main();

    // Exits
    return 0;
}
