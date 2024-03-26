#include "net.h"
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>

int https_net()
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/typecho-fans/plugins/contents/");
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* always cleanup */
        curl_easy_cleanup(curl);
        system("pause");
    }
    return 0;
}