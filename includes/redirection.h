#ifndef __REDIRECTION_H__
#define __REDIRECTION_H__


void redirectionEntree(char *inNom, int *prevCmdPipe, int deb, int *fd_in);
void redirectionSortie(char *outNom, int *nextCmdPipe, int fin, int *fd_out);


#endif