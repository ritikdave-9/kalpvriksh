#include <stdio.h>
#include <stdlib.h>

int compare_string(char *str1, char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            return 0;
        }
        str1++;
        str2++;
    }

    return 1;
}

void copy_string(char *str1, char *str2)
{
    while (*str2 != '\0')
    {
        *str1 = *str2;
        str1++;
        str2++;
    }
}

typedef struct node
{
    char data[10];
    struct node *next;
} node;

node *createNode(char *str)
{
    node *newnode = (node *)malloc(sizeof(node));
    copy_string(newnode->data, str);
    newnode->next = NULL;
    return newnode;
}

node *create_list()
{
    node *temp = NULL;
    node *head = NULL;
    char str[10];
    char *end = "end";
    printf("enter empolye ids and enter \"end\" to stop insertion\n");
    while (1)
    {

        scanf("%s", str);
        if (compare_string(str, end))
        {
            break;
        }
        node *newnode = createNode(str);
        if (!head)
        {
            head = newnode;
        }
        else
        {
            temp->next = newnode;
        }
        temp = newnode;
    }
    return head;
}

void printList(node *head)
{
    node *temp = head;

    while (temp)
    {
        printf("%s->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

node *intersection(node *node1, node *node2)
{

    node *head1 = node1;
    node *head2 = node2;

    node *head = NULL;

    node *temp = NULL;

    while (head1)
    {
        head2 = node2;

        while (head2)
        {
            if (compare_string(head1->data, head2->data))
            {

                node *newnode = createNode(head1->data);

                if (!head)
                {
                    head = newnode;
                }
                else
                {
                    temp->next = newnode;
                }
                temp = newnode;
                break;
            }
            head2 = head2->next;
        }
        head1 = head1->next;
    }

    return head;
}

node *union_list(node *node1, node *node2)
{
    node *head1 = node1;
    node *temp = node1;
    node *head2 = node2;
    node *common = intersection(head1, head2);

    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = head2;
    node *prev = temp;

    while (common)
    {
        head2 = temp->next;
        prev = temp;
        while (head2)
        {
            if (compare_string(common->data, head2->data))
            {
                prev->next = head2->next;

                break;
            }
            prev = head2;
            head2 = head2->next;
        }
        common = common->next;
    }
    return node1;
}

int main()
{

    node *head1 = create_list();
    printList(head1);
    node *head2 = create_list();
    printList(head2);

    node *common = intersection(head1, head2);

    printList(common);
    node *all = union_list(head1, head2);
    printList(all);
}