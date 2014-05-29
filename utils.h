#include <stdlib.h>
#include <libxml/tree.h>
#include <libnetconf_xml.h>
#include <string.h>


/* Simply prints the parameters values plus some additional information (xmlNode first child and parent). */
void logTransapiOperation(void ** data, XMLDIFF_OP op, xmlNodePtr node, struct nc_err** error);

char*getChildContent(xmlNode*father, char*childName);
