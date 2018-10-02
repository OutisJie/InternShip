
let n = 4;
let arr = ["bytedance",
    "toutiaohao",
    "toutiaoapp",
    "iesa"];
let arr1 = ["bytedance",
"toutiaohao",
"toutiaoapp",
"iesa"];

JSON.stringify
let arrSort = arr1.sort();
for (let i = 0; i < n; i++) {
    let str = arr[i];
    // console.log(i, str);
    if (str.length === 1) {
        console.log(str);
    } else {
        let temp = "";
        for (let j = 0; j < str.length; j++) {
            temp += str[j];
            if (single(temp, arrSort)) {
                console.log(temp);
                break;
            }
        }
    }
}

function single(str, arr) {
    let num = 0;
    for (let i = 0; i < arr.length; i++) {
        
        if (arr[i].includes(str, 0)) {
            num += 1;
            if (num > 1) {
                console.log("test", str, arr[i])
                return false;
            }
           
        }
    }
    return true;
}