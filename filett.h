#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student_data {
  int Mxt;
  char Hten[25];
  float Dxt;
  char Sohieu[5];
} stdata;

typedef struct Stdata_pos {
  int Mxt;
  int pos;
} stpos;

void clean_newLine(char value[]) {
  char *newlinePos = strchr(value, '\n');
  if (newlinePos != NULL) {
    *newlinePos = '\0';
  }
}
void clean_stdin() {
  printf("Clean stdin,Enter to continue...\n");
  int c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}

void initial_file(char fileName[]) {
  FILE *f;
  f = fopen(fileName, "wb");
  fclose(f);
  printf("created\n");
}

void NhapBangDiem(char fileName[]) {
  FILE *f;
  f = fopen(fileName, "wb");
  if (f == NULL) {
    printf("file error");
    exit(1);
  }

  while (1) {
    stdata s;
    printf("\nMxt\n");
    scanf("%d", &s.Mxt);
    if (s.Mxt == 0) {
      break;
    }
    clean_stdin();

    printf("\nName:\n");
    fgets(s.Hten, 25, stdin);
    clean_stdin();
    clean_newLine(s.Hten);

    printf("%s", s.Hten); // for debug
    printf("\nScore\n");
    scanf("%f", &s.Dxt);
    clean_stdin();
    printf("\nSoHieu\n");
    fgets(s.Sohieu, 5, stdin);
    clean_stdin();
    clean_newLine(s.Sohieu);
    printf("%s", s.Sohieu); // for debug
    if (strcmp(s.Sohieu, "***") == 1) {
      break;
    }
    printf("\n%d %s %f %s \n", s.Mxt, s.Hten, s.Dxt, s.Sohieu);
    fwrite(&s, sizeof(stdata), 1, f);
    printf("\nWrite in ...\n");
  }
  fclose(f);
}

// Tim theo Mxt
void Mxt_search(char fileDaTa[]) {
  int target;
  printf("\nMxt search:   ");
  scanf("%d", &target);
  stdata S;
  FILE *db;
  db = fopen(fileDaTa, "rb");
  while (fread(&S, sizeof(stdata), 1, db)) {
    if (S.Mxt == target) {
      printf("%d %s %.2f %s", S.Mxt, S.Hten, S.Dxt, S.Sohieu);
    }
  }
  printf("\ndone");
  fclose(db);
}

// Tim theo SoHieu
void SoHieu_search(char fileDaTa[]) {
  char target[5];
  printf("\nSohieu search:   ");
  fgets(target, 5, stdin);
  clean_newLine(target);
  clean_stdin();
  stdata S;
  FILE *db;
  db = fopen(fileDaTa, "rb");
  while (fread(&S, sizeof(stdata), 1, db)) {
    if (strcmp(S.Sohieu, target) == 0) {
      printf("%d %s %.2f %s", S.Mxt, S.Hten, S.Dxt, S.Sohieu);
    }
  }
  printf("\ndone");
  fclose(db);
}

// hien danh sach
void Hien_danh_sach(char fileDaTa[]) {
  stdata S;
  FILE *db;
  db = fopen(fileDaTa, "rb");
  while (fread(&S, sizeof(stdata), 1, db)) {
    printf("%d %s %.2f %s\n", S.Mxt, S.Hten, S.Dxt, S.Sohieu);
  }
  printf("\ndone");
  fclose(db);
}

// Lap bao cao
void print_info(char fileDaTa[], char FileResault[]) {
  stdata S;
  int count = 0;
  FILE *db, *rs;
  db = fopen(fileDaTa, "rb");
  rs = fopen("resault.txt", "w");
  fprintf(rs, "\n\t DANH SACH TRUNG TUYEN \t\n");
  fprintf(rs, "\nSTT,HOTEN,DIEM,SOHIEU");
  while (fread(&S, sizeof(stdata), 1, db)) {
    count++;
    if (S.Dxt > 5) {
      fprintf(rs, "\n %d,%s,%f.1,%s", S.Mxt, S.Hten, S.Dxt, S.Sohieu);
    }
  }
  fprintf(rs, "\n Tong sinh vien trung tuyen : %d\n", count);
  fprintf(rs, "end");
  printf("Done!");
  fclose(rs);
  fclose(db);
}

// doc tep va in ra maso sv va vt
// doc ds sv
// gan vt
// ghi vao file chisoMXT.idx
void get_stdId_pos_file(char FileData[], char FileOutput[]) {
  stdata Std;
  FILE *fd, *fo;
  fd = fopen(FileData, "rb");
  fo = fopen(FileOutput, "wb");
  int count = 0;
  while (fread(&Std, sizeof(stdata), 1, fd)) {
    count++;
    stpos stdpos;
    stdpos.Mxt = Std.Mxt;
    stdpos.pos = count;
    fwrite(&stdpos, sizeof(stpos), 1, fo);
  }
  fclose(fd);
  fclose(fo);
}

void showoutput(char FileOpen[]) {
  FILE *f;
  f = fopen(FileOpen, "rb");
  if (f == NULL) {
    printf("File not found");
  }

  stpos sp;
  while (fread(&sp, sizeof(stpos), 1, f)) {
    printf("\n%d %d", sp.Mxt, sp.pos);
  }
  fclose(f);
}

// lay masv cho vao mang
// sap xep mang
// in mang vao file

void sapxep_stpos(char IDfile[]) {
  FILE *f;
  f = fopen(IDfile, "rb");
  int count, i = 0;
  stpos s, slist[50];
  while (fread(&s, sizeof(stpos), 1, f)) {
    slist[i] = s;
    i++;
  }
  printf("%d\n", i);
  for (int j = 0; j < i - 1; j++) {
    for (int k = 0; k < i - j - 1; k++) {
      if (slist[k].Mxt < slist[k + 1].Mxt) {
        stpos temp = slist[k];
        slist[k] = slist[k + 1];
        slist[k + 1] = temp;
        printf("found and sort\n");
      }
    }
  }
  fclose(f);
  f = fopen(IDfile, "wb");
  for (int j = 0; j < i; j++) {
    fwrite(&slist[j], sizeof(stpos), 1, f);
  }
  printf("done");
  fclose(f);
}

// nhap mxt cho biet kq
// tim kiem mxt trong chisomxt.idx
// lay vt tron file idx de  tim thong so sv

void search_by_id(char IDfile[], char DataFile[]) {
  FILE *id, *db;
  id = fopen(IDfile, "rb");
  db = fopen(DataFile, "rb");
  stdata sdata;
  stpos spos;

  printf("\nID: ");
  int n;
  scanf("%d", &n);
  fseek(id, 0, SEEK_SET);
  while (fread(&spos, sizeof(stpos), 1, id)) {
    if (spos.Mxt == n) {
      fseek(db, ((spos.pos - 1) * sizeof(stdata)), SEEK_SET);
      fread(&sdata, sizeof(stdata), 1, db);
      printf("%d %s", sdata.Mxt, sdata.Hten);
      break;
    }
  }
  fclose(id);
  fclose(db);
}
