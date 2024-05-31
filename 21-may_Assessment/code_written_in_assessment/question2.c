#include<stdio.h>
#include<stdlib.h>

typedef struct employe {
    char* id;
    struct employe * next;

} employe;

employe * createEmploye(char * id){
    employe * newEmp = (employe*)malloc(sizeof(employe));

    newEmp->id = id;

    newEmp->next = NULL;
}

employe * commonIds(employe * head1, employe * head2){
    int flag = 0;
    
    employe * head = createEmploye("0") ;
    employe * head_to_return = head;
    employe * temp1 = head1;
    employe * temp2 = head2;

    while(temp1){
        while(temp2){
            if(temp1->id == temp2->id){
                head->id = temp1->id;

                employe* newEmp = createEmploye("0");
                newEmp->next = NULL;

                head->next = newEmp;
                head = head->next;

                
                
            }
            temp2 = temp2->next;


        }
        temp1 = temp1->next;
    }

    return head_to_return;


}

employe * unionEmploye(employe * head1, employe*head2){
    employe * common_head = commonIds(head1,head2);
    employe * iter_common_head = common_head;
    employe * temp = head1;

    employe * temp2 = head2;

    employe * returnHead = temp;

    int flag = 0;

    
    while(temp->next){
            temp = temp->next;
     }



     while(temp2){
        while(iter_common_head){
            if(temp2->id == iter_common_head->id){
                flag = 1;
                break;
            }
            

        }
        if(flag = 1){
            temp->next = temp2;
            
        }
        temp2 = temp2->next;
        

     }

     return returnHead;




    


   


}

void takeinput(employe * head){
    
}

int main(){

    employe * head1 = (employe * )malloc (sizeof(employe));
        employe * head2 = (employe * )malloc (sizeof(employe));

    employe * temp = head1;
    employe * temp2 = head2;
    char str[20] ;
    while(str!= "end"){
        scanf("%s",temp->id);
        employe * next = createEmploye("0");
        temp->next  = next;
        temp = temp->next;

    } 
    temp->next = NULL;
    while(str!= "end"){
        scanf("%s",str);
        if(str=="end"){
            break;
        }
        temp->id = str;
        employe * next = createEmploye("0");
        temp2->next  = next;
        temp2 = temp2->next;

    }
    temp2->next = NULL;

    employe * intersect = commonIds(head1,head2);
    employe * unionEmps = unionEmploye(head1,head2);
    return 0;




}

