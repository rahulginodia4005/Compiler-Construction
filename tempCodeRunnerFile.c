00, fp)) {
    //     // printf("%s\n\n", data);
    //     line_number++;
    //     for(int i = 0;i<200;i++) {
    //         int ind = 0;
    //         if(data[i] == '<') {
    //             i++;
    //             char *non_terminal = (char*) malloc(50 * sizeof(char));
    //             memset(non_terminal, '\0', 50 * sizeof(char));
    //             int non_terminal_ind = 0;
    //             while(data[i] != '>') {
    //                 non_terminal[non_terminal_ind++] = data[i++];
    //             }
    //             char *newNonTerminal = (char*) malloc(non_terminal_ind * sizeof(char));
    //             memset(newNonTerminal, '\0', non_terminal_ind * sizeof(char));
    //             for(int j = 0;j<non_terminal_ind;j++) {
    //                 newNonTerminal[j] = non_terminal[j];
    //             }
    //             // printf("%d\t%d\n", line_number, HM_search(strToI, newNonTerminal));
    //             free(non_terminal);
    //         }
    //         else if(data[i] == 'T') {
    //             char *terminal = (char*) malloc(50 * sizeof(char));
    //             memset(terminal, '\0', 50 * sizeof(char));
    //             int terminal_ind = 0;
    //             while(data[i] != ' ' && data[i] != '\n') {
    //                 terminal[terminal_ind++] = data[i++];
    //             }
    //             i--;
    //             char *newTerminal = (char*) malloc(terminal_ind * sizeof(char));
    //             memset(newTerminal, '\0', terminal_ind * sizeof(char));
    //             for(int j = 0;j<terminal_ind;j++) {
    //                 newTerminal[j] = terminal[j];
    //             }
    //             // printf("%d\t%d\n", line_number, HM_search(strToI, newTerminal));
    //             free(terminal);
    //         }
    //         else if(data[i] == '|') {

    //         }
    //         else if(data[i] == '\n'){
    //             break;
    //         }