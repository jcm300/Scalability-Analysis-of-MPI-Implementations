awk 'function case_fold_compare(i1, v1, i2, v2, l, r){
        l = v1
        r = v2

        if (l < r)
            return -1
        else if (l == r)
            return 0
        else
            return 1
    }

     BEGIN {c = 0}
     {
      a[c] = $0; 
      c++;
      if(c==15){
          asort(a,b,"case_fold_compare");
          if((c % 2) == 1){
              median = b[int(c/2) + 1];
          }else{
              median = ( b[c/2] + b[c/2-1] ) / 2;
          }
          print median
          c=0
      }
     }' $1
