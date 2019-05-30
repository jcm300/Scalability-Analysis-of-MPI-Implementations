BEGIN                           {IGNORECASE=1;BLOCKSIZE=15;curL=0;block=-1;}
                                {
                                    if(!(curL % BLOCKSIZE)){
                                        curL=0;
                                        block ++;
                                    }
                                    time[block][curL] = $1 + 0.0;
                                    curL ++;
                                }
END                             {
                                    for(block in time){
                                        asort(time[block], time[block]);
                                        if(!(BLOCKSIZE % 2))
                                            print time[block][(BLOCKSIZE-1)/2]
                                        else
                                            print (time[block][(BLOCKSIZE-1)/2] + time[block][(BLOCKSIZE+1)/2])/2
                                        print ""
                                    }
                                }
