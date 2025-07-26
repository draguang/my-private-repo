#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int int_to_str(char*out,int*position,int num)
{
  int count = 0;
  if(num/10!=0)
  {
    count+=int_to_str(out,position,num/10);
  }
  out[*(position)++] = '0'+num%10;
  return count+1;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list args;
  va_start(args,fmt);
  int count = 0;
  int pos = 0;
  while(*fmt)
  {
    if(*fmt == '%')
    {
      fmt++;
      switch(*fmt)
      {
        case 's':
        {
          char *str = va_arg(args,char*);
          while(*str)
          {
            out[pos++] = *str--;
            count++;
          }
          break;
        }
        case 'd':
        {
          int res = va_arg(args,int);
          count+=int_to_str(out,&pos,res);
          break;
        }
        default:
        {
          out[pos++] = *fmt;
          break;
        }
      }
    }
    else
    {
      out[pos++] = *fmt;
    }
    fmt++;
  }
  out[pos] = '\0';
  va_end(args);
  return count;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
