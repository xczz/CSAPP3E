/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/

queue_t *q_new()
{
    queue_t *q=(queue_t*)malloc(sizeof(queue_t));
    if(!q)
        return NULL;
    q->tail=q->head=NULL;
    q->size=0;
    return q;
    /* Remember to handle the case if malloc returned NULL */
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if(!q)
        return;
    list_ele_t *cur=q->head,*next;
    while(cur!=NULL)
    {
        next=cur->next;
        cur->next=NULL;
        free(cur);
        cur=next;
    }
    q->head=NULL;
    q->tail=NULL;
    free(q);
    /* Remember to free the queue structue and list elements */
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    /* What should you do if the q is NULL? */
    if(!q)
        return false;
    /* What if malloc returned NULL? */
    list_ele_t *p=(list_ele_t*)malloc(sizeof(list_ele_t));
    if(!p)
        return false;
    p->value=v;
    p->next=q->head;
    q->head=p;
    ++(q->size);
    if(q->tail==NULL)
        q->tail=p;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if(!q)
        return false;
    list_ele_t *p=(list_ele_t*)malloc(sizeof(list_ele_t));
    if(!p)
        return false;
    p->value=v;
    p->next=NULL;
    if(q->tail==NULL)
    {
        q->head=p;
        q->tail=p;
    }
    else
    {
        q->tail->next=p;
        q->tail=p;
    }
    ++(q->size);
    /* Remember: It should operate in O(1) time */
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if(!q)
        return false;
    if(!q->head)
        return false;
    list_ele_t *p=q->head;
    q->head=p->next;
    if(vp)
        (*vp)=p->value;
    q->size--;
    p->next=NULL;
    if(q->size==0)
        q->tail=NULL;
    free(p);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(!q)
        return 0;
    if(!q->head)
        return 0;
    return q->size;
    /* Remember: It should operate in O(1) time */
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if(q==NULL || q->head==NULL)
        return;
    list_ele_t *before=NULL;
    list_ele_t *cur=q->head;
    list_ele_t *next=cur;
    while(cur!=NULL)
    {
        next=cur->next;
        cur->next=before;
        before=cur;
        cur=next;
    }
    list_ele_t *tmp=q->head;
    q->head=q->tail;
    q->tail=tmp;
}

