#include <stdlib.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/types.h>
#include <ifaddrs.h>

#include <libxml/tree.h>
#include <libnetconf_xml.h>
#include "utils.h"


#define MAX_COMMANDS 500
char * commands_to_execute[MAX_COMMANDS];
int num_cmds=0;

void enqueue_command(char * cmd){
  commands_to_execute[num_cmds] = strdup(cmd);
  num_cmds ++;
}

void exec_commands(){
  int i=num_cmds-1;
  for (; i>=0; i--){
      nc_verb_verbose("Executing: ");
      nc_verb_verbose(commands_to_execute[i]);
      system(commands_to_execute[i]);
      free(commands_to_execute[i]);
  }
  num_cmds=0;
}

void logTransapiOperation(void ** data, XMLDIFF_OP op, xmlNodePtr node, struct nc_err** error){
 
    nc_verb_verbose("OPERATION:");
    
    switch(op){
     
      case XMLDIFF_MOD:
	nc_verb_verbose("MOD");
	break;
      
      case XMLDIFF_CHAIN:
	nc_verb_verbose("CHAIN");
	break;
      
      case XMLDIFF_REM:
	nc_verb_verbose("XMLDIFF_REM");
	break;
      
      case XMLDIFF_ADD:
	nc_verb_verbose("XMLDIFF_ADD");
	break;
      
      case XMLDIFF_NONE:
	nc_verb_verbose("XMLDIFF_NONE");
	break;
      
      case XMLDIFF_SIBLING:
	nc_verb_verbose("XMLSIBLING_NONE");
	break;
      
      case XMLDIFF_REORDER:
	nc_verb_verbose("XMLREORDER_NONE");
	break;
	
      default: 
	nc_verb_verbose("UNKNOWN OPERATION!");
    }
      
    nc_verb_verbose("xmlNode: %s", node->name);
    nc_verb_verbose("xmlNode first child name: %s", node->children->name);
    

    if (node->children->last!=NULL)	{
      nc_verb_verbose("xmlNode first child content: %s", (char*)node->children->last->content);
      nc_verb_verbose("xmlNode last child: %s", node->last->name);
   					}
    if (node->parent!=NULL)	{
      			nc_verb_verbose("xmlNode parent: %s", node->parent->name);
    				} 
	else 
	{
      		nc_verb_verbose("xmlNode NOPARENT");
    	}


    return;
  
}

char* getChildContent(xmlNode *father, char *childName)
{
	int maxLenght=512;
	char*result=malloc(maxLenght);
	result[0]='\0';

xmlNode*node=father->children;

	if (strcmp((char*)node->name, childName)==0)
		{
		strncpy(result, (char*)node->last->content, maxLenght);
		}

 else
		{
		while ((node=node->next)!=0)
		{

			if (strcmp((char*)node->name, childName)==0)
			{
			strncpy(result, (char*)node->last->content, maxLenght);
			break;
			}
		
		}

		
		}
return result;

}


/* return a number different from 0 if ipAddress is a valid address */
int isValidIpAddress(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

int getInterfaceFromIp(char * ip, char * ifn) {
  struct ifaddrs *addrs, *iap;
  struct sockaddr_in *sa;
  char buf[32];
  int found=0;

  getifaddrs(&addrs);
  for (iap = addrs; iap != NULL; iap = iap->ifa_next) {
    if (iap->ifa_addr && (iap->ifa_flags & IFF_UP) && iap->ifa_addr->sa_family == AF_INET) {
      sa = (struct sockaddr_in *)(iap->ifa_addr);
      inet_ntop(iap->ifa_addr->sa_family, (void *)&(sa->sin_addr), buf, sizeof(buf));
      if (!strcmp(ip, buf)) {
        sprintf(ifn, "%s", iap->ifa_name);
	found=1;
      }
    }
  }
  freeifaddrs(addrs);

  return found;
}



char * getInterfaceName(xmlNode *father, char *childName)
{
	char result[IFNAMSIZ];
	//result[0]='\0';
	char * ifn = malloc(IFNAMSIZ);


	xmlNode*node=father->children;

	if (strcmp((char*)node->name, childName)==0){
		strncpy(result, (char*)node->last->content, IFNAMSIZ);
	} else {
		while ((node=node->next)!=0){
			if (strcmp((char*)node->name, childName)==0){	
			  strncpy(result, (char*)node->last->content, IFNAMSIZ);
			  break;
			}
		}
	}

	nc_verb_verbose("RESULT IS EQUAL TO: %s.", result);

	
	if (isValidIpAddress(result)){
	    if (getInterfaceFromIp(result, ifn)==0){
		strcpy(ifn,"");
	    }	    
	} else {
	   nc_verb_verbose("RESULT IS EQUAL TO: %s.", result);
	   strncpy(ifn, result, IFNAMSIZ);
	}
	
	return ifn;
}











