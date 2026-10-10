#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/udp.h>

#include "omoe_driver_nf_receiver.h"
#include "omoe_driver_protocol_parser.h"

#define OMOE_PROTOCOL 253	/* experimental number 253 */

static struct nf_hook_ops nfho;

static void process_omoe_packet(struct sk_buff* skb)
{
    if (skb_is_nonlinear(skb))
    {
	int retval = skb_linearize(skb);
	if (retval != 0)	/* if no memory left, just drop the packet */
	{
	    pr_err("Error, unable to linearize packet, out of memory");
	    return;
	}
    }
    
    // now the sb_buff is linear

    struct iphdr* iph = ip_hdr(skb);
    
    unsigned char* payload = (unsigned char*)iph + sizeof(struct iphdr);
    size_t payload_len = ntohs(iph->tot_len) - sizeof(struct iphdr);

    pr_info("parsed packet with data %s of size %ld\n", payload, payload_len);

    // omoe_sysfs_set_value(payload_len);

    parse_incoming_packet(payload, payload_len);
    
}

static unsigned int omoe_nf_recv_hook(void* priv,
				      struct sk_buff* skb,
				      const struct nf_hook_state* state)
{
    if (!skb)
	return NF_ACCEPT;

    struct iphdr* ip_header = ip_hdr(skb);

    if (!ip_header)
	return NF_ACCEPT;

    if (ip_header->protocol != OMOE_PROTOCOL)
	return NF_ACCEPT;
    
    pr_info("Got OMOE packet from %pI4\n",
	    &ip_header->saddr);

    process_omoe_packet(skb);
    
    return NF_DROP;
}

int __init omoe_nf_init(void)
{
    pr_info("Initializing OMOE netfilter hook\n");

    nfho.hook = omoe_nf_recv_hook;
    nfho.hooknum = NF_INET_PRE_ROUTING;
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;

    return nf_register_net_hook(&init_net, &nfho);
}

void __exit omoe_nf_exit(void)
{
    pr_info("Unregistering OMOE netfilter hook\n");

    nf_unregister_net_hook(&init_net, &nfho);
}
