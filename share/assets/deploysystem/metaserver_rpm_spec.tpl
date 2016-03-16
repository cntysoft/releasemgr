%define version <version>
%define installRoot ${RPM_BUILD_ROOT}/usr/local
name: meta_server
Summary: 神恩信息分布式部署 metaserver 主系统
Version: %{version}
License: 郑州神恩信息技术有限公司 sheneninfo License
URL: http://www.sheneninfo.com
Release:1
Group: System Environment/Kernel
BuildArch:x86_64
%description
神恩信息分布式部署系统主控部分，主要负责接受连接，分发任务
%build
/usr/local/bin/qbs -f ../SOURCES/%{name}.qbs profile:Qt5 project.resourcesInstallDir:share/deploysystem project.msversion:%{version} qbs.installRoot:%{installRoot} release
%files
/usr/local/bin/meta_server
/usr/local/lib/libmserver.so
/usr/local/lib/libsncore.so
/usr/local/lib/libmsservice.so