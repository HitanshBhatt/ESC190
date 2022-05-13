#include "a2.h"

//declare functions
char * decimal_to_binary(int num);
int check(int num);
int calc_min(int a, int b, int c);
//int find(int n, int arr[], int len);


//works!!!
int bitwise_xor(int value){
    int output;
    output = value ^ KEY;
    return output; 
}

char *xor_encrypt(char c){
    return decimal_to_binary(bitwise_xor(c));
}

char * decimal_to_binary(int num){
    char *bin = malloc(sizeof(char) * 8);

    for (int i = 0; i < 7; i++) 
    {
        bin[i] = ((num >> (6 - i)) & 1) + 48;
    }

    bin[7] = '\0';

    return bin;
}


char xor_decrypt(char *s){
    int num = 0;
    for (int i = 0; i < 7; i++) 
    {
        num += (s[i] - 48) << (6 - i);
    }
    return bitwise_xor(num);
}

/*int find(int n, int arr[], int len){
    for (int i = 0; i < len; i++){
        if (arr[i] == n)
        {
            return 1;
        }
    }
    return 0;
}
char *gen_code(char *msg)
{
    char* code = (char*)malloc(sizeof(char) * (257));
    memset(code, '0', sizeof(char) * (257));

    char* bin;
    int c_index = 0, repeat, i, j, k;

    //all indexes with values of 0 to generate code
    int z_index[] = {17, 18, 19, 28, 29, 30, 33, 35, 44, 46, 49, 50, 51, 60, 61, 62, 193, 194, 195, 209, 211, 225, 226, 227};
    //all index with values of 1 to generate code
    int o_index[] = {0, 1, 2, 3, 4, 11, 12, 13, 14, 15, 16, 20, 27, 31, 32, 
                    34, 36, 43, 45, 47, 48, 52, 60, 64, 65, 66, 67, 68, 69, 
                    76, 77, 78, 79, 80, 176, 177, 178, 179, 180, 192, 196, 208,
                    210, 212, 224, 228, 240, 241, 242, 243, 244, 255};
    
    //for 0 values:
    int temp_z = (sizeof(z_index))/(sizeof(int));
    //for 1 values:
    int temp_o = (sizeof(o_index))/(sizeof(int));

    for (i = 0; i < temp_z; i++)
    {
        code[z_index[i]] = '0';
    }
    
    for (j = 0; j < temp_o; j++)
    {
        code[o_index[j]] = '1';
    }
    
    for (k = 0; k < strlen(msg) + 1; k++)
    {
        bin = xor_encrypt(msg[k]);
        repeat = 0;

        while (repeat < 7)
        {
            if (find(c_index, z_index, temp_z) || find(c_index, o_index, temp_o))
            {
                c_index++;     //increment code index
                continue;
            } 
            else 
            {
                code[c_index] = bin[repeat];
                c_index++;
                repeat++;
            }
        }
        free(bin);
    }

    code[256] = '\0';
    return code;
}*/

char *gen_code(char *msg){
    char* code = (char*)malloc(sizeof(char) * (257));
    
    int len = strlen(msg);

    //char* bin;
    int idx = 0, repeat, i, j, k;

    //all indexes with values of 0 to generate code
    int z_index[] = {17, 18, 19, 28, 29, 30, 33, 35, 44, 46, 49, 50, 51, 60, 61, 62, 193, 194, 195, 209, 211, 225, 226, 227};
    //all index with values of 1 to generate code
    int o_index[] = {0, 1, 2, 3, 4, 11, 12, 13, 14, 15, 16, 20, 27, 31, 32, 
                    34, 36, 43, 45, 47, 48, 52, 59, 63, 64, 65, 66, 67, 68, 75, 
                    76, 77, 78, 79, 176, 177, 178, 179, 180, 192, 196, 208,
                    210, 212, 224, 228, 240, 241, 242, 243, 244, 255};
    
    //for 0 values:
    int temp_z = (sizeof(z_index))/(sizeof(int));
    //for 1 values:
    int temp_o = (sizeof(o_index))/(sizeof(int));

    for (i = 0; i < 256; i++)
    {
        code[i] = 't';
    }

    for (i = 0; i < temp_z; i++)
    {
        code[z_index[i]] = '0';
    }
    
    for (j = 0; j < temp_o; j++)
    {
        code[o_index[j]] = '1';
    }
    
    for (i = 0; i < (len + 1); i++)
    {
        char* bin = xor_encrypt(msg[i]);
        j = 0;
        char charac = bin[j];

        while (charac != '\0')
        {
            if (code[idx] == 't')
            {
                code[idx] = charac;
                j++;
                charac = bin[j];
            }

            idx++;
        }

        free(bin);

        bin = NULL;
    }

    for (idx = idx; idx < 256; idx++)
    {
        if(code[idx] == 't')
        {
            code[idx] = '0';
        }
    }

    code[256] = '\0';
    
    return code;
}

