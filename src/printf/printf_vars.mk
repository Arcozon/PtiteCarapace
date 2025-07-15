S_SRC_GA_FPRINTF =  my_printf.c  write_buff.c  format/conversion.c  format/flags.c  format/precision.c  conversion/fill_format.c
S_SRC_GA_FPRINTF += format/width.c  conversion/cpy_uint_b10_to_buff.c  conversion/cpy_ulong_b16_to_buff.c  conversion/s.c
S_SRC_GA_FPRINTF += conversion/x.c  conversion/p.c  conversion/percent.c  conversion/c.c  conversion/di.c  conversion/u.c
D_SRC_GA_FPRINTF =  ga_fprintf/
SRC_GA_FRPINTF   = $(addprefix $(D_SRC_GA_FPRINTF), $(S_SRC_GA_FPRINTF))

SSRC_PRINTF	=	format.c \
			utils.c \
			utils2.c \
			print.c \
			parsing.c \
			get_len.c \
			get_len2.c \
			align.c \
			get_size.c \
			len.c\
			main_bonus.c\

SRC_PRINTF = $(addprefix srcs/, $(SSRC_PRINTF)) \
			$(SRC_GA_FRPINTF) 
