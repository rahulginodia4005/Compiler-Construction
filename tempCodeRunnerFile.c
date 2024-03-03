  while(1){
            printStruct(getNextToken(NULL)); // not using currently
            // getNextToken(NULL);
            printStruct(getNextToken(NULL)); // not using currently
            // getNextToken(NULL);
            int characters_processed = TwinBuffer->fwd - fwd_curr;
            printf("forward pointer = %d\t", TwinBuffer->fwd);
            printf("back pointer = %d\n", TwinBuffer->back);
            if(characters - characters_processed <=1){
                printf("breaking");
                break;
            }
        }
      