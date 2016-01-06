%define version <version>
%define installRoot ${RPM_BUILD_ROOT}/usr/local
name: upgrademgr_master
Summary: 神恩信息分布式更新服务master分系统
Version: %{version}
License: 郑州神恩信息技术有限公司 sheneninfo License
URL: http://www.sheneninfo.com
Release:1
Group: System Environment/Kernel
BuildArch:x86_64
%description
神恩信息分布式打包工具主控部分，主要负责控制更新子服务器的活动
%build
/usr/local/bin/qbs -f ../SOURCES/%{name}.qbs profile:Qt5 project.resourcesInstallDir:share/upgrademgr_master project.upgrademgrMasterversion:%{version} qbs.installRoot:%{installRoot} release
%files
/usr/local/bin/upgrademgr_master
/usr/local/lib/libumm.so
/usr/local/lib/libsncore.so