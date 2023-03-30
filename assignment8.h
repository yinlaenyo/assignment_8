//
// Created by National Cyber City on 2/20/2023.
//

#ifndef DIPLEVEL1_ZOOM_ONLINE_BANK_H
#define DIPLEVEL1_ZOOM_ONLINE_BANK_H

#include "stdio.h"
#include "stdlib.h"
#define SIZE 1000 // symbolic constant
struct trans{
    char note[200];
};
//id name nrc email password pOrb loan_status monthly_income
// loan_amount loan_rate accountStatus account_Level phNumber current_amount address TransRC
struct data{
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char pOrb[20]; // personal or business
    char loan_s[2]; // loan status
    unsigned int monthly_income;
    unsigned int loan_amount; // ဘယ်လောက်ချေးထားသလဲ
    float loan_rate;
    char acc_s[10]; //account status
    int acc_level; // copy
    unsigned long long int phNumber;
    unsigned int cur_amount; //current amount
    char address[100];
    int transAmoLimitPerDay; // transAmountLimitPerDay minimize for our project 5min
    struct trans trc[100];

};

struct data db[SIZE];

// Global Variable Declaration

int users=0;
int gValid=-1;
int emailExist=-1;
int pass_Exist=-1;
int two_charArray=-1;
int nrc_valid = -1;
int strongPass=-1;
int phone_valid=-1;
int phone_found=-1;
int phone_format_valid=-1;


// global array
int space_array[30];
char int_to_char_array_data[50];
unsigned int charArray_to_unsignedInt_data=0;





// For Function Declaration
void welcome();
void login();
void userSector();
void loadingAllDataFromFile();
void printingAllData();
void registration();
int charCounting(char toCount[50]);
void myGmailValidation(char toValidate[50]);
void emailExistChecking(char toCheck[50]);
void compare_two_charArray(char first[50] , char second[50]);
void nrc_validation(char nrc_toCheck[50]);
void myStrongPassword(char pass[50]);
void phone_validation(unsigned long long int phone);
void phone_format_checking(unsigned long long int phone_toCheck);
void copy_two_char_array(char receiver[200] ,char transmitter[200] );
void finding_phone_number(unsigned int tofind);
void transfer_money(int transfer , int receiver , unsigned int amount);
void recording_alldata_toFile();
void integer_to_char(unsigned long long int value);
unsigned long long int charArray_to_unsigned_fun(char charArray[]);



void welcome(){

    int option=0;
    printf("Welcome to our Bank!\n");
    printf("Press 1 to Login!\nPress 2 to Register!\nPress 3 to Exit!:::");
    scanf("%d",&option);

    if(option == 1){

        login();

    } else if(option == 2){
        registration();

    } else if( option == 3){

        recording_alldata_toFile();
        exit(1);
    } else {
        welcome();
    }

}

void login(){

    char l_email[50];
    char l_pass[50];
    emailExist=-1;
    two_charArray=-1;

    while (emailExist == -1 || two_charArray==-1){
        printf("This is login:\n");

        printf("Enter your email:");
        scanf(" %[^\n]",&l_email[0]);
        printf("Enter your password:");
        scanf(" %[^\n]",&l_pass[0]);
        emailExistChecking(l_email);
        compare_two_charArray(db[emailExist].password,l_pass);

        if(emailExist == -1 || two_charArray==-1){
            emailExist=-1;
            two_charArray=-1;
            printf("Your login credential was wrong:\n");
        }
    }
    printf("Welcome Mr/Mrs: %s\n",db[emailExist].name);
    printf("Your current amount : %u\n",db[emailExist].cur_amount);
    userSector();

}


void userSector(){

    int user_option=0;
    unsigned int phone=0;
    unsigned int amount_to_transfer=0;
    printf("This is user Sector\n");
    printf("Press 1 to Transfer Money:\nPress 2 to Withdraw:\nPress 3 to update your information\nPress 4 Cash in :\nPress 5 to Loan:\nPress 6 to view your history:\nPress 7 Exit");
    scanf("%d",&user_option);

    if(user_option==1){
        printf("This is for Transfer Option:\n");

        phone_found=-1;

        while (phone_found==-1){
            printf("Enter receive phone number : ");
            scanf("%u",&phone);
            finding_phone_number(phone);
            if(phone_found==-1){
                printf("Phone number does not belong to any user:\n");
            }

        }
        printf("Are u sure to send for %s email: %s:\n",db[phone_found].name,db[phone_found].email);

        while (amount_to_transfer<db[emailExist].cur_amount){

            printf("Enter your amount: to transfer:");
            scanf("%u",&amount_to_transfer);

            if(db[emailExist].cur_amount-1000>amount_to_transfer){
                break;
            } else{
                printf("not sufficient balance:\n");
                amount_to_transfer=0;
            }


        }
        two_charArray=-1;
        char tran_pass[50];
        while (two_charArray==-1){
            printf("Enter password to proceed transaction:");
            scanf(" %[^\n]",&tran_pass[0]);
            compare_two_charArray(db[emailExist].password,tran_pass);

            if(two_charArray==-1){
                printf("Wrong credential:\n");
            }


        }

        transfer_money(emailExist,phone_found,amount_to_transfer);
        printingAllData();
        userSector();


    } else if(user_option==7){
        welcome();
    }


}

