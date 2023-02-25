#ifndef __REDIRECTION_H__
#define __REDIRECTION_H__


int redirectionEntree(char *inNom, int *prevCmdPipe, int deb, int *fd_in);
int redirectionSortie(char *outNom, int *nextCmdPipe, int fin, int deb, int *fd_out);


#endif