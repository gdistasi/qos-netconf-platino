/*
 * This is automatically generated callbacks file
 * It contains 3 parts: Configuration callbacks, RPC callbacks and state data callbacks.
 * Do NOT alter function signatures or any structures unless you know exactly what you are doing.
 */

#include <stdlib.h>
#include <libxml/tree.h>
#include <libnetconf_xml.h>

#include "utils.h"

/* transAPI version which must be compatible with libnetconf */
int transapi_version = 4;

/* Signal to libnetconf that configuration data were modified by any callback.
 * 0 - data not modified
 * 1 - data have been modified
 */
int config_modified = 0;

/*
 * Determines the callbacks order.
 * Set this variable before compilation and DO NOT modify it in runtime.
 * TRANSAPI_CLBCKS_LEAF_TO_ROOT (default)
 * TRANSAPI_CLBCKS_ROOT_TO_LEAF
 */
const TRANSAPI_CLBCKS_ORDER_TYPE callbacks_order = TRANSAPI_CLBCKS_ORDER_DEFAULT;

/* Do not modify or set! This variable is set by libnetconf to announce edit-config's error-option
Feel free to use it to distinguish module behavior for different error-option values.
 * Possible values:
 * NC_EDIT_ERROPT_STOP - Following callback after failure are not executed, all successful callbacks executed till
                         failure point must be applied to the device.
 * NC_EDIT_ERROPT_CONT - Failed callbacks are skipped, but all callbacks needed to apply configuration changes are executed
 * NC_EDIT_ERROPT_ROLLBACK - After failure, following callbacks are not executed, but previous successful callbacks are
                         executed again with previous configuration data to roll it back.
 */
NC_EDIT_ERROPT_TYPE erropt = NC_EDIT_ERROPT_NOTSET;

/**
 * @brief Initialize plugin after loaded and before any other functions are called.

 * This function should not apply any configuration data to the controlled device. If no
 * running is returned (it stays *NULL), complete startup configuration is consequently
 * applied via module callbacks. When a running configuration is returned, libnetconf
 * then applies (via module's callbacks) only the startup configuration data that
 * differ from the returned running configuration data.

 * Please note, that copying startup data to the running is performed only after the
 * libnetconf's system-wide close - see nc_close() function documentation for more
 * information.

 * @param[out] running	Current configuration of managed device.

 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int transapi_init(xmlDocPtr * running)
{
	return EXIT_SUCCESS;
}

/**
 * @brief Free all resources allocated on plugin runtime and prepare plugin for removal.
 */
void transapi_close(void)
{
	return;
}

/**
 * @brief Retrieve state data from device and return them as XML document
 *
 * @param model	Device data model. libxml2 xmlDocPtr.
 * @param running	Running datastore content. libxml2 xmlDocPtr.
 * @param[out] err  Double pointer to error structure. Fill error when some occurs.
 * @return State data as libxml2 xmlDocPtr or NULL in case of error.
 */
xmlDocPtr get_state_data (xmlDocPtr model, xmlDocPtr running, struct nc_err **err)
{
	return(NULL);
}
/*
 * Mapping prefixes with namespaces.
 * Do NOT modify this structure!
 */
char * namespace_mapping[] = {"shaper", "http://www.comics.unina.it/nc/shaper", NULL, NULL};

/*
* CONFIGURATION callbacks
* Here follows set of callback functions run every time some change in associated part of running datastore occurs.
* You can safely modify the bodies of all function as well as add new functions for better lucidity of code.
*/

/**
 * @brief This callback will be run when node in path /shaper:shaper changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] node	Modified node. if op == XMLDIFF_REM its copy of node removed.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_shaper_shaper (void ** data, XMLDIFF_OP op, xmlNodePtr node, struct nc_err** error)
{
	logTransapiOperation(data, op, node, error);
	return EXIT_SUCCESS;
}


/**
 * @brief This callback will be run when node in path /shaper:shaper/shaper:qdisc changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] node	Modified node. if op == XMLDIFF_REM its copy of node removed.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_shaper_shaper_shaper_qdisc (void ** data, XMLDIFF_OP op, xmlNodePtr node, struct nc_err** error)
{

	logTransapiOperation(data, op, node, error);
	
 	if (op & XMLDIFF_ADD){
		nc_verb_verbose("Requested to add a qdisc.");
			
		char * ifn=0;
		char * bandwidth=0;	

		ifn = getChildContent(node, "interface");
		bandwidth = getChildContent(node, "bandwidth");
		
		char cmd[512];

		/* commands are enqueue in reverse order */
		/* define default class for non classified packetes */
		sprintf(cmd, "tc class add dev %s parent 1:1 classid 1:100 htb rate 10kbit ceil %skbit", ifn, bandwidth);
		nc_verb_verbose(cmd);
		enqueue_command(cmd);
		
		/* define bandwidth for the interface */
		sprintf(cmd, "tc class add dev %s parent 1: classid 1:1 htb rate %skbit ceil %skbit", ifn, bandwidth, bandwidth);
		nc_verb_verbose(cmd);
		enqueue_command(cmd);
		
		/* install htb traffic shaper */
		sprintf(cmd, "tc qdisc add dev %s root handle 1:0 htb default 100", ifn); 
		nc_verb_verbose(cmd);
		enqueue_command(cmd);
		
	}	
	
	else if (op & XMLDIFF_REM){
		nc_verb_verbose("Requested to delete a qdisc.");
	
		char cmd[512];
		char * ifn=0;
	
		ifn = getChildContent(node, "interface");
	
		sprintf(cmd, "tc qdisc del dev %s root", ifn); 
		nc_verb_verbose(cmd);
		system(cmd);
		
	}
	
	
	/* exec all the enqueued commands in reverse order */
	exec_commands();
			
	return EXIT_SUCCESS;
	
}

