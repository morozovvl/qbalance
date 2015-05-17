#
# Example spec file for cdplayer app...
#
Summary: One more account platform
Name: qbalance
Version: 0.0.1
Release: 1
License: GPL
Group: Applications/Productivity
Source: https://github.com/morozovvl/qbalance/archive/qbalance-master.zip
URL: https://github.com/morozovvl/qbalance
Distribution: WSS Linux
Vendor: Vladimir A.Morozov
Packager: Vladimir A.Morozov
Icon: /home/vladimir/work/qbalance1/resources/qbalance

%description
It is new account platform

%prep
%setup -q -n qbalance-master

#%files
#/qbalance/src/qbalance

%build
make


