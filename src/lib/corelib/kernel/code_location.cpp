#include "code_location.h"
#include <QDataStream>
#include <QSharedData>
#include <QString>
#include <QDir>

namespace releasemgr
{

class CodeLocation::CodeLocationPrivate : public QSharedData
{
public:
   QString filepath;
   int line;
   int column;
};

CodeLocation::CodeLocation()
{}

CodeLocation::CodeLocation(const QString &filepath, int line, int column)
   :d(new CodeLocationPrivate)
{
   d->filepath = filepath;
   d->line = line;
   d->column = column;
}

CodeLocation::~CodeLocation()
{}

CodeLocation::CodeLocation(const CodeLocation &other)
   :d(other.d)
{
   
}

CodeLocation& CodeLocation::operator=(const CodeLocation &other)
{
   d = other.d;
   return *this;
}

QString CodeLocation::getFilePath() const
{
   return d ? d->filepath : QString();
}

int CodeLocation::getLine() const
{
   return d ? d->line : -1;
}

int CodeLocation::getColumn() const
{
   return d ? d->column : -1;
}

bool CodeLocation::isValid() const
{
   return !getFilePath().isEmpty();
}

QString CodeLocation::toString() const
{
   QString str;
   if(isValid()){
      str = QDir::toNativeSeparators(getFilePath());
      QString lineAndColumn;
      if (getLine() > 0 && !str.contains(QRegExp(QLatin1String(":[0-9]+$")))){
         lineAndColumn += QLatin1Char(':') + QString::number(getLine());
      }
      
      if (getColumn() > 0 && !str.contains(QRegExp(QLatin1String(":[0-9]+:[0-9]+$")))){
         lineAndColumn += QLatin1Char(':') + QString::number(getColumn());
      }
      
      str += lineAndColumn;
   }
   return str;
}

bool operator ==(const CodeLocation &lhs, const CodeLocation &rhs)
{
   if(lhs.d == rhs.d){
      return true;
   }
   return lhs.getFilePath() == rhs.getFilePath() && lhs.getLine() == rhs.getLine()
         && lhs.getColumn() == rhs.getColumn();
}

bool operator !=(const CodeLocation &lhs, const CodeLocation &rhs)
{
   return !(lhs == rhs);
}

QDebug operator <<(QDebug debug, const CodeLocation &location)
{
   return debug << location.toString();
}
}//releasemgr