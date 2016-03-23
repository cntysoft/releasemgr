%define version <version>
%define absoluteInstallRoot ${RPM_BUILD_ROOT}/usr/local
%define installRoot /usr/local
name: upgrademgr_slave
Summary: 神恩信息分布式更新服务slave分系统
Version: %{version}
License: 郑州神恩信息技术有限公司 sheneninfo License
URL: http://www.sheneninfo.com
Release:1
Group: System Environment/Kernel
BuildArch:x86_64
%description
神恩信息分布式打包工具主控部分，主要负责控制更新子服务器的活动
%build
/usr/local/bin/qbs -f ../SOURCES/%{name}.qbs profile:Qt5 project.resourcesInstallDir:share/upgrademgr_slave project.installRoot:%{installRoot} project.upgrademgrSlaveVersion:%{version} qbs.installRoot:%{absoluteInstallRoot} release
%files
/usr/local/bin/upgrademgr_slave
/usr/local/lib/libums.so
/usr/local/lib/libsncore.so
/usr/local/lib/libumsservice.so