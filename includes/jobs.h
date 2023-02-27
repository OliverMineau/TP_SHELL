
typedef struct Jobs Jobs;
struct Jobs {
    char *name;
    int pid;
    int num;
    Jobs *next;
};


void addJob(Jobs **jobs, char *name, int pid);

Jobs *findJobByName(Jobs *jobs, char *name);

Jobs *findJobByPID(Jobs *jobs, int pid);

int deleteJob(Jobs **jobs, Jobs *del);

void printJobs(Jobs *jobs);