//done
char *read_code(char *code){
    int max_encoded_message = 180, max_num = 256, max_size = 25;

    char* message = malloc(sizeof(char) * 180);
    char* decrypt = malloc(sizeof(char) * max_size);
    char* enc; //do sizeof(char) * 7 because increment 7 bits at a time
    char dec;
    int counter = 0, i;

    for (i = 5; i < max_num; i++)
    {
        if (check(i) == 1)
        {
            message[counter] = code[i];
            counter ++;
        }
    }

    for (i = 0; i < (max_size + 1); i++)
    {
        enc = malloc(sizeof(char) * 7);
        strncpy(enc, (message + (i * 7)), 7);

        dec = xor_decrypt(enc);

        decrypt[i] = dec;

        free(enc);

        //to stop the for loop at the null terminating character:
        if (dec == '\0')
        {
            break;
        }
    }

    free(message);

    return decrypt;
}

int check(int num)
{
    if((num > 4 && num < 11) || (num > 20 && num < 27) || (num > 36 && num < 43) || (num > 52 && num < 59)
    || (num > 68 && num < 75) || (num > 79 && num < 176) || (num > 180 && num < 192) || (num > 196 && num < 208)
    || (num > 212 && num < 224) || (num > 228 && num < 240) || (num > 245 && num < 255))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char *compress(char *code){
    int max_size = 65, max_template = 256, c_index = 0, hexamdecimal = 0, sc_index = 0, counter = 0;

    char* c = (char*)malloc(sizeof(char) * max_size);
    c[64] = '\0';        //set value at last index to null terminating character

    while (sc_index <= max_template)
    {
        if (counter == 4)
        {
            if (hexamdecimal < 10)
            {
                c[c_index] = (char)(hexamdecimal + 48);
            }
            else
            {
                c[c_index] = (char)(hexamdecimal + 55);
            }

            c_index++;

            counter = 0;
            hexamdecimal = 0;

            if (sc_index == max_template)
            {
                break;      //to break at last index
            }

            continue;
        }
        if (code[sc_index] == '1')
        {
            hexamdecimal += pow(2, 3-counter);  //convert to hexadecimal if 1
        }

        counter++;
        sc_index++;

    }

    return c;
}

char *decompress(char *code){
    int sc_index = 0, hexamdecimal, max_template = 256, max_c = 64, i, j, check;

    char* c = (char*)malloc(sizeof(char) * max_template + 1);
    
    //hexadecimal conversion
    for (i = 0; i < max_c; i++)
    {
        hexamdecimal = (code[i] > 64) ? (code[i]-55) : (code[i]-48);
        
        for (int j = 0; j < 4; j++)
        {
            check = (hexamdecimal) / ((int)pow(2, 3-j));

            c[sc_index] = (check == 1) ? '1' : '0';

            hexamdecimal = hexamdecimal - ((c[sc_index] - 48) * pow(2, 3-j));

            sc_index++;
        }
    }

    c[max_template] = '\0';

    return c;
}

int calc_ld(char *sandy, char *cima)
{
    int i, j, k, s_len, c_len, val;

    s_len = strlen(sandy);
    c_len = strlen(cima);

    int **matrix = (int**)malloc(sizeof(int*) * (s_len + 1));
    
    for (i = 0; i < (s_len + 1); i++)
    {
        matrix[i] = (int*)malloc(sizeof(int) * (c_len + 1));
    }

    //set the values of the first row in ascending order
    for (i = 0; i < (s_len + 1); i++)
    {
        matrix[i][0] = i;
    }

    // set the values of the first column in ascending order
    for (i = 1; i < (c_len + 1); i++)
    {
        matrix[0][i] = i;
    }

    for (j = 1; j < (s_len + 1); j++){
        for (k = 1; k < (c_len + 1); k++){
            if (sandy[j-1] == cima[k-1])
            {
                matrix[j][k] = matrix[j-1][k-1];
            } 
            else 
            {
                matrix[j][k] = 1 + (calc_min(matrix[j-1][k-1], matrix[j-1][k], matrix[j][k-1]));
            }
        }
    }

    val = matrix[s_len][c_len];
    
    // free the  matrix
    for ( i = 0; i < (s_len + 1); i++)
    {
        free(matrix[i]);
    }

    free(matrix);

    return val;
}

int calc_min(int a, int b, int c)
{
    int minimum;

    if (a <= b && a <= c)
    {
        minimum = a;
    }
    else if (b <= a && b <= c)
    {
        minimum = b;
    }
    else if (c <= a && c<= b)
    {
        minimum = c;
    }

    return minimum;
}