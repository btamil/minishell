# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 18:58:50 by tponnusa          #+#    #+#              #
#    Updated: 2023/11/24 15:40:14 by tponnusa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= 	ft_strlen.c ft_strjoin.c ft_split.c ft_substr.c ft_strnstr.c ft_strchr.c ft_strrchr.c ft_putstr_fd.c \
				ft_isdigit.c ft_isalnum.c ft_isalpha.c ft_atoi.c ft_strncmp.c ft_strdup.c ft_strtrim.c ft_itoa.c ft_strlcpy.c\
				ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isascii.c ft_calloc.c ft_bzero.c ft_memset.c
			
#BSRC		= 	ft_lstnew.c ft_lstsize.c ft_lstadd_back.c ft_lstadd_front.c  ft_lstlast.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror

SOFILES 	=	$(SRC:.c=.o)

#BOFILES 	=   $(BSRC:.c=.o)

NAME		= 	libft.a

all			:	$(NAME)

$(NAME)		:	$(SOFILES)
				ar -r $(NAME) $(SOFILES)

$(SOFILES)	:	$(SRC)
				$(CC) $(CFLAGS) -c $(SRC)

#$(BOFILES)	:	$(BSRC)
#				$(CC) $(CFLAGS) -c $(BSRC)

#bonus  		:	$(BOFILES)
#				ar -r $(NAME) $(BOFILES)

clean		:
				rm -f $(SOFILES)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re 
