Summary: gigz is a parallel implementation of gzip for modern macOS machines
Name: gigz
Version: 1.0
Release: 1
Source0: %{name}-%{version}.tar.gz
License: zlib
Group: Applications/Tools
Packager: Sebastian Ritter <duncan@duncanbrown.org>
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
URL: http://www.zlib.net/pigz

%description
gigz, which stands for parallel implementation of gzip, is a fully functional replacement for gzip that exploits modern macOS hardware to the hilt when compressing data. pigz was written by Mark Adler, and uses the zlib and pthread libraries. gigz based on pigz.

%clean
rm -rf $RPM_BUILD_ROOT
%prep
mkdir -p $RPM_BUILD_ROOT

%setup -q
%build
make
mkdir -p ${RPM_BUILD_ROOT}/usr/bin
mkdir -p ${RPM_BUILD_ROOT}/usr/man/man1
mv gigz unpigz ${RPM_BUILD_ROOT}/usr/bin
mv gigz.1 ${RPM_BUILD_ROOT}/usr/man/man1

%files
%defattr(-,root,root)
/usr/bin/gigz
/usr/bin/ungigz
%doc
/usr/man/man1/gigz.1
