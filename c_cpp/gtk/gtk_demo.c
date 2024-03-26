//
// Created by zhangyipeng on 2023/11/7.
//
#include <gtk/gtk.h>
#include <curl/curl.h>

static void on_button_clicked(GtkButton *button, gpointer user_data) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        // 设置请求的 URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com");
        // 设置接收数据的回调函数，这里使用 libcurl 的默认打印到控制台
        res = curl_easy_perform(curl);
        // 检查请求是否成功
        if (res != CURLE_OK) {
            g_printerr("curl_easy_perform() failed: %s\n",
                       curl_easy_strerror(res));
        }
        // 清理资源
        curl_easy_cleanup(curl);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);


    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *button = gtk_button_new_with_label("Send HTTP Request");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    GtkWidget *button2 = gtk_button_new_with_label("Send HTTPS Request");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_box_pack_start(GTK_BOX(box), button, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_window_set_default_size(GTK_WINDOW (window), 500, 300);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}