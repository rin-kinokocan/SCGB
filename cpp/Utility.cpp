#include "class/define.h"
namespace scgb{
  namespace Util{
    cChar make_cChar(wchar_t in,int attr){
      //make cchar_t from single wchar_t
      cChar re;
      re.chars[0]=in;
      re.chars[1]='\0';
      re.attr=attr;
      return re;
    }
    wchar_t cCharToWchar(cChar c){
      return c.chars[0];
    }
  }
}
