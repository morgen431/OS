#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>

// MINIMAL ERROR HANDLING FOR EASE OF READING

int main(int argc, char *argv[])
{
  int totalsent = -1;
  int nsent     = -1;
  int len       = -1;
  int n         =  0;
  int listenfd  = -1;
  int connfd    = -1;

  struct sockaddr_in serv_addr;
  struct sockaddr_in my_addr;
  struct sockaddr_in peer_addr;

  char data_buff[1025];
  time_t ticks;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset( &serv_addr, '0', sizeof(serv_addr));
  memset( data_buff, '0', sizeof(data_buff));

  serv_addr.sin_family = AF_INET;
  // INADDR_ANY = any local machine address
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(10000);

  if( 0 != bind( listenfd,
                 (struct sockaddr*) &serv_addr,
                 sizeof(serv_addr)))
  {
    printf("\n Error : Bind Failed. %s \n", strerror(errno));
    return 1;
  }

  if( 0 != listen(listenfd, 10) )
  {
    printf("\n Error : Listen Failed. %s \n", strerror(errno));
    return 1;
  }

  while(1)
  {
    // Prepare for a new connection
    socklen_t addrsize = sizeof(struct sockaddr_in );

    // Accept a connection.
    // Can use NULL in 2nd and 3rd arguments
    // but we want to print the client socket details
    connfd = accept( listenfd,
                     (struct sockaddr*) &peer_addr,
                     &addrsize);

    if( connfd < 0 )
    {
      printf("\n Error : Accept Failed. %s \n", strerror(errno));
      return 1;
    }

	char num2read[sizeof(int)];
	int printable[126-32];
	memset(printable,0,126-32);
	int i;
int j;
int printable_out=0;
	
	read(connfd,num2read, sizeof(int) );
	int num_int2read= atoi(num2read);
	printf("Server needs to read %d bytes \n", num_int2read);
	
	char bytes_read[num_int2read];

	int total= num_int2read;
printf("server-pre-total %d\n", total);	


while(total>0){
	printf("server-entered while");
		int cur_read = read(connfd,bytes_read, total ); 
		total-=cur_read;
printf("server-total %d\n", total);	
		for(i=0;i<cur_read; i++){
			if ((((int)bytes_read[i])>=32) && (((int)bytes_read[i])<=126)){
				printable[(int)bytes_read[i]-32]++;
				printable_out++;
			}
		}
	
	}

	printf("Server found: Total printable %d \n", printable_out);
	char printable2client[BUFSIZ];
	sprintf(printable2client, "%d", printable_out); 

	 write(connfd, printable2client, BUFSIZ);
	 
    close(connfd);
  
}
}