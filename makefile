#*******************************************************************************
# PROJECT: Gamp
#
# AUTHORS: Yohann Martin, Mathias Géroudet, Timothée Pionnier, Oscar Mc Auliffe
#
# DATE CREATED: 04/26/2021
#
# Copyright (c) 2021 Gamp. All rights reserved.
#
# Licensed under the MIT License. See LICENSE file in the project root for full
# license information.
#*******************************************************************************

CC			= g++
OPENCV		= `pkg-config --cflags --libs opencv4`
CPPFLAGS	= -std=c++11 -Wall -Wextra -Werror -Wno-sign-compare -Iincludes/ $(OPENCV) -O2

FOLDER		= build/
TARGET		= gamp
RM			= rm -f

SRC			= \
			$(wildcard src/*.cpp)

OBJ			= $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(FOLDER)$(TARGET)


.PHONY: clean fclean re install_opencv

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(FOLDER)$(TARGET)

re: fclean all

install_opencv:
	bash ./install_opencv.sh
