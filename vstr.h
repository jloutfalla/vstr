/* vstr -- View String utility library

   Copyright (C) 2021 Jean-Baptiste Loutfalla <jb.loutfalla@orange.fr>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>. */

#ifndef VSTR_H
#define VSTR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef VSTRDEF
  #ifdef VSTRDEF_STATIC
    #define VSTRDEF static
  #else
    #define VSTRDEF extern
  #endif
#endif
  
  typedef struct
  {
    size_t      size;
    const char *data;
  } vstr;

#define VSTR(str) vstr_from_cstr((str))
#define VSTR_STATIC(str) (vstr) { .size = sizeof((str)) - 1, .data = (str) }
#define VSTR_NULL vstr_from_size_cstr(NULL, 0)
#define VSTR_FMT "%.*s"
#define VSTR_ARG(vstr) (int)(vstr).size, (vstr).data

  VSTRDEF vstr vstr_from_cstr(const char *cstr);
  VSTRDEF vstr vstr_from_size_cstr(const char *cstr, size_t size);
  VSTRDEF vstr vstr_trim_left(vstr str);
  VSTRDEF vstr vstr_trim_right(vstr str);
  VSTRDEF vstr vstr_separate_delim(vstr *restrict str, const char *restrict delim);
  VSTRDEF vstr vstr_separate_size(vstr *str, size_t count);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VSTR_H */

#ifdef VSTR_IMPLEMENTATION

#include <string.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  VSTRDEF vstr
  vstr_from_cstr(const char *cstr)
  {
    return vstr_from_size_cstr(cstr, strlen(cstr));
  }

  VSTRDEF vstr
  vstr_from_size_cstr(const char *cstr, size_t size)
  {
    vstr str = { .size = size, .data = cstr };
    return str;
  }

  VSTRDEF vstr
  vstr_trim_left(vstr str)
  {
    while (str.size > 0 && isspace(*str.data))
      {
        ++str.data;
        --str.size;
      }

    return str;
  }

  VSTRDEF vstr
  vstr_trim_right(vstr str)
  {
    while (str.size > 1 && isspace(str.data[str.size - 1]))
      --str.size;

    return str;
  }

  VSTRDEF vstr
  vstr_separate_delim(vstr *restrict str, const char *restrict delim)
  {
    size_t i, n, delim_size;
    vstr cut_part;

    delim_size = strlen(delim);
    n = delim_size > str->size ? str->size : delim_size;
    
    i = 0;
    while (i < str->size && strncmp(str->data + i, delim, n) != 0)
      ++i;

    cut_part = vstr_from_size_cstr(str->data, i);
    if (i + delim_size - 1 < str->size)
      {
        str->size -= i + delim_size;
        str->data += i + delim_size;
      }
    else
      {
        str->size = 0;
        str->data += i;
      }

    return cut_part;
  }

  VSTRDEF vstr
  vstr_separate_size(vstr *str, size_t count)
  {
    vstr cut_part;
  
    if (str->size < count)
      return VSTR_NULL;

    cut_part = vstr_from_size_cstr(str->data, count);
    str->size -= count;
    str->data += count;
  
    return cut_part;
  }


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VSTR_IMPLEMENTATION */
