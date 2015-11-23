#include "terminal.h"
#include <QByteArray>
#include <iostream>

namespace releasemgr 
{

const QMap<TerminalColor, int> Terminal::colorMap{
   {TerminalColor::Default, 39},
   {TerminalColor::Black, 30},
   {TerminalColor::Red, 31},
   {TerminalColor::Green, 32},
   {TerminalColor::Yellow, 33},
   {TerminalColor::Blue, 34},
   {TerminalColor::Magenta, 35},
   {TerminalColor::Cyan, 36},
   {TerminalColor::LightGray, 37},
   {TerminalColor::DarkGray, 90},
   {TerminalColor::LightRed, 91},
   {TerminalColor::LightGreen, 92},
   {TerminalColor::LightYellow, 93},
   {TerminalColor::LightBlue, 94},
   {TerminalColor::LightMagenta, 95},
   {TerminalColor::LightCyan, 96},
   {TerminalColor::White, 97}
};

QByteArray Terminal::getColorText(const char* str, TerminalColor color, bool underline, bool blink)
{
   QByteArray ret("\e[");
   QStringList codesList;
   if(underline){
      codesList << QByteArray::number(UNDERLINE_CODE);
   }
   if(blink){
      codesList << QByteArray::number(BLINK_CODE);
   }
   codesList << QString::number(colorMap[color]);
   ret.append(codesList.join(';'));
   ret.append('m');
   ret.append(str);
   ret.append("\e[0m");
   return ret;
}

void Terminal::writeText(const char *str, TerminalColor color, bool underline, bool blink)
{
   std::cout << getColorText(str, color, underline, blink).constData() << std::flush;
}

}