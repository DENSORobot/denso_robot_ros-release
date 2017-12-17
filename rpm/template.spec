Name:           ros-kinetic-denso-robot-control
Version:        3.0.2
Release:        0%{?dist}
Summary:        ROS denso_robot_control package

Group:          Development/Libraries
License:        MIT
URL:            http://ros.org/wiki/denso_robot_control
Source0:        %{name}-%{version}.tar.gz

Requires:       ros-kinetic-bcap-core
Requires:       ros-kinetic-bcap-service
Requires:       ros-kinetic-controller-manager
Requires:       ros-kinetic-denso-robot-core
Requires:       ros-kinetic-hardware-interface
Requires:       ros-kinetic-joint-limits-interface
Requires:       ros-kinetic-roscpp
Requires:       ros-kinetic-std-msgs
Requires:       ros-kinetic-transmission-interface
BuildRequires:  ros-kinetic-bcap-core
BuildRequires:  ros-kinetic-bcap-service
BuildRequires:  ros-kinetic-catkin
BuildRequires:  ros-kinetic-controller-manager
BuildRequires:  ros-kinetic-denso-robot-core
BuildRequires:  ros-kinetic-hardware-interface
BuildRequires:  ros-kinetic-joint-limits-interface
BuildRequires:  ros-kinetic-roscpp
BuildRequires:  ros-kinetic-std-msgs
BuildRequires:  ros-kinetic-transmission-interface

%description
The denso robot control package includes a node for controlling DENSO robot
controllers with MoveIt!.

%prep
%setup -q

%build
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree that was dropped by catkin, and source it.  It will
# set things like CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/kinetic/setup.sh" ]; then . "/opt/ros/kinetic/setup.sh"; fi
mkdir -p obj-%{_target_platform} && cd obj-%{_target_platform}
%cmake .. \
        -UINCLUDE_INSTALL_DIR \
        -ULIB_INSTALL_DIR \
        -USYSCONF_INSTALL_DIR \
        -USHARE_INSTALL_PREFIX \
        -ULIB_SUFFIX \
        -DCMAKE_INSTALL_LIBDIR="lib" \
        -DCMAKE_INSTALL_PREFIX="/opt/ros/kinetic" \
        -DCMAKE_PREFIX_PATH="/opt/ros/kinetic" \
        -DSETUPTOOLS_DEB_LAYOUT=OFF \
        -DCATKIN_BUILD_BINARY_PACKAGE="1" \

make %{?_smp_mflags}

%install
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree that was dropped by catkin, and source it.  It will
# set things like CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/kinetic/setup.sh" ]; then . "/opt/ros/kinetic/setup.sh"; fi
cd obj-%{_target_platform}
make %{?_smp_mflags} install DESTDIR=%{buildroot}

%files
/opt/ros/kinetic

%changelog
* Sun Dec 17 2017 DENSO WAVE INCORPORATED <denso_robot_soft@denso-wave.co.jp> - 3.0.2-0
- Autogenerated by Bloom

* Fri Dec 08 2017 DENSO WAVE INCORPORATED <denso_robot_soft@denso-wave.co.jp> - 3.0.1-0
- Autogenerated by Bloom

