#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{
 int i,status=-1,opt,dom_id,num_domains;
 int *active_doms;
 char domain_name[40];

 virConnectPtr connect;
 virDomainPtr dptr;

 connect = virConnectOpen("xen:///");

 if (connect == NULL) 
 {
 	fprintf(stderr, "Could not connect to hypervisor XEN\n");
        exit(1);
 }
 else
 {
	while(1)
        {
		num_domains=virConnectNumOfDomains(connect);
        	active_doms=malloc(sizeof(int) * num_domains);
        	num_domains = virConnectListDomains(connect, active_doms, num_domains);            	
		printf("Active Domain IDs: \n");
        
		for (i=0;i<num_domains;i++)
		{
            	printf("  %d\n", active_doms[i]);
        	}
        	free(active_doms);

        	printf("1.Start\n2.Pause\n3.Resume\n4.Shutdown\n5.Exit\n");
            	scanf("%d",&opt);
		

            	
        
            	switch(opt)
            	{
                	case 1:
			system("sudo xm list");
                       	printf("Enter the domU name to be started  :");
		       	scanf("%s",domain_name);
			dptr=virDomainLookupByName(connect,domain_name);
			status=virDomainCreate(dptr);
			if(status==0)
				printf("Starting domU success\n");
                       	else
                           	printf("Failed to start the domU\n");   
                       	break;

                	case 2:
			printf("\nEnter the active domian ID: ");
            		scanf("%d",&dom_id); 
            		dptr=virDomainLookupByID(connect,dom_id);
		       	status=virDomainSuspend(dptr);
                       	if(status==0)
                           	printf("Success suspending the domU\n");
                       	else
                           	printf("Failed to suspend the domU\n");   
                       	break;

                	case 3: 
			printf("\nEnter the active domian ID: ");
            		scanf("%d",&dom_id); 
            		dptr=virDomainLookupByID(connect,dom_id);
		        status=virDomainResume(dptr);
                        if(status==0)                     
                            	printf("Success resuming the domU\n");
                        else
                            	printf("Failed to resume the domU\n");   
                        break;

                	case 4: 
			printf("\nEnter the active domian ID: ");
            		scanf("%d",&dom_id); 
            		dptr=virDomainLookupByID(connect,dom_id);
			status=virDomainShutdown(dptr);
                        if(status==0)
			{                     
                            	printf("Success shutting down the domain\n");
			}
                        else
                            	printf("Failed to shut down the domain\n");   
                        break;

                	default:exit(1);
                }
        }
        virConnectClose(connect);
    }
}
