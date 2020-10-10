static void SendB_f(void const * argument){

	 struct netconn *conn, *newconn;
	  err_t err, accept_err, recv_err;
	  struct netbuf *inbuf;
	  int result;
	  char* buf;
	    char data_stored[] ="Hi";
	  u16_t buflen;
	  const unsigned char b[] = "ABC";
	  /* Create a new TCP connection handle */
	  conn = netconn_new(NETCONN_TCP);
	  err = netconn_bind(conn, NULL, 80);
	  netconn_listen(conn);

	  for( ;; )
	  {
	        /* accept any icoming connection */
		  accept_err = netconn_accept(conn, &newconn);
	        if(accept_err == ERR_OK)
	        {
	    	    BSP_LED_Toggle(LED2);
	    	    netconn_write(newconn, b, strlen((char*)b), NETCONN_COPY );
	    	    osDelay(250);

	    	    recv_err = netconn_recv(newconn, &inbuf);
	    	    if (recv_err == ERR_OK){
	    	    	netbuf_data(inbuf, (void**)&buf, &buflen);
	    	    	result = strcmp(buf, data_stored);
	    	    	if(result == 0){
	    	    		BSP_LED_Toggle(LED3);
	    	    	}
	    	    }
	        }
	    /* Toggle LED4 each 250ms */

	  }
}