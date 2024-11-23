OBJS = texas_holdemv6.o cardart.o cardops.o handscore.o pokerAI.o
CC= gcc 
CFLAGS = -c 
WFLAGS = -Wall 

poker: $(OBJS)
	$(CC) $(WFLAGS) -g $(OBJS) -o poker
  
texas_holdem: texas_holdemv6.c cardart.h cardops.h
	$(CC) $(CFLAGS) texas_holdemv6.c 
  
cardart: cardart.c cardart.h
	$(CC) $(CFLAGS) cardart.c 

cardops: cardops.c cardops.h
	$(CC) $(CFLAGS) cardops.c 

handscore: handscore.c handscore.h cardops.h
	$(CC) $(CFLAGS) handscore.c 
 
pokerAI: pokerAI.c pokerAI.h handscore.h cardops.h cardart.h
	$(CC) $(CFLAGS) pokerAI.c 