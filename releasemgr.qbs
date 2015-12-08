import qbs

Project
{
   minimumQbsVersion: "1.4.2"
   qbsSearchPaths:["qbs-resources"]
   property bool enableUnitTests: false
   property bool enableRPath: true
   property bool installApiHeaders: true
   property string libDirName: "lib"
   property string appInstallDir: "bin"
   property string libInstallDir: libDirName
   property string resourcesInstallDir: "share"
   property string rmmgrVersion: "0.0.1"
   property stringList libRPaths: {
      if (!enableRPath){
         return undefined;
      }else{
         return ["$ORIGIN/../" + libDirName];
      }
   }
   references: [
      "src/src.qbs",
      "share/share.qbs"
   ]
}
