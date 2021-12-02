#include <stdio.h>

#define VSTR_IMPLEMENTATION
#include "vstr.h"

const char *cstr = "\
Lorem ipsum dolor sit amet, consectetur adipiscing elit. \
Pellentesque consequat finibus nibh, a lacinia dolor malesuada nec. \
Mauris justo felis, fringilla lacinia mattis sed, tincidunt vel diam. \
Pellentesque luctus ante vitae tellus cursus, nec porta ante congue. \
Lorem ipsum dolor sit amet, consectetur adipiscing elit. \
Aenean posuere vulputate commodo. \
Nam sagittis vestibulum lectus eu ornare. \
Maecenas odio felis, mattis eu massa at, tincidunt sodales libero. \
Pellentesque rhoncus ante urna, non lacinia nunc luctus vel. \
Nulla lacinia facilisis porta. \
Etiam id elit pharetra, eleifend ligula suscipit, laoreet eros. \
Pellentesque commodo, urna non congue eleifend, sapien odio hendrerit felis, in volutpat tellus quam quis eros. \
Nam dictum, odio porta vehicula ornare, lorem elit luctus leo, in finibus justo dolor at enim.\n\
\n\
Aenean velit dolor, hendrerit ut porta quis, volutpat nec quam. \
Interdum et malesuada fames ac ante ipsum primis in faucibus. \
Sed nec egestas erat. \
Integer eu maximus tellus, efficitur accumsan ex. \
Nulla hendrerit in magna quis ornare. \
Praesent felis risus, imperdiet lobortis eleifend non, euismod id lacus. \
Sed eleifend interdum sem, quis scelerisque augue gravida ut. \
Proin vitae tincidunt nibh. \
Curabitur quis mi eu neque rhoncus iaculis ac ac nibh. \
Donec vel sollicitudin dui. \
Donec dapibus tortor at rhoncus gravida. \
Aenean ac arcu dictum, ultrices ligula ac, consectetur diam. \
Fusce imperdiet lectus accumsan volutpat ornare. \
Donec a neque lacinia velit lacinia scelerisque ac nec orci. \
Donec quis egestas est.\
";

const char *cstr2 = "          Need     trim            ";

int
main()
{
  {
    vstr lorem = VSTR(cstr);
    vstr paragraph, sentence;
    int i, j;

    i = 0;
    while ((paragraph = vstr_separate_delim(&lorem, "\n\n")).size > 0)
      {
        j = 0;
            
        printf("Paragraph %d:\n", i);
        while ((sentence = vstr_separate_delim(&paragraph, ". ") ).size > 0)
          {
            printf("\t- Sentence %d:\t"VSTR_FMT"\n", j, VSTR_ARG(sentence));
            ++j;
          }
      
        ++i;
      }
  }

  printf("\n");

  {
    vstr trim = VSTR(cstr2);
    printf("Before trim: \""VSTR_FMT"\"\n", VSTR_ARG(trim));
    
    trim = vstr_trim_right(trim);
    printf("Trim right: \""VSTR_FMT"\"\n", VSTR_ARG(trim));

    trim = vstr_trim_left(trim);
    printf("Trim left: \""VSTR_FMT"\"\n", VSTR_ARG(trim));
  }
  
  return 0;
}

