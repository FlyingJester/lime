export EXEFORMAT=elf
export TOOLBUILD=x86_64
TT=$(TOOLBUILD)-$(EXEFORMAT)

export XCC=$(TT)-gcc
export XCXX=$(TT)-g++
export XAR=$(TT)-ar
export XRANLIB=$(TT)-ranlib
export XLINK=$(TT)-ld
export XSTRIP=$(TT)-strip
export XAS=yasm

export ARCHTARGET=i386
export TARGETBITS=32

export XCCFLAGS=-Os -ffreestanding -Wall -Wextra -ansi -pedantic -Werror -m$(TARGETBITS) -I$(PDIR)/klime
export XLINKFLAGS=-nostdlib -nostdinc -m$(EXEFORMAT)_$(ARCHTARGET)
export XASFLAGS=-f$(EXEFORMAT)$(TARGETBITS) -Worphan-labels
export XCXXFLAGS=$(XCCFLAGS) -fno-exceptions -fno-rtti -std=c++98
