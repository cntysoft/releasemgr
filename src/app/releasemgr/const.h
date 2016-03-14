#ifndef RELEASEMGR_CONST_H
#define RELEASEMGR_CONST_H
#include <QChar>
#include <QDir>

namespace releasemgr 
{

extern const char* CFG_FILE_NAME;
extern const char* CFG_GROUP_FHZC;
extern const char* CFG_GROUP_FHSHOP;
extern const char* CFG_GROUP_GLOBAL;
extern const char* CFG_GROUP_RMMGR;
extern const char* CFG_GROUP_UPGRADEMGR_MASTER;
extern const char* CFG_GROUP_UPGRADEMGR_SLAVE;
extern const char* CFG_GROUP_CLOUDCONTROLLER;
extern const char* CFG_GROUP_METASERVER;
extern const char* CFG_GROUP_LUOXI;

const int DEPLOY_TYPE_PRODUCT = 4;
const int DEPLOY_TYPE_DEBUG = 5;

const QChar DS = QDir::separator();

}//releasemgr

#endif // RELEASEMGR_CONST_H