#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "util.h"
#include "mem.h"

void* alloc(int n) {
    int *ptr = (int *) mem_alloc(n * sizeof(int));
    if (ptr == NULL_POINTER) {
        print_string("Memory not allocated.\n");
    } else {
        // Get the elements of the array
        for (int i = 0; i < n; ++i) {
//            ptr[i] = i + 1; // shorthand for *(ptr + i)
        }

        for (int i = 0; i < n; ++i) {
//            char str[256];
//            int_to_string(ptr[i], str);
//            print_string(str);
        }
//        print_nl();
    }
    return ptr;
}

void start_kernel(int argc, char **argv) {
    clear_screen();
    print_string("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print_string("Enabling external interrupts.\n");
    asm volatile("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();

    print_string("Initializing dynamic memory.\n");
    init_dynamic_mem();

    clear_screen();

    print_string("init_dynamic_mem()\n");
    print_dynamic_node_size();
    print_dynamic_mem();
    print_nl();

    int *ptr1 = alloc(5);
    print_string("int *ptr1 = alloc(5)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr2 = alloc(10);
    print_string("int *ptr2 = alloc(10)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr1);
    print_string("mem_free(ptr1)\n");
    print_dynamic_mem();
    print_nl();

    int *ptr3 = alloc(2);
    print_string("int *ptr3 = alloc(2)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr2);
    print_string("mem_free(ptr2)\n");
    print_dynamic_mem();
    print_nl();

    mem_free(ptr3);
    print_string("mem_free(ptr3)\n");
    print_dynamic_mem();
    print_nl();

    print_string("Seting up storage...\n");
    for (int i = 0; i == 20; ++i) {
        print_nl();
    }
    print_string("Storage setup.\n");
    print_nl();

    print_string("Welcome to AOS user!\n");
    print_string("> ");
}

void execute_command(char *input) {
    int arr_size = 512;
    int* arr[512];
    if (compare_string(input, "EXIT") == 0) {
        print_string("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    else if (compare_string(input, "ABOUT") == 0){
        print_string("Welcome to AOS.\n");
        print_string("The greatest OS.\n");
        print_string("There is no GUI or DESKTOP.\n");
        print_string("Have fun :)\n");
        print_string("> ");
    }
    else if (compare_string(input, "HELP") == 0) {
        print_string("EXIT\n");
        print_string("ABOUT\n");
        print_string("HELP\n");
        print_string("TOUCH\n");
        print_string("  FILE\n");
        print_string("      Usage: TOUCH FILE\n");
        print_string("> ");

    }
    else if (compare_string(input, "TOUCH") == 0) {
        print_string("This needs to be used with another arg.\n");
        print_string("Args:\n");
        print_string("FILE\n");
        print_string("  Usage: TOUCH FILE\n");
        print_string("> ");
    }
    else if (compare_string(input, "TOUCH FILE") == 0) {
        arr[0] = 1;
        print_string("WORK IN PROGRESS");
        print_string("\n");
        print_string("> ");
    }
    else if (compare_string(input, "HIDE") == 0) {
        clear_screen();
        print_string("> ");
    }
    else {
    print_string("Unknown command: ");
    print_string(input);
    print_string("\n");
    print_string("> ");
    }
}
