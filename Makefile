#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchedal- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/06 14:30:26 by jchedal-          #+#    #+#              #
#    Updated: 2018/03/08 15:43:36 by jchedal-         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

################################## DIRECTORIES ################################# 

ASM_DIR = asm_dir/
D_ASM_DIR = d_asm_dir/
COREWAR_DIR = corewar_dir/

SRCS = srcs/
INCS = includes/
OBJS = objs/

################################### PROGRAMS ###################################

ASM = asm
D_ASM = d_asm
COREWAR = corewar

##################################### LIBFT ####################################

LIB = libft/
LIBFT = $(LIB)libft.a
LIBFLAGS = -L$(LIB) -lft

###################################### ASM #####################################

ASM_PATH = $(ASM_DIR)$(SRCS)
I_ASM_PATH = $(ASM_DIR)$(INCS)
O_ASM_PATH = $(ASM_DIR)$(OBJS)

ASM_SRCS = assign_instr.c\
		   check_instr.c\
		   error_handler.c\
		   extract_label.c\
		   get_file.c\
		   get_header.c\
		   get_instr.c\
		   get_labels.c\
		   get_opcode.c\
		   get_params_size.c\
		   get_values.c\
		   initializing.c\
		   main.c\
		   parse_instr.c\
		   print.c\
		   utilities.c

ASM_OBJS = $(addprefix $(addprefix $(ASM_DIR), $(OBJS)), $(ASM_SRCS:.c=.o)) 

##################################### D_ASM ####################################

D_ASM_PATH = $(D_ASM_DIR)$(SRCS)
I_D_ASM_PATH = $(D_ASM_DIR)$(INCS)
O_D_ASM_PATH = $(D_ASM_DIR)$(OBJS)

D_ASM_SRCS = main.c\
			ft_error.c\
			ft_free.c\
			ft_coding_byte.c\
			ft_filup_arg.c\
			ft_opcode.c\
			ft_init.c\
			ft_put_in_buff.c

D_ASM_OBJS = $(addprefix $(addprefix $(D_ASM_DIR), $(OBJS)), $(D_ASM_SRCS:.c=.o)) 

#################################### COREWAR ###################################

COREWAR_PATH = $(COREWAR_DIR)$(SRCS)
I_COREWAR_PATH = $(COREWAR_DIR)$(INCS)
O_COREWAR_PATH = $(COREWAR_DIR)$(OBJS)

COREWAR_SRCS = add_sub.c\
			   aff.c\
			   and_or_xor.c\
			   argv.c\
			   check.c\
			   color.c\
			   end.c\
			   fork_lfork.c\
			   free.c\
			   get_champ.c\
			   get_val.c\
			   init.c\
			   ld_lld.c\
			   ldi_lldi.c\
			   lib.c\
			   live.c\
			   main.c\
			   number.c\
			   op.c\
			   play.c\
			   proc.c\
			   st.c\
			   sti.c\
			   usage.c\
			   use.c\
			   value.c\
			   zjmp.c


COREWAR_OBJS = $(addprefix $(addprefix $(COREWAR_DIR), $(OBJS)), $(COREWAR_SRCS:.c=.o)) 

################################### COMPILING ##################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(ASM) $(D_ASM) $(COREWAR)

libft: $(LIBFT)

$(LIBFT):
	make -C $(LIB) > /dev/null || TRUE

$(ASM): $(LIBFT) $(ASM_OBJS)
	$(CC) $(CFLAGS) $(ASM_OBJS) -o $@ $(LIBFLAGS)

$(O_ASM_PATH)%.o: $(ASM_PATH)%.c
	mkdir -p $(O_ASM_PATH)
	$(CC) $(CFLAGS) $(INC_FLAG) -o $@ -c $< -I $(I_ASM_PATH) -I $(LIB)$(INCS)

$(D_ASM): $(LIBFT) $(D_ASM_OBJS)
	$(CC) $(CFLAGS) $(D_ASM_OBJS) -o $@ $(LIBFLAGS)

$(O_D_ASM_PATH)%.o: $(D_ASM_PATH)%.c
	mkdir -p $(O_D_ASM_PATH)
	$(CC) $(CFLAGS) $(INC_FLAG) -o $@ -c $< -I $(I_D_ASM_PATH) -I $(LIB)$(INCS)

$(COREWAR): $(LIBFT) $(COREWAR_OBJS)
	$(CC) $(CFLAGS) $(COREWAR_OBJS) -o $@ $(LIBFLAGS)

$(O_COREWAR_PATH)%.o: $(COREWAR_PATH)%.c
	mkdir -p $(O_COREWAR_PATH)
	$(CC) $(CFLAGS) $(INC_FLAG) -o $@ -c $< -I $(I_COREWAR_PATH) -I $(LIB)$(INCS)

clean:
	make clean -C $(LIB)
	rm -rf $(O_ASM_PATH)
	rm -rf $(O_D_ASM_PATH)
	rm -rf $(O_COREWAR_PATH)

fclean: clean
	make fclean -C $(LIB)
	rm -f $(ASM)
	rm -f $(D_ASM)
	rm -f $(COREWAR)

re: fclean all
