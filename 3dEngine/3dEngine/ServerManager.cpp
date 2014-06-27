# include <winsock2.h>
# include <Windows.h>


void ServerManager::StartListening(int iPort)
{
    iCount=0;
printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return;
    }
     
    printf("Initialised.\n");
     
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        m_pDialog->ShowServerInfo("Could not create socket");
    }

    printf("Socket created.\n");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( iPort );
     
    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        m_pDialog->ShowServerInfo("Bind failed with error code");
        exit(EXIT_FAILURE);
    }
     
    puts("Bind done");

    //Listen to incoming connections
    listen(s , 100);
     char *message;
     puts("Waiting for incoming connections...");
     m_pDialog->ShowServerInfo("Waiting for incoming connections...\n");
     c = sizeof(struct sockaddr_in);
     
    while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
    {
        puts("Connection accepted");
       
        socklen_t len;
        struct sockaddr_storage addr;
        char ipstr[INET6_ADDRSTRLEN];
        int port;

        len = sizeof addr;
        getpeername(new_socket, (struct sockaddr*)&addr, &len);

        // deal with IPv4:
        if (addr.ss_family == AF_INET) {
            struct sockaddr_in *s = (struct sockaddr_in *)&addr;
            port = ntohs(s->sin_port);
            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
        }

        printf("Peer IP address: %s\n", ipstr);
        m_pDialog->ShowServerInfo("Connected Peer IP address: "+string(ipstr)+"\n");
        CWinThread *cTh = AfxBeginThread(
        DataThreadFunc,
        (LPVOID)new_socket);
        ++iCount;
        sArray[iCount] = new_socket;
    }
     
    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d" , WSAGetLastError());
        return;
    }
}

UINT __cdecl ServerManager::DataThreadFunc(LPVOID pParam)
{
    SOCKET pYourSocket = reinterpret_cast<SOCKET>(pParam);
   
    char *message;
    message = "Welcome to Matrix chat room.\n";
    send(pYourSocket , message , strlen(message) , 0);
    char server_reply[2000];
    int recv_size;

    while((recv_size = recv(pYourSocket , server_reply , 2000 , 0)) != SOCKET_ERROR)
    {
        server_reply[recv_size] = '\0';
         for(int i = 1;i<=iCount; i++)
        {
            if( send(sArray[i] , server_reply, recv_size , 0) < 0)
            {
                puts("Send failed");
             }
        }

    }
    return 0;
}