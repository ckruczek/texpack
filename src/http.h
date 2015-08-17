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

#ifndef HTTP_H
#define	HTTP_H

#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#define HTTP_PACKAGE_URL_FORMAT         "https://www.ctan.org/json/pkg/%s"
#define HTTP_PACKAGES_URL_FORMAT        "https://www.ctan.org/json/packages?key=%s"
#define HTTP_MIRROR                     "http://mirror.ctan.org/"

typedef size_t (*write_callback)(void*,size_t,size_t,void*);

void http_init();
void http_cleanup();
char* http_create_url(char *packageName,char *format);
void http_request(char *url,write_callback callback);
size_t http_default_callback(void*,size_t,size_t,void*);

#endif	

