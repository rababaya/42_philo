CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -I includes -g3 #-fsanitize=thread
RM					=	rm -f
NAME				=	philo

VALIDATION_SRC_DIR	=	validation

VALIDATION_SRC		=	$(VALIDATION_SRC_DIR)/validation.c \
						$(VALIDATION_SRC_DIR)/ft_atoi.c

PHILO_SRC			=	main.c \
						init.c \
						philo_actions.c \
						utils.c \
						$(VALIDATION_SRC) #\
						$(STACK_SRC) \
						$(PS_SRC) \
						$(BASIC_SORT_SRC) \
 
PHILO_OBJ			=	$(PHILO_SRC:%.c=obj/philo/%.o)

all:				$(NAME)
 
$(PHILO_OBJ):		obj/philo/%.o: %.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@
 
$(NAME):			$(PHILO_OBJ) 
					$(CC) $(CFLAGS) $(PHILO_OBJ) -o $@
 
clean:
					rm -rf obj
 
fclean:				clean
					$(RM) $(NAME)
 
re:					fclean all
 
.PHONY:				all clean fclean re #bonus
