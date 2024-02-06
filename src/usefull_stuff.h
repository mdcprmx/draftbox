// soo this is kind-a my custom library lmao

void open_file_with check() {
  FILE *fname;
  if ((fname = fopen("test.txt", "r")) == NULL) {
    printf("error cannot open file.\n");
    exit(1);
  }
}
