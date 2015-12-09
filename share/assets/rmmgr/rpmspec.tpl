%define version <version>
%define installRoot ${RPM_BUILD_ROOT}/usr/local
name: releasemgr
Summary: 神恩信息发行打包系统
Version: %{version}
License: 郑州神恩信息技术有限公司 sheneninfo License
URL: http://www.sheneninfo.com
Release:1
Group: System Environment/Kernel
BuildArch:x86_64
%description
神恩信息技术官方打包发行工具，暂时负责打包凤凰筑巢系统和凤凰筑巢商家版系统已经发行系统本身
%build
/usr/local/bin/qbs -f ../SOURCES/%{name}.qbs profile:Qt5 project.resourcesInstallDir:share/releasemgr project.rmmgrVersion:%{version} qbs.installRoot:%{installRoot} release
%files
/usr/local/bin/releasemgr
/usr/local/lib/libreleasemgrcore.so
/usr/local/share/releasemgr/assets/fhzc/distconst/AliyunDeployment.php
/usr/local/share/releasemgr/assets/fhzc/distconst/NormalDeployment.php
/usr/local/share/releasemgr/assets/rmmgr/rpmspec.tpl