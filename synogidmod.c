#include <fcntl.h>
#include <stdio.h>
#include <synosdk/user.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: synogidmod GROUPNAME [gid]\n");
        return 1;
    }

    int modify = argc >= 3 ? 1 : 0;
    char *groupname = argv[1];

    // convert username to uppercase
    int i = 0;
    for (i = 0; groupname[i]; i++ ) {
        groupname[i] = toupper( (unsigned char)groupname[i]);
    }

    gid_t gid;
    if (modify) {
        gid = atoi(argv[2]);
    }

    int groupdb = 0;

    PSYNOGROUP group = NULL;
    int exitCode = 1;

    groupdb = SYNOGroupDbOpen(modify ? O_RDWR : O_RDONLY);
    if (!groupdb) {
        fprintf(stderr, "Failed to open database (permission?).\n");
        goto finish;
    } else {
        printf("Database opened successfully\n");
    }

    if (SYNOGroupDbGet(groupdb, groupname, &group) == -1 || !group) {
        fprintf(stderr, "Group '%s' not found.\n", groupname);
        goto finish;
    }

    printf("Group '%s' has been found: groupname=%s, gid=%d\n", groupname, group->szName, group->nGid);
    if (!modify) {
        fprintf(stderr, "No modifications applied to database\n", groupname);
        exitCode = 0;
        goto finish;
    }

    printf("Modifying '%s' to gid=%d\n", group->szName, gid);

    //SLIBUserShadowAlloc(&shadow, SYNO_SHADOW_UPDATE_USER);
    //if (!shadow) {
    //    fprintf(stderr, "SLIBUserShadowAlloc failed\n");
    //    goto finish;
    //}
    // SYNOGroupAlloc(PSYNOGROUP *ppGroup, const char *szName, gid_t nGid, char **rgszMember);

    group->nGid = gid;
    // SYNOGroupDbSet(PSYNOGROUPDB pdbGroup, const char *szOldNameUpper, const PSYNOGROUP pGroup);
    if (SYNOGroupDbSet(groupdb, groupname, group) == -1) {
        fprintf(stderr, "Update failed\n");
        goto finish;
    }

    printf("Update successfull\n");
    exitCode = 0;
    
    finish:
    if (groupdb) {
        SYNOGroupDbClose(groupdb);
    }
    return exitCode;
}