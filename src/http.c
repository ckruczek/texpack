/* 
 * File:   http.h
 * Author: Christopher Kruczek
 * 
 * Copyright (C) 2015 The texpack Open Source Project
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <string.h>

#include "http.h"

static CURL *curl_handle;

/*
 Initialize curl and set some basic information
 * like the useragent.
 */
void http_init()
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
}
/*
 * Cleanup the curl handle and the global configuration.
 */
void http_cleanup()
{
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
}

/*
 * Perform a http request with the given url
 * and the callback.
 * @param url - The url used for the request
 * @param callback - The callback used for the result processing.
 *                   If the callback is NULL a default callback is used
 *                   that just prints the content to the stdout.
 */
void http_request(char* url, write_callback callback)
{
    write_callback defaultcb = callback == NULL ? http_default_callback : callback;
    curl_easy_setopt(curl_handle,CURLOPT_URL,url);
    curl_easy_setopt(curl_handle,CURLOPT_WRITEFUNCTION,defaultcb);
    curl_easy_perform(curl_handle);
}

/*
 * A default callback handler for requests with no defined callbacks.
 * This callback prints the result to the stdout.
 */
size_t http_default_callback(void *content, size_t size, size_t nmemb, void *userdata)
{
    (void)userdata;
    
    size_t realsize = size * nmemb;
    char *realContent = malloc(realsize);
    if(!realContent)
    {
        fprintf(stderr,"Can't allocate memory in http_default_callback\n");
        exit(0);
    }
    
    memcpy(realContent,content,realsize);
    fprintf(stdout,"%s\n",realContent);
    free(realContent);
    
    return realsize;
}

/*
 * Create a url from the given packagename and format
 * @param packageName - The packagename used for the url format.
 * @param format - The url format, e.g.HTTP_PACKAGE_URL_FORMAT or HTTP_PACKAGES_URL_FORMAT
 */
char* http_create_url(char* packageName, char* format)
{
    size_t combinedLength = strlen(packageName) + strlen(format);
    char *url = malloc(combinedLength);
    if(!url)
    {
        fprintf(stderr,"Can't allocate memory in http_create_url\n");
        exit(-1);
    }
    sprintf(url,format,packageName);
    return url;
}
