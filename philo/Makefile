# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/30 16:02:30 by dzivanov          #+#    #+#              #
#    Updated: 2021/12/30 16:02:30 by dzivanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror -pthread
#CFLAGS		= -g -Wall -Wextra -Werror -pthread -fsanitize=thread
RM			= rm -f
SRCD		= ./srcs/
SRC			=  philosophers.c ft_libft_utils.c ft_delays.c ft_handlers.c ft_philo_feeding.c ft_threads.c ft_philo.c ft_initializers.c ft_thread_gen.c
# Command to add the source folder prefix (instead of having it added manually to SRC)
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD		= $(OBJF:$(OBJD)%.o)

NAME		= philo
HEADD		= ./incl/
HEADF		= philosophers.h

#if to the respective c file in the source directory no matching o file in the object
#directory is available, then create it according to the following rules:
#Note: the object directory will only be created if not existing already. -p flag throws no errors when already there
$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

$(NAME):	${OBJF}
			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) -L $(HEADD)

all:		${NAME}

clean:
			${RM} ${OBJF}

fclean:		clean
			${RM} ${NAME}
			@${RM} ${HEADD}philosophers.h.gch

re:			fclean all

.PHONY:		all clean fclean re