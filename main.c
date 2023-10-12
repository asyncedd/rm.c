#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void removeFile(const char *filePath) {
  int status = remove(filePath);
  if (status != 0) {
    fprintf(stderr, "[ERROR] Can't remove %s\n", filePath);
  }
}

bool checkIfReadonly(const char *filePath) {
  return access(filePath, R_OK) != 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [FILE...]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {
    if (checkIfReadonly(argv[i])) {
      char choice;
      printf("The file %s is read-only. Do you want to delete it? (y/n): ",
             argv[i]);
      scanf(" %c", &choice);

      if (choice != 'y' && choice != 'Y') {
        printf("Deletion of %s aborted.\n", argv[i]);
        continue;
      }
    }
    removeFile(argv[i]);
  }

  return 0;
}
