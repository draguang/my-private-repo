/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

static uint32_t choose(uint32_t num)
{
  return rand()%num;
}

static void gen_num()
{
  uint32_t num = rand()%9+1;
  char num_str[2];
  snprintf(num_str, sizeof(num_str), "%d", num);
    if(strlen(buf)+strlen(num_str)<sizeof(buf)) 
    {
        strcat(buf, num_str);
    }
}

static void gen(char c)
{
  char des[2] = {c,'\0'};
  if(strlen(buf)+1<sizeof(buf))
    strcat(buf,des);
}

static void gen_rand_op()
{
  if (buf[0] != '\0' && strchr("+-*/", buf[strlen(buf)-1]))
    return;
  char op[4] = {'+','-','*','/'};
  char des[2] = {op[choose(4)], '\0'};
  if(strlen(buf)+1<sizeof(buf))
    strcat(buf,des);
}

static void gen_rand_expr(int depth) {
  if(depth>10)
  {
    gen_num();
    return;
  }
  switch (choose(3)) {
    case 0: 
    if(buf[0] == '\0' || !isdigit(buf[strlen(buf)-1])) {
        gen_num();
    }
    break;
    case 1: 
    if(buf[0] == '\0' || 
       strchr("+-*/(", buf[strlen(buf)-1])) {
        gen('(');
        gen_rand_expr(depth+1);
        gen(')');
    }
    break;
    default:
    gen_rand_expr(depth+1);
    if(buf[0] != '\0' && !strchr("+-*/(", buf[strlen(buf)-1])) 
    {
        gen_rand_op();
        gen_rand_expr(depth+1);
    }
    break;
  }
}

static int is_division_by_zero() 
{
  char *p = buf;
  while (*p) 
  {
    if (*p == '/' && *(p + 1) == '0') 
    {
      return 1;
    }
    p++;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    memset(buf, '\0', sizeof(buf));
    gen_rand_expr(0);
    if(is_division_by_zero())
    {
      do{
        memset(buf, '\0', sizeof(buf));
        gen_rand_expr(0);
      }while(is_division_by_zero());
    }
    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