/**
 * @brief This callback will be run when node in path /shaper:shaper/shaper:qdisc/shaper:class changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] node	Modified node. if op == XMLDIFF_REM its copy of node removed.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_shaper_shaper_shaper_qdisc_shaper_class (void ** data, XMLDIFF_OP op, xmlNodePtr node, struct nc_err** error)
{
	logTransapiOperation(data, op, node, error);

	if (op & XMLDIFF_ADD){
	  
		nc_verb_verbose("Requested to add a class.");
				
		char * id=0;
		char * prio=0;		
		char * rate=0;
		char * ceil=0;
		char * burst=0;	
		char * ifn=0;

		id = getChildContent(node, "id");
		prio = getChildContent(node, "prio");
		rate = getChildContent(node, "rate");
		ceil = getChildContent(node, "ceil");
		burst = getChildContent(node, "burst");
		ifn = getChildContent(node->parent, "interface");
		
		char cmd[512];
		sprintf(cmd, "tc class add dev %s parent 1:1 classid 1:%s %s htb rate %skbit ceil %skbit ",ifn, id, prio, rate, ceil); 
		
		
		char temp[512];		
		if (burst!=0 && strlen(burst) > 0){
		  sprintf(temp, " burst %s", burst);
		  strcat(cmd, temp);
		}
		
		nc_verb_verbose(cmd);
		enqueue_command(cmd);							
						
	}	
	
	
	else if (op & XMLDIFF_MOD){
	  
		nc_verb_verbose("Requested to modify a class.");
				
		char * id=0;
		char * prio=0;		
		char * rate=0;
		char * ceil=0;
		char * burst=0;	
		char * ifn=0;

		id = getChildContent(node, "id");
		prio = getChildContent(node, "prio");
		rate = getChildContent(node, "rate");
		ceil = getChildContent(node, "ceil");
		burst = getChildContent(node, "burst");
		ifn = getChildContent(node->parent, "interface");
		
		char cmd[512];
		sprintf(cmd, "tc class replace dev %s parent 1:1 classid 1:%s %s htb rate %skbit ceil %skbit ",ifn, id, prio, rate, ceil); 
		
		
		char temp[512];		
		if (burst!=0 && strlen(burst) > 0){
		  sprintf(temp, " burst %s", burst);
		  strcat(cmd, temp);
		}
		
		nc_verb_verbose(cmd);
		enqueue_command(cmd);							
						
	}
	
	else if (op & XMLDIFF_REM){
	  
		nc_verb_verbose("Requested to delete a class.");
				
		char * id=0;
		char * ifn=0;

		id = getChildContent(node, "id");
		ifn = getChildContent(node->parent, "interface");
		
		char cmd[512];
		sprintf(cmd, "tc class del dev %s parent 1:1 classid 1:%s ",ifn, id); 
		
		nc_verb_verbose(cmd);
		system(cmd);							
						
	}	
				
	return EXIT_SUCCESS;

}


void AddIfNotEmpty(char * cmd, char * key, char * value, char * trailer){
  
 	char temp[512];		
	
	if (value!=0 && strlen(value) > 0){
	  sprintf(temp, " %s %s%s",key, value,trailer);
	  strcat(cmd, temp);
	}
    
}


/**
 * @brief This callback will be run when node in path /shaper:shaper/shaper:qdisc/shaper:class/shaper:filter changes
 *
 * @param[in] data	Double pointer to void. Its passed to every callback. You can share data using it.
 * @param[in] op	Observed change in path. XMLDIFF_OP type.
 * @param[in] node	Modified node. if op == XMLDIFF_REM its copy of node removed.
 * @param[out] error	If callback fails, it can return libnetconf error structure with a failure description.
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/* !DO NOT ALTER FUNCTION SIGNATURE! */
int callback_shaper_shaper_shaper_qdisc_shaper_class_shaper_filter (void ** data, XMLDIFF_OP op, xmlNodePtr node, struct nc_err** error)
{
	logTransapiOperation(data, op, node, error);

	/* Filter node added */
	if (op & XMLDIFF_ADD || op & XMLDIFF_MOD){
		nc_verb_verbose("Requested to add/modify a filter.");
			
		char * id;
		char * protocol;	
		char * source=0;
		char * destination=0;		
		char * sport=0;
		char * dport=0;
		char * pmark=0;	
		
		char * classid=0;
		char * ifn=0;
		
		id = getChildContent(node, "id");
		protocol = getChildContent(node, "protocol");
		source = getChildContent(node, "source");
		destination = getChildContent(node, "destination");
		sport = getChildContent(node, "sourcePort");
		dport = getChildContent(node, "destinationPort");
		pmark = getChildContent(node, "packetMark");
		
		ifn = getChildContent(node->parent->parent, "interface");
		classid = getChildContent(node->parent, "id");
		
		char cmd[512];
		
		if (op & XMLDIFF_ADD || op & XMLDIFF_MOD)
		  sprintf(cmd, "tc filter add dev %s parent 1: protocol ip handle 800::%s prio 1 u32 ", ifn, id); 
		  
		AddIfNotEmpty(cmd, "match ip protocol", protocol, " 0xff");
		AddIfNotEmpty(cmd, "match ip sport", sport, " 0xffff");
		AddIfNotEmpty(cmd, "match ip dport", dport, " 0xffff");
		AddIfNotEmpty(cmd, "match ip src", source, "");
		AddIfNotEmpty(cmd, "match ip dst", destination, "");
		AddIfNotEmpty(cmd, "match pmark", pmark, "");
		
		
		strcat(cmd, " flowid 1:");
		strcat(cmd, classid);
		
		nc_verb_verbose(cmd);
		enqueue_command(cmd);	
		
		// if the filter was alread present, delete the old
		if (op & XMLDIFF_MOD){
		      sprintf(cmd, "tc filter del dev %s parent 1: protocol ip handle 800::%s prio 1 u32", ifn, id);
		      nc_verb_verbose(cmd);
		      enqueue_command(cmd);	
		}
		
	}
	
	else if (op & XMLDIFF_REM){
	      nc_verb_verbose("Requested to delete a filter.");
	  
	      char * id;
	      char * ifn=0;
       	      char cmd[512];
	      
	      id = getChildContent(node, "id");
	      ifn = getChildContent(node->parent->parent, "interface");
	      
	      sprintf(cmd, "tc filter del dev %s parent 1: protocol ip handle 800::%s prio 1 u32", ifn, id);
	      nc_verb_verbose(cmd);
	      system(cmd);	
	}
    	
	return EXIT_SUCCESS;

}
/*
* Structure transapi_config_callbacks provide mapping between callback and path in configuration datastore.
* It is used by libnetconf library to decide which callbacks will be run.
* DO NOT alter this structure
*/
struct transapi_data_callbacks clbks =  {
	.callbacks_count = 4,
	.data = NULL,
	.callbacks = {
		{.path = "/shaper:shaper", .func = callback_shaper_shaper},
		{.path = "/shaper:shaper/shaper:qdisc", .func = callback_shaper_shaper_shaper_qdisc},
		{.path = "/shaper:shaper/shaper:qdisc/shaper:class", .func = callback_shaper_shaper_shaper_qdisc_shaper_class},
		{.path = "/shaper:shaper/shaper:qdisc/shaper:class/shaper:filter", .func = callback_shaper_shaper_shaper_qdisc_shaper_class_shaper_filter}
	}
};

/*
* RPC callbacks
* Here follows set of callback functions run every time RPC specific for this device arrives.
* You can safely modify the bodies of all function as well as add new functions for better lucidity of code.
* Every function takes array of inputs as an argument. On few first lines they are assigned to named variables. Avoid accessing the array directly.
* If input was not set in RPC message argument in set to NULL.
*/

/*
* Structure transapi_rpc_callbacks provide mapping between callbacks and RPC messages.
* It is used by libnetconf library to decide which callbacks will be run when RPC arrives.
* DO NOT alter this structure
*/
struct transapi_rpc_callbacks rpc_clbks = {
	.callbacks_count = 0,
	.callbacks = {
	}
};

