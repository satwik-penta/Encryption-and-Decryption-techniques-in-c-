#include<stdio.h>
#include<string.h>
void removeSpaces(char text[])
{
    int i,j=0;
    for(i=0; text[i]!='\0'; i++)
    {
        if(text[i]!=' ' && text[i]!='\n')
        {
            text[j]=text[i];
            j++;
        }
    }
    text[j]='\0';
}

void encrypt(char text[],char encrypted[],int rails)
{
    int n=strlen(text);
    int k=0;

    for(int r=0;r<rails;r++)
    {
        int row=0;
        int direction=1;

        for(int i=0;i<n;i++)
        {
            if(row==r)
            {
                encrypted[k]=text[i];
                k++;
            }

            if(row==rails-1)
                direction=-1;

            if(row==0)
                direction=1;

            row=row+direction;
        }
    }

    encrypted[k]='\0';
}

void decrypt(char encrypted[],char decrypted[],int rails)
{
    int n=strlen(encrypted);

    int pattern[200];
    int count[20]={0};
    int pos[20]={0};

    int row=0;
    int direction=1;
    int k=0;

    for(int i=0;i<n;i++)
    {
        pattern[i]=row;
        count[row]++;

        if(row==rails-1)
            direction=-1;

        if(row==0)
            direction=1;

        row=row+direction;
    }

    for(int r=0;r<rails;r++)
    {
        pos[r]=k;
        k=k+count[r];
    }

    for(int i=0;i<n;i++)
    {
        int r=pattern[i];

        decrypted[i]=encrypted[pos[r]];
        pos[r]++;
    }

    decrypted[n]='\0';
}

int main()
{
    char text[200];
    char result[200];

    int rails;
    int choice;

    printf("Enter the text : ");
    fgets(text,sizeof(text),stdin);

    removeSpaces(text);

    printf("Text after removing spaces : %s\n",text);

    printf("Enter the number of rails : ");
    scanf("%d",&rails);

    if(rails<2 || rails>strlen(text))
    {
        printf("Invalid number of rails");
        return 0;
    }

    printf("Enter your choice\n1.Encryption\n2.Decryption\n");
    scanf("%d",&choice);

    if(choice==1)
    {
        encrypt(text,result,rails);

        printf("Encrypted message : %s",result);
    }
    else if(choice==2)
    {
        decrypt(text,result,rails);

        printf("Decrypted message : %s",result);
    }
    else
    {
        printf("Invalid input");
    }

    return 0;
}