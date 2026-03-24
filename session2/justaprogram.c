#include <assert.h>
#include <stdio.h>
 
int main(void) {
    int value;
    printf("Enter an integer: ");
    scanf("%d", &value);
    assert(value % 2 == 0);
    printf("You entered %d\n", value);
    return 0;
}