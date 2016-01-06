%define version <version>
%define installRoot ${RPM_BUILD_ROOT}/usr/local
name: cloudcontroller
Summary: 神恩信息发行云控制终端系统
Version: %{version}
License: 郑州神恩信息技术有限公司 sheneninfo License
URL: http://www.sheneninfo.com
Release:1
Group: System Environment/Kernel
BuildArch:x86_64
%description
神恩信息分布式管理系统控制终端
%build
/usr/local/bin/qbs -f ../SOURCES/cloud_controller.qbs profile:Qt5 project.resourcesInstallDir:share/cloudcontroller project.ccVersion:%{version} qbs.installRoot:%{installRoot} release
%files
/usr/local/bin/cloudcontroller
/usr/local/bin/cloudcontroller-gui
/usr/local/lib/libsncore.so
/usr/local/lib/libcloudcontroler.so
