








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
    }
      
    nc_verb_verbose("xmlNode: %s", node->name);
    nc_verb_verbose("xmlNode child: %s", node->children->name);

    nc_verb_verbose("xmlNode last child: %s", node->last->name);
    if (node->parent!=NULL){
      nc_verb_verbose("xmlNode parent: %s", node->parent->name);
    } else {
      nc_verb_verbose("xmlNode NOPARENT");
    }
    
    
    return;
  
}