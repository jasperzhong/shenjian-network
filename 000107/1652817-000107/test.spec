Name:		test
Version:	1652817
Release:	zyc
Summary:	test
License:	GPL

Source0:	%{name}-%{version}.tar.bz2

%description
1652817 zyc

%prep
%setup -q

%build
make

%install
rm -rf %{buildroot}
%{__install} -d %{buildroot}/usr/sbin
%{__install} -d %{buildroot}/usr/lib64
%{__install} -d %{buildroot}/etc
%{__install} -d %{buildroot}/usr/1652817
%{__install} -D test-1652817.service %{buildroot}/etc/systemd/system/test-1652817.service
make DESTDIR=%{buildroot} install

%pre
echo 准备安装test-1652817
mkdir -p /usr/1652817

%post
echo 安装完成test-1652817

%preun
echo 准备卸载test-1652817

%postun
echo 完成卸载test-1652817
if [ -d "/usr/1652817" ]; then if [ "`ls -A /usr/1652817`" = "" ]; then `rm -rf /usr/1652817`; fi;fi;

%clean
rm -rf %{buildroot}

%files
/etc/1652817.conf
/usr/sbin/test-1652817
/usr/lib64/lib1652817.so
/usr/1652817/1652817.dat
/etc/systemd/system/test-1652817.service
