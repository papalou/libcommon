#!/bin/bash

config_file="../../cross_toolchain.config"
defconfig_file="../../cross_toolchain.defconfig"


if [ ! -e ${config_file} ]; then
	printf "${config_file} didn't exist, create it\n"
	cp ${defconfig_file} ${config_file}
fi

toolchain_path=$(grep "TOOLCHAIN_PATH" ${config_file} | awk -F'\"' '{print $2}')
toolchain_prefix=$(grep "TOOLCHAIN_PRFIX" ${config_file} | awk -F'\"' '{print $2}')
sysroot=$(grep "SYSROOT" ${config_file} | awk -F'\"' '{print $2}')
arch=$(grep "ARCH" ${config_file} | awk -F'\"' '{print $2}')

#Relocate toolchain folder
toolchain_path="../../${toolchain_path}"
sysroot="../../${sysroot}"

export TOOLCHAIN_PATH=${toolchain_path}
export TOOLCHAIN_PRFIX=${toolchain_prefix}

export LD_LIBRARY_PATH=$TOOLCHAIN_PATH/lib
export PATH=$TOOLCHAIN_PATH/bin:$PATH

make ARCH=$arch CROSS_COMPILE=$TOOLCHAIN_PRFIX SYSROOT=${sysroot} $1
