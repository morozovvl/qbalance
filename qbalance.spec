#
# Example spec file for cdplayer app...
#
Summary: One more account platform
Name: qbalance
Version: 0.0.1
Release: 1
License: GPL
Group: Applications/Account
Source: https://github.com/morozovvl/qbalance/archive/master.zip
URL: https://github.com/morozovvl/qbalance
Distribution: WSS Linux
Vendor: Vladimir A.Morozov
Packager: Vladimir A.Morozov

%description
It is new account platform

%prep
%setup -q
