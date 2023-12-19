#include "filett.h"
#include <stdio.h>
#include <string.h>
// khai bao cau truc
// tao tep nhi phan
// void initial_file(char fileName[]) {
//   FILE *f;
//   f = fopen(fileName, "wb");
//   fclose(f);
// }
// tim kiem theo so lieu
// lop ds trung tuyen

int main(int argc, char *argv[]) {
  // initial_file("student_db.dbo");
  // NhapBangDiem("student_db.dbo");
  // print_info("student_db.dbo", "student_resault.txt");
  Hien_danh_sach("student_db.dbo");
  // Mxt_search("student_db.dbo");
  // SoHieu_search("student_db.dbo");
  // get_stdId_pos_file("student_db.dbo", "chisoMxt.idx");
  showoutput("chisoMxt.idx");
  search_by_id("chisoMxt.idx", "student_db.dbo");
  // sapxep_stpos("chisoMxt.idx");
  // showoutput("chisoMxt.idx");
  return 0;
}
