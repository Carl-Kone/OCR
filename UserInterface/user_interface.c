#include <gtk/gtk.h>
#include <err.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "../Image/pixel_operations.h"
#include "../Image/hough_transform.h"
#include "../Image/display.h"
#include "../Image/preprocessing.h"

typedef struct UserInterface
{
    GtkWindow *window;
    SDL_Surface *image;
    GtkButton* load;
    GtkButton* grid;
    GtkButton* prepro;
    GtkButton* lines;
    GtkButton* result;
    GtkButton* split;
    GtkButton* train;
    GtkButton* test;
    GtkImage *display;
}UserInterface;

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
        g_print("%s\n", filename);
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, 600, 400, TRUE, NULL);
        gtk_image_set_from_pixbuf(ui->display,pixbuf);
    }
    gtk_widget_destroy(dialog);
    return TRUE;
}

gboolean prepro(GtkWidget *widget, gpointer user_data)
{
    UserInterface *ui = user_data;
    if(ui->image == NULL)
        return load_image(widget, user_data);
    else
    {
        const char *filename = preprocess(ui->image);
        ui->image = loadImage((char*)filename);
        g_print("%s\n", filename);
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, 600, 400, TRUE, NULL);
        gtk_image_set_from_pixbuf(ui->display,pixbuf);
        return TRUE;
    }
}

gboolean detectEdge(GtkWidget *widget, gpointer user_data)
{
    UserInterface *ui = user_data;
    if(ui->image == NULL)
        return load_image(widget, user_data);
    else
    {
        const char *filename = edge_detection(ui->image);
        ui->image = loadImage((char*)filename);
        g_print("%s\n", filename);
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, 600, 400, TRUE, NULL);
        gtk_image_set_from_pixbuf(ui->display,pixbuf);
        return TRUE;
    }
}

gboolean gridDetect(GtkWidget *widget, gpointer user_data)
{
    UserInterface *ui = user_data;
    squaredetect();
    ui->image = loadImage("final_square.bmp");
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("final_square.bmp", 600, 400, TRUE, NULL);
    gtk_image_set_from_pixbuf(ui->display,pixbuf);
    return TRUE;
}

gboolean split_func(GtkWidget *widget, gpointer user_data)
{
    return TRUE;
}

gboolean train_func(GtkWidget *widget, gpointer user_data)
{
    return TRUE;
}

gboolean test_func(GtkWidget *widget, gpointer user_data)
{
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
    GtkButton* grid = GTK_BUTTON(gtk_builder_get_object(builder, "grid_button"));
    GtkButton* lines = GTK_BUTTON(gtk_builder_get_object(builder, "solver_button"));
    GtkButton* result = GTK_BUTTON(gtk_builder_get_object(builder, "result_button"));
    GtkButton* split = GTK_BUTTON(gtk_builder_get_object(builder, "split_button"));
    GtkButton* train = GTK_BUTTON(gtk_builder_get_object(builder, "train_button"));
    GtkButton* test = GTK_BUTTON(gtk_builder_get_object(builder, "test_button"));
    GtkImage* display = GTK_IMAGE(gtk_builder_get_object(builder, "image"));

    UserInterface ui =
    {
        .image = NULL,
        .grid = grid,
        .split = split,
        .train = train,
        .test = test,
        .window = window,
        .load = load,
        .lines = lines,
        .result = result,
        .display = display,
    };

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(load, "clicked", G_CALLBACK(load_image), &ui);
    g_signal_connect(pre, "clicked", G_CALLBACK(prepro), &ui);
    g_signal_connect(grid, "clicked", G_CALLBACK(gridDetect), &ui);
    g_signal_connect(split, "clicked", G_CALLBACK(split_func), &ui);
    g_signal_connect(train, "clicked", G_CALLBACK(train_func), &ui);
    g_signal_connect(test, "clicked", G_CALLBACK(test_func), &ui);
    g_signal_connect(lines, "clicked", G_CALLBACK(detectEdge), &ui);
    g_signal_connect(result, "clicked", G_CALLBACK(displayy), NULL);

    gtk_main();

    // Exits
    return 0;
}
