bin/a.out:obj/lottery_user.o obj/lottery_tickets.o obj/lottery_period.o obj/view.o obj/getPasswd.o obj/control.o obj/main.o
	gcc obj/lottery_user.o obj/lottery_tickets.o obj/lottery_period.o obj/view.o obj/getPasswd.o obj/control.o obj/main.o -o bin/a.out
obj/lottery_user.o:src/lottery_user.c
	gcc -c src/lottery_user.c -o obj/lottery_user.o -I include 
obj/lottery_tickets.o:src/lottery_tickets.c
	gcc -c src/lottery_tickets.c -o obj/lottery_tickets.o -I include 
obj/lottery_period.o:src/lottery_period.c
	gcc -c src/lottery_period.c -o obj/lottery_period.o -I include 
obj/view.o:src/view.c
	gcc -c src/view.c -o obj/view.o -I include 
obj/getPasswd.o:src/getPasswd.c
	gcc -c src/getPasswd.c -o obj/getPasswd.o -I include 
obj/main.o:src/main.c
	gcc -c src/main.c -o obj/main.o -I include 
obj/control.o:src/control.c
	gcc -c src/control.c -o obj/control.o -I include 

.PHONY:clean

clean:
	rm obj/*.o bin/a.out
