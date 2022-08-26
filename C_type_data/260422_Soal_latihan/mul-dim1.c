#include <stdio.h>
#include <string.h>

int main()
{
  // buat data array string
  char strings[10][100] =
  {
    "demonstration",
    "apple",
    "joyful",
    "friends",
    "battle",
    "incredible",
    "example",
    "great",
    "happy",
    "city",
  };
  
  // length untuk array
  int length = 10;
   
  // temp char array akan digunakan untuk swap aray
  char temp[100];
  
  for (int i = 0; i < (length - 1); i++)
  {
    // posisi dari minimum string (alphabetically minimum)
    int j_min = i;
    for (int j = i + 1; j < length; j++)
      if (strcmp(strings[j], strings[j_min]) < 0)
        j_min = j;
    
    // jika yang diperlukan, swap the minimum string dengan string ke index i
    if (j_min != i)
    {
      strcpy(temp, strings[i]);
      strcpy(strings[i], strings[j_min]);
      strcpy(strings[j_min], temp);
    }
  }
  
  // output array strings
  for (int i = 0; i < length; i++)
    printf("%s\n", strings[i]);

  return 0;
}

// bagaimana string membandingkan fungsi yang ada
//
// strcmp(s1,s2)
//
// < 0  first non-matching char memiliki nilai rendah pada s1 dari s2
// 0    sama dengan strings
// > 0  first non-matching char memiliki nilai tinggi pada s1 dari s2
//
