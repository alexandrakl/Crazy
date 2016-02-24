NAME=Crazy

all: $(NAME).cpp; clang++ -std=c++11 -o $(NAME) $(NAME).cpp

clean: $(NAME); rm $(NAME)

commit:	$(NAME).cpp; git add --all; git commit -m "generic"; git push origin master