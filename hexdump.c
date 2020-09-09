#include <stdlib.h>
#include <stdio.h>

void removeNewLines(char *s);

#define LINELENGTH 16
#define HALFLINE   8


int main(int argc, char* argv[]){
  if (argc != 2){
    return EXIT_FAILURE;
  }

  char* Filename = argv[1];
  FILE* File = fopen(Filename, "r");

  fseek(File, 0, SEEK_END);

  size_t FileSize = ftell(File);

  fseek(File, 0, SEEK_SET);
  char buffer[FileSize];

  fread(buffer, FileSize, 1, File);

  removeNewLines(buffer);

  for (unsigned counter = 0, c2 = 1; counter < FileSize; counter++, c2++){
    if(counter % LINELENGTH == 0) {
      printf("%.08x  ", counter);
    }
    printf("%02x ", buffer[counter]);
    if (counter % HALFLINE == 0 && counter % LINELENGTH != 0){
      printf(" ");
    }
    if (c2 % LINELENGTH == 0 ) {
        printf("|%.16s|\n", &buffer[c2-LINELENGTH]);
    } else if (c2 == FileSize-1){
      if (c2 % LINELENGTH != 0){
        for (unsigned i = 0; i != (LINELENGTH - (c2 % LINELENGTH)); i++){
          printf("   ");
        }
        printf("|%.16s|\n", &buffer[c2-LINELENGTH]);
      }
    }
  }
  return EXIT_SUCCESS;
}

void removeNewLines(char *s){
  while (*s != 0){
    if (*s == '\n'){
      *s = ' ';
    }
    s++;
  }
}
