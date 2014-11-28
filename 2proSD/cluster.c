#include "headers.h"

item *CreateItem(item *p)
{	
	p=NULL;
	return(p);
}

item *InsertItem(item *p, int w)
{
	if ( p==NULL ) {
		p = (item *) malloc (sizeof(item)+1);
		p->itemid = w;
		p->next = NULL;
		}
	else 	{
		p->next = InsertItem(p->next, w);
		}
	return(p);
}


item *DeleteItem(item *p, int w)
{	item	*aux=NULL, *throwaway=NULL;

	aux=p;
	if (aux==NULL) 
		return (NULL);
	else {
		if ( aux->itemid == w){
			throwaway=aux;
			aux = aux->next;
			free (throwaway) ;
			throwaway = NULL;
			return(aux);
			}
		else	{
			aux->next=DeleteItem(aux->next, w);
			return(aux);
			}
	}
}

int	IsMemberOfList(item *p, int w)
{	item	*aux=NULL;
	
	aux = p;
	while (aux!=NULL){
		if (aux->itemid == w)
			return(YES);
		aux=aux->next;
		}
	return(NO);
}

