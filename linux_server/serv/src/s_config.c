#include<libconfig.h>
#include<stdio.h>
#include"s_config.h"

void read_config_file( char * filename , int * port, int * maxclients )
{
   config_t cfg;
   
   config_init(&cfg);

   if(!config_read_file(&cfg, filename))
   {
      printf("%s:%d -%s\n",config_error_file(&cfg),config_error_line(&cfg),config_error_text(&cfg));
      config_destroy(&cfg);      
    return;
   }
          

   if(config_lookup_int(&cfg, "port" , port ))
   {
      printf("Port servera: %d \n", *port);
   }
   else
   {
      printf("Nie znaleziono Portu w %s\n", filename);
      config_destroy(&cfg); 
     return;
   }
   
   if(config_lookup_int(&cfg, "max_clients" , maxclients))
   {
      printf("Maksymalna liczba klientow: %d \n", *maxclients);
   }
   else
   {
      printf("Nie znaleziono liczby klientow w %s\n", filename);
      config_destroy(&cfg); 
     return ;
   }

   config_destroy(&cfg);
   return ;
}

