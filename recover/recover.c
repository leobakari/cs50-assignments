#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int input_is_valid(int num_arguments, char *filename);
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Something went wrong! Please provide 1 cmd argument with the card.");
        return 1;
    }
    else
    {
        FILE *card = fopen(argv[1], "r");

        if (card == NULL)
        {
            printf("Something went wrong! Please provide 1 cmd argument with the card.");
            return 1;
        }
        else
        {
            // Define a byte as type
            typedef uint8_t BYTE;
            // Create buffer
            BYTE buffer[BLOCK_SIZE];
            FILE *output_img;
            int img_count = 0;
            char img_name[8];

            while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
            {
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && (buffer[3] & 0xf0) == 0xe0)
                {
                    if (img_count != 0)
                    {
                        fclose(output_img);
                    }
                    sprintf(img_name, "%03i.jpg", img_count);
                    img_count++;
                    output_img = fopen(img_name, "w");
                    fwrite(buffer, 1, BLOCK_SIZE, output_img);
                }
                else if (img_count >= 1)
                {
                    fwrite(buffer, 1, BLOCK_SIZE, output_img);
                }
            }
            fclose(card);
            fclose(output_img);
        }
    }
    return 0;
}