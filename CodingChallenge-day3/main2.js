let [n, s, l] = readline().split(' ').map(Number);

let num = Math.floor(l/(s+1));
if(num == 0 && s == l){
    print(n);
}else if(num!==13){
    if((n - Math.floor(n/num))%13 == 0){
       print(Math.ceil(n/num) + 1);
    }else{
         print(Math.ceil(n/num));
    }
}else {
    print(Math.ceil(n/(num-1)));
}