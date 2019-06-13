
#include <linux/kernel.h>
#include <linux/module.h>

static int inport(int port)
{
    int value;
    asm ("xor %%eax, %%eax; inb %%dx, %%al" : "=a"(value) : "d"(port));
    return value;
}

static void outport(int port, int value)
{
    asm ("outb %%al, %%dx" : : "d"(port), "a"(value));
}

static int __init xbiospwd_init(void)
{
    int i;

    printk("[%s]\n", __func__);

    for (i = 0; i < 0x100; ++i) {
        outport(0x70, i);
        printk("%x: %x\n", i, inport(0x71));
    }

    for (i = 0; i < 0x100; ++i) {
        outport(0x70, i);
        outport(0x71, i);
    }

    for (i = 0; i < 0x100; ++i) {
        outport(0x70, i);
        printk("%x: %x\n", i, inport(0x71));
    }

    return 0;
}

static void __exit xbiospwd_exit(void)
{
    printk("[%s]\n", __func__);
}

module_init(xbiospwd_init);
module_exit(xbiospwd_exit);

