# SPDX-License-Identifier: GPL-2.0

$(info "CONFIG_MITEE_SUPPORT=$(CONFIG_MITEE_SUPPORT)")

$(info "Welcome to MiTee...")
obj-m += mitee.o
mitee-y :=	core.o \
         	call.o \
			rpc.o \
			supp.o \
			shm_pool.o \
			device.o \
			bench.o \
			mitee_memlog.o
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/
