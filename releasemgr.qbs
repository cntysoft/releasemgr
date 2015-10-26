import qbs

Project
{
   minimumQbsVersion: "1.4"
   qbsSearchPaths:["qbs-resources"]
   property bool enableUnitTests: false
   property bool enableRPath: true
   property bool installApiHeaders: true
   property string libDirName: "lib"
   property string appInstallDir: "bin"
   property string libInstallDir: libDirName
   property stringList libRPaths: {
      if (!enableRPath){
         return undefined;
      }else{
         return ["$ORIGIN/../" + libDirName];
      }
   }
   references: [
      "src/src.qbs"
   ]
}
