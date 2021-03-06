%define version <version>
%define absoluteInstallRoot ${RPM_BUILD_ROOT}/usr/local
%define installRoot /usr/local
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
/usr/local/bin/qbs -f ../SOURCES/%{name}.qbs profile:Qt5 project.resourcesInstallDir:share/releasemgr project.installRoot:%{installRoot} project.rmmgrVersion:%{version} qbs.installRoot:%{absoluteInstallRoot} release
%files
/usr/local/bin/releasemgr
/usr/local/lib/libsncore.so
/usr/local/share/releasemgr/assets/fhzc/distconst/AliyunDeployment.php
/usr/local/share/releasemgr/assets/fhzc/distconst/NormalDeployment.php
/usr/local/share/releasemgr/assets/fhshop/distconst/AliyunDeployment.php
/usr/local/share/releasemgr/assets/fhshop/distconst/NormalDeployment.php
/usr/local/share/releasemgr/assets/rmmgr/rpmspec.tpl
/usr/local/share/releasemgr/assets/upgrademgr_master/rpmspec.tpl
/usr/local/share/releasemgr/assets/cloudcontroller/rpmspec.tpl
/usr/local/share/releasemgr/assets/cloudcontroller/distconst/AliyunDeployment.php
/usr/local/share/releasemgr/assets/cloudcontroller/distconst/NormalDeployment.php
/usr/local/share/releasemgr/assets/deploysystem/luoxi_rpm_spec.tpl
/usr/local/share/releasemgr/assets/upgradetester/rpmspec.tpl
/usr/local/share/releasemgr/assets/deploysystem/metaserver_rpm_spec.tpl
/usr/local/share/releasemgr/assets/upgrademgr_slave/rpmspec.tpl
/usr/local/share/releasemgr/assets/zhuchao/distconst/AliyunDeployment.php
/usr/local/share/releasemgr/assets/zhuchao/distconst/NormalDeployment.php
