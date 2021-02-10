#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* You will to add includes here */
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>


// Enable if you want debugging to be printed, see examble below.
// Alternative, pass 
#define DEBUG
#define DEBUG2




// Input hantering

int main(int argc, char* argv[]) {


  printf("Fick %d \n", argc);
  if (argc!=2) {
    printf("Usage; %s <ip>:<port> \n", argv[0]);
    exit(1);
  }
   
  /*
    Read first input, assumes <ip>:<port> syntax, convert into one string (Desthost) and one integer (port). 
    Atm, works only on dotted notation, i.e. IPv4 and DNS. IPv6 does not work if its using ':'. 
  */
  char delim[]=":";
#ifdef DEBUG2   
  printf("org argv[1] == %s \n",argv[1]); 
#endif
  char *Desthost=strtok(argv[1],delim);

#ifdef DEBUG2 
  printf("first argv[1] == %s \n",argv[1]);
#endif
  char *Destport=strtok(NULL,delim);
#ifdef DEBUG2 
  printf("last argv[1] == %s \n",argv[1]);
#endif

  if (Desthost == NULL || Destport == NULL){
    printf("Missing host or port.\n");
    exit(1);
  };



  printf("Desthost = %p len = %d \n",Desthost, strlen(Desthost));
  printf("Destport = %p len = %d \n",Destport, strlen(Destport));

  

  
  // *Desthost now points to a sting holding whatever came before the delimiter, ':'.
  // *Dstport points to whatever string came after the delimiter. 



  
  /* Do magic */
  int port=atoi(Destport);
#ifdef DEBUG 
  printf("Host %s, and port %d.\n",Desthost,port);
#endif
  
  

  
  // Skapa socket


  struct addrinfo hints, *servinfo, *p;
  int rv;
  int sockfd;
  struct protoent *servptr;

  
   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC; // AF_INET , AF_INET6
   hints.ai_socktype = SOCK_DGRAM; // <<--- TRANSPORT PROTOCOL!!

   printf("Bob\n");

   
  if ((rv = getaddrinfo(Desthost, Destport, &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  int k=0;
  for(p = servinfo; p != NULL; p = p->ai_next) {
    
#ifdef DEBUG
    printf("[%d] - ",k);
    if (p->ai_family == AF_INET ) {
      printf("IPv4 (%d)| ",p->ai_family);
    }
    if (p->ai_family == AF_INET6 ) {
      printf("IPv6 (%d)|",p->ai_family);
    }

    if (p->ai_socktype == SOCK_STREAM){
      printf("STREAM|");
    }
    if (p->ai_socktype == SOCK_DGRAM){
      printf("DGRAM|");
    } 
    servptr = getprotobynumber(p->ai_protocol);
    printf("%s  --> ", servptr->p_name);
#endif
    k++;
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
			 p->ai_protocol)) == -1) {
      printf("Socket creation failed.\n");
      continue;
    }

    printf("Socket created.\n");
    break;

  }


  if (p == NULL) {
    fprintf(stderr, "Client failed to creat an appropriate socket.\n");
    freeaddrinfo(servinfo);
    exit(1);
  }
     

  /* ---- 


  
  /* Applikation API */

  // send, sendto, sendmsg

  ssize_t sentbytes;

  char myBugger[]="Hello World!!!\n";
  
  printf("myBugger => sizeof () = %d \n", sizeof(myBugger));
  printf("myBugger => strlen () = %d \n", strlen(myBugger));


  rv=connect(sockfd,  p->ai_addr,p->ai_addrlen);
  printf("rv = %d \n",rv);
	 
  sentbytes=send(sockfd,&myBugger,sizeof(myBugger), NULL);
  printf("Skickade (send) %d bytes.\n", sentbytes);


  
  sentbytes=sendto(sockfd,&myBugger,sizeof(myBugger), NULL, p->ai_addr,p->ai_addrlen);
  printf("Skickade (sendto ) %d bytes.\n", sentbytes);
  

  struct __attribute__((__packed__))  myStruct {
    int32_t enInteger;
    int32_t enAnnanInteger;
    int16_t foo;
    double aDouble;
    double bDouble;
  };
  
  struct myStruct Bob;
  Bob.enInteger=htonl(1);
  Bob.enAnnanInteger=htonl(2);
  Bob.foo=htons(3);
  Bob.aDouble=100;
  Bob.bDouble=200;


  printf("Bob => sizeof () = %d \n", sizeof(Bob));
  
  sentbytes=sendto(sockfd,&Bob,sizeof(Bob), NULL,  p->ai_addr,p->ai_addrlen);
  printf("Skickade %d bytes.\n", sentbytes);

  
  
  // Skicka msg
  // Läs svar



// Stäng socket

/* EOF */ 


}