void transfer_money(int transfer , int receiver , unsigned int amount){

    printf("loading to transfer.....\n");
    db[transfer].cur_amount = db[transfer].cur_amount-amount;
    db[receiver].cur_amount = db[receiver].cur_amount+amount;
    printf("transaction complete!");



}



//id name nrc email password pOrb loan_status monthly_income
// loan_amount loan_rate accountStatus account_Level phNumber current_amount address TransRC
void loadingAllDataFromFile(){

    FILE *fptr = fopen("ncc_db1.txt","r");

    if( fptr == NULL){
        printf("Error at loadingAllDataFromFile Function!\n");
    } else{
        for(int ncc=0; ncc<SIZE ; ncc++){

            fscanf(fptr ,"%u%s%s%s%s%s%s%u%u%f%s%d%llu%u%s%d",&db[ncc].id,&db[ncc].name,&db[ncc].nrc,&db[ncc].email,
                   &db[ncc].password,&db[ncc].pOrb,&db[ncc].loan_s,&db[ncc].monthly_income,
                   &db[ncc].loan_amount ,&db[ncc].loan_rate , &db[ncc].acc_s ,&db[ncc].acc_level,
                   &db[ncc].phNumber , &db[ncc].cur_amount,&db[ncc].address ,&db[ncc].transAmoLimitPerDay);

            for(int gcc=0; gcc<space_array[ncc]-15 ; gcc++){
                fscanf(fptr,"%s",&db[ncc].trc[gcc].note);
            }



            if(db[ncc].email[0] == '\0'){
                break;
            }

            users++;

        }

    }

    fclose(fptr);

}
void printingAllData(){

    for(int ncc=0; ncc<users ; ncc++){


        printf("%u-%s-%s-%s-%s-%s-%s-%u-%u-%f-%s-%d-%llu-%u-%s-%d",db[ncc].id,db[ncc].name,db[ncc].nrc,db[ncc].email,db[ncc].password,
               db[ncc].pOrb, db[ncc].loan_s,db[ncc].monthly_income,db[ncc].loan_amount ,db[ncc].loan_rate , db[ncc].acc_s ,db[ncc].acc_level,
               db[ncc].phNumber , db[ncc].cur_amount,db[ncc].address,db[ncc].transAmoLimitPerDay);

        for(int gcc=0; gcc<space_array[ncc]-15 ; gcc++){
            printf("-%s",&db[ncc].trc[gcc].note[0]);
        }
        printf("\n");
    }

}

void recording_alldata_toFile(){
    FILE *fptr = fopen("ncc_db1.txt","w");
    if(fptr==NULL){
        printf("cannot open file to record:\n");

    }

    for(int ncc=0; ncc<users; ncc++){
        fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%s%c%s%c%u%c%u%c%f%c%s%c%d%c%llu%c%u%c%s%c%d",db[ncc].id,' ',db[ncc].name,' ',db[ncc].nrc,' ',db[ncc].email,' ',db[ncc].password,
                ' ',db[ncc].pOrb, ' ',db[ncc].loan_s,' ',db[ncc].monthly_income,' ',db[ncc].loan_amount ,' ',db[ncc].loan_rate ,' ', db[ncc].acc_s ,' ',db[ncc].acc_level,
                ' ',db[ncc].phNumber , ' ',db[ncc].cur_amount,' ',db[ncc].address,' ',db[ncc].transAmoLimitPerDay);

        for(int gcc=0; gcc<space_array[ncc]-15 ; gcc++){
            fprintf(fptr," %s",&db[ncc].trc[gcc].note[0]);
        }
        fprintf(fptr,"%c",'\n');
    }



}


void registration(){

    char reEmail[50];
    char re_name[50];
    char re_nrc[50];
    char re_pass[50];
    unsigned long long int re_phone=0;

    printf("This is NCC Bank User Registration!\n");
    printf("Enter your email:");
    scanf(" %[^\n]",&reEmail[0]);
    gValid=-1;
    myGmailValidation(reEmail);
    if( gValid != -1){

        emailExist=-1;
        emailExistChecking(reEmail);

        if( emailExist == -1 ){

            printf("Your email is valid!\n");
            printf("Enter your name:");
            scanf(" %[^\n]",&re_name[0]);
            nrc_valid=-1;
            while (nrc_valid==-1){
                printf("Enter your NRC:");
                scanf(" %[^\n]",&re_nrc[0]);

                nrc_validation(re_nrc);
                if(nrc_valid == -1){
                    printf("Your NRC Format was Not Valid!\n");
                }

            }
            printf("Your NRC Format was Valid!\n");
            strongPass=-1;
            while (strongPass == -1){
                printf("Enter your password!:");
                scanf(" %[^\n]",&re_pass[0]);
                myStrongPassword(re_pass);
                if(strongPass == -1){
                    printf("Your Password Format too weak and Try Again!\n");
                }
            }
            printf("Your password format was valid and saved!\n");

            phone_valid=-1;
            phone_format_valid=-1;
            while (phone_valid==-1 || phone_format_valid==-1){
                printf("[X]Enter your Phone Number:");
                scanf("%llu",&re_phone);

                phone_format_checking(re_phone);
                if(phone_format_valid==-1){
                    printf("Your phone number format is not valid : \n");
                }
                phone_validation(re_phone);

                if(phone_valid == -1){

                    printf("[-]Your phone number is already registered:\n");
                }

            }
            printf("[+] Your phone is correct and saved!\n");

            printf("[+] Enter your monthly income:");
            scanf("%u",&db[users].monthly_income);
            printf("[+] Enter your current amount:");
            scanf("%u",&db[users].cur_amount);

            printf("[+]Enter your address");
            scanf(" %[^\n]",&db[users].address[0]);

            copy_two_char_array(db[users].pOrb , db[2].pOrb);
            copy_two_char_array(db[users].loan_s,db[2].loan_s);

            db[users].loan_amount= db[2].loan_amount;
            db[users].phNumber= re_phone;
            db[users].loan_rate= db[2].loan_rate;
            copy_two_char_array(db[users].acc_s,db[2].acc_s);
            db[users].acc_level= db[2].acc_level;
            db[users].transAmoLimitPerDay= db[2].transAmoLimitPerDay;
            copy_two_char_array(db[users].trc[0].note,db[2].trc[0].note);
            copy_two_char_array(db[users].email,reEmail);
            copy_two_char_array(db[users].nrc,re_nrc);
            copy_two_char_array(db[users].password,re_pass);
            copy_two_char_array(db[users].name,re_name);

//            char pOrb[20]; // personal or business
//            char loan_s[2]; // loan status
//            unsigned int monthly_income;x
//            unsigned int loan_amount; // ဘယ်လောက်ချေးထားသလဲ
//            float loan_rate;
//            char acc_s[10]; //account status
//            int acc_level; // copy
//            unsigned int phNumber;x
//            unsigned int cur_amount; //current amountx
//            char address[100];x
//            int transAmoLimitPerDay; // transAmountLimitPerDay minimize for our project 5min
//            struct trans trc[100];
            db[users].id = users+1;
            users++;
            printingAllData();
            welcome();

        } else{

            printf("Your gmail already taken!\n");
            registration();

        }

    } else{
        printf("Your gmail format not valid!\n");
        registration();
    }

}

