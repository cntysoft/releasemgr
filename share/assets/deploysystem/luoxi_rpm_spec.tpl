%define version <version>
%define absoluteInstallRoot ${RPM_BUILD_ROOT}/usr/local
%define installRoot /usr/local
name: luoxi
Summary: 神恩信息分布式部署系统slave分系统
Version: %{version}
License: 郑州神恩信息技术有限公司 sheneninfo License
URL: http://www.sheneninfo.com
Release:1
Group: System Environment/Kernel
BuildArch:x86_64
%description
神恩信息分布式运维从系统，主要执行主系统发过来的请求
%build
/usr/local/bin/qbs -f ../SOURCES/%{name}.qbs profile:Qt5 project.resourcesInstallDir:share/deploysystem project.luoxiVersion:%{version} project.installRoot:%{installRoot} qbs.installRoot:%{absoluteInstallRoot} release
%files
/usr/local/bin/luoxi
/usr/local/lib/liblx.so
/usr/local/lib/libsncore.so
/usr/local/lib/liblxservice.so
/usr/local/share/deploysystem/conf/nginx_conf.tpl