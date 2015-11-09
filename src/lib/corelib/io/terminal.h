#ifndef TERMINAL
#define TERMINAL

#include <QMap>
#include "global/global.h"


namespace releasemgr
{

enum class TerminalColor
{
   Default,
   Black,
   Red,
   Green,
   Yellow,
   Blue,
   Magenta,
   Cyan,
   LightGray,
   DarkGray,
   LightRed,
   LightGreen,
   LightYellow,
   LightBlue,
   LightMagenta,
   LightCyan,
   White
};

class RMGR_EXPORT Terminal
{
   
public:
   static QByteArray getColorText(const char* str, TerminalColor color, bool underline = false, bool blink = false);
   static void writeText(const char* str, TerminalColor color, bool underline = false, bool blink = false);
protected:
   const static QMap<TerminalColor, int> colorMap;
   const static int BOLD_CODE = 1;
   const static int UNDERLINE_CODE = 4;
   const static int BLINK_CODE = 5;
   const static int REVERSE_CODE = 7;
};

}//releasemgr

#endif // TERMINAL