int charCounting(char toCount[50]){ // toCount[50] = {'w','i','n','@'gmail.com,'\0' , '\0'}
    int charCount = 0;
    for(int gcc=0; gcc<50 ; gcc++){

        if( toCount[gcc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void myGmailValidation(char toValidate[50]){

    // winhtut@gmail.com
    int toEndPoint = charCounting(toValidate);
    char form[10]={'@','g','m','a','i','l','.','c','o','m'};
    int count=0;

    for(int i=0; i<toEndPoint; i++){

        if(toValidate[i] == '@' || toValidate[i] ==' '){
            break;
        }else{
            count++;
        }

    }
    int tocheck=0;
    for( int i=0 ; i< toEndPoint ; i++){

        if( toValidate[count] != form[i]){
            break;
        } else{
            count++;
            tocheck++;
        }
    }

    if( tocheck == 10){
        gValid=1;
    }

}

void emailExistChecking(char toCheck[50]){

    int toCheckCount = charCounting(toCheck);
    int sameCounting=0;

    for(int ncc=0; ncc<users ; ncc++){
        int dbEmailCount = charCounting(db[ncc].email);

        sameCounting=0;
        if( toCheckCount == dbEmailCount){

            for(int gcc=0; gcc<toCheckCount ; gcc++){

                if(toCheck[gcc] != db[ncc].email[gcc] ){
                    break;
                } else{
                    sameCounting++;
                }

            }

        }

        if(toCheckCount == sameCounting){

            emailExist = ncc;
        }
    }
}

void nrc_validation(char nrc_toCheck[50]){

    int nrc_counter =charCounting(nrc_toCheck);
    int nrc_char=0;

    for(register int i=0; i< nrc_counter ; i++){

        if( nrc_toCheck[i] == ')'){
            break;
        }
        nrc_char++;
    }

    for(int i=0; i<3; i++){

        two_charArray=-1;
        compare_two_charArray(nrc_toCheck,db[i].nrc);
        if(two_charArray == 1){
            nrc_valid=1;
            break;
        }

    }
}

void compare_two_charArray(char first[50] , char second[50]){

    int first_counter =  charCounting(first);
    int second_counter = charCounting(second);
    int same_counter = 0;

    if( first_counter == second_counter) {
        for (register int i = 0; i < first_counter; i++) {
            if(first[i] != second[i]){
                break;
            }
            same_counter++;
        }

        if( first_counter == same_counter){
            two_charArray = 1;
        }
    }

}

void myStrongPassword(char pass[50]){

    int i=0;
    int special=0;
    int numberChar=0;
    int capChar=0;
    int smallChar=0;
    int pass_counter = charCounting(pass);
    while (strongPass == -1){
        if( i == pass_counter){
            strongPass=-1;
            break;
        }
        if( pass[i] >= 33 && pass[i] <= 42){

            special++;
        } else  if( pass[i] >= 48 && pass[i] <= 57){

            numberChar++;

        } else if( pass[i] >= 65 && pass[i] <= 90){

            capChar++;
        } else if( pass[i] >= 97 && pass[i] <= 122) {

            smallChar++;
        }
        i++;
        if( special > 0 && numberChar >0 && capChar > 0 && smallChar >0){
            strongPass = 1;
        }
    }
}

void phone_validation(unsigned long long int phone){
    int phone_counter=0;
    for(int i=0; i<users ; i++){

        if(phone != db[i].phNumber){

            phone_counter++;
        } else{
            phone_valid=-1;
            break;
        }

    }
    if(phone_counter == users){
        phone_valid=1;
    }

}

void phone_format_checking(unsigned long long int phone_toCheck){

    char phone_toCheck_array[50];

    integer_to_char(phone_toCheck);

    int phone_counter = charCounting(int_to_char_array_data);

    int phone_index=0;

    for(phone_index=0; phone_index<phone_counter ; phone_index++){

        phone_toCheck_array[phone_index]=int_to_char_array_data[phone_index];

    }
    phone_toCheck_array[phone_index]=0;

    if(phone_toCheck_array[0]=='9' && phone_toCheck_array[1]=='5' && phone_toCheck_array[2]=='9'){
        char prefix =phone_toCheck_array[3];

         if (prefix == '2' || prefix== '5'){
            if(phone_counter>=10 && phone_counter<= 12){
                phone_format_valid=1;
            }
         }else if(phone_counter == 12){
             phone_format_valid=1;
         }
    }
}

void integer_to_char(unsigned long long int value){

    FILE *fptr = fopen("100.txt","w");

    if(fptr==NULL){
        printf("file opening error at integer_to_char:\n");
    } else{
        fprintf(fptr,"%llu",value);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("100.txt","r");
    fscanf(fptr2,"%s",&int_to_char_array_data[0]);

}

unsigned long long int charArray_to_unsigned_fun(char charArray[]){
    unsigned long long int data=0;
    FILE *fptr = fopen("100.txt","w");

    if(fptr==NULL){
        printf("file opening error at integer_to_char:\n");
    } else{
        fprintf(fptr,"%s",charArray);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("100.txt","r");
    fscanf(fptr2,"%llu",&data);

    return data;
}
void copy_two_char_array(char receiver[200] ,char transmitter[200] ){


//    for(register int i=0; i<200; i++){
//        receiver[i]='\0';
//    }

    int transmit_counter = charCounting(transmitter);
    for(int i=0; i<transmit_counter; i++){
        receiver[i] = transmitter[i];
    }
}

void finding_phone_number(unsigned int tofind){

    for(int i=0; i<users ; i++){

        if(db[i].phNumber==tofind){
            phone_found=i;
            break;
        }
    }
}


#endif //DIPLEVEL1_ZOOM_ONLINE_BANK_H
