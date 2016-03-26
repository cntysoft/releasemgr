%define version <version>
%define absoluteInstallRoot ${RPM_BUILD_ROOT}/usr/local
%define installRoot /usr/local
name: upgrade_tester
Summary: 神恩信息升级测试模拟系统
Version: %{version}
License: 郑州神恩信息技术有限公司 sheneninfo License
URL: http://www.sheneninfo.com
Release:1
Group: System Environment/Kernel
BuildArch:x86_64
%description
这个工具主要用于发布升级前进行测试，模拟upgrade script运行
%build
/usr/local/bin/qbs -f ../SOURCES/%{name}.qbs profile:Qt5 project.resourcesInstallDir:share/upgradetester project.upgradeTesterVersion:%{version} project.installRoot:%{installRoot} qbs.installRoot:%{absoluteInstallRoot} release
%files
/usr/local/bin/upgrade_tester
/usr/local/lib/libut.so
/usr/local/lib/libsncore.so