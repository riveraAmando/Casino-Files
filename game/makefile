OBJS = casino_project.o blackjack.o texas_holdemv6.o cardart.o cardops.o handscore.o pokerAI.o
CC= gcc 
CFLAGS = -c 
WFLAGS = -Wall 

casino: $(OBJS)
	$(CC) $(WFLAGS) -g $(OBJS) -o casino_game
  
casino_project: casino_project.c texas_holdemv6.h slots.h blackjack.h
	$(CC) $(CFLAGS) casino_project.c 
 
blackjack: blackjack.c cardart.h cardops.h blackjackscore.h
	$(CC) $(CFLAGS) blackjack.c 

texas_holdem: texas_holdemv6.c cardart.h cardops.h pokerAI.h handscore.h
	$(CC) $(CFLAGS) texas_holdemv6.c 
  
cardart: cardart.c cardart.h
	$(CC) $(CFLAGS) cardart.c 

cardops: cardops.c cardops.h
	$(CC) $(CFLAGS) cardops.c 

handscore: handscore.c handscore.h cardops.h
	$(CC) $(CFLAGS) handscore.c 
 
pokerAI: pokerAI.c pokerAI.h handscore.h cardops.h cardart.h
	$(CC) $(CFLAGS) pokerAI.c 