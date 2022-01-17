/*
ESC190 Lab 1
Author: Hitansh Bhatt
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/* Part 1: Splitting Bills */
double split_bill(double base_amount , double tax_rate , double tip_rate , int num_people) {
    double base_tax, tip_tax, final_amt, final_tax, split;
    base_tax = (base_amount*tax_rate);
    //printf("%.2f.\n", base_tax);
    tip_tax = ((base_amount + base_tax)*tip_rate);
    //printf("%.2f.\n", tip_tax);
    final_tax = base_tax + tip_tax;
    //printf("%.2f.\n", final_tax);
    final_amt = (base_amount + final_tax);
    //printf("%.2f.\n", final_amt);
    split = (final_amt/num_people);
    //printf("%.2f.\n", final_amt);

    double check_final = roundf(final_amt * 100) / 100; 
	double check_split = roundf(split * 100) / 100; //round result to nearest cent
	
	if ((check_split * num_people) < check_final) {
		return split + 0.01; //round up a cent if needed
	}
	else {
		return split; 
	}
}

/* Part 2: Adjusting Pizza Prices */
double adjust_price(double original_price) {
    double adj_price, exponent;
    exponent = 0.5;
    int CONSTANT = 10;
    adj_price = CONSTANT*(pow(original_price, exponent));
    return adj_price;
}

/* Part 3: Picky Eating*/
int sandy_eats (char menu_item []) {

	for (int i = 0; menu_item[i]; i++){
		menu_item[i] = tolower(menu_item[i]); //make entire item lowercase 
	}

	char *p; //pointers
	char *q;
	char *r;
	char *s;

	p = strchr (menu_item, 'j');
	q = strchr (menu_item, 'k');
	r = strchr (menu_item, 'l');
	s = strstr (menu_item, "fish");
	
	int count = 0;
	
	for (int i = 0; i < strlen(menu_item); i++) {
		if(menu_item[i] != ' ') 
        {
			count++; 
		}
	}
	
	if (p || q || r || s || (count % 2!= 0)) 
    {
		return 0;
	} else 
		return 1;
}

/* Part 4: Just Thinking About Fish */
void imagine_fish(char thing []){
    //char temp[50];
    //strcpy(temp, thing);
    char concat[] = "fish";
    strcat(thing, concat);
    //printf("Part 4: Just imagine, a %s\n", temp);
}

/*int main() {
    float amt = split_bill (50.01 , 0.13, 0.15, 2);
    printf("Part 1: The split will be: $%.1f\n", amt);

    char test_p4 [30] = "zebra";
    imagine_fish(test_p4);
    //printf("Just imagine , a %s!\n", test_p4 );

    char test_food [] = "Three Cheese Pizza";
    int test_p3 = sandy_eats(test_food );
    if (test_p3 == 0){
    printf("Sandy would NOT eat '%s '.\n", test_food );
    }
    else {
    printf("Sandy would eat '%s '.\n", test_food );
    }
    // Sandy would eat ‘Three Cheese Pizza ’.
}*/
