#include <stdlib.h>
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














