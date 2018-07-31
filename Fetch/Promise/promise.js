var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;

const myFirstPromise = new Promise((resolve, reject) => {
    console.log("do some async operation");
    resolve("console right");
  //reject("console error");
});

console.log(myFirstPromise);


function myAsyncFunction(url){
	return new Promise((resolve, reject) => {
    const xhr = new XMLHttpRequest();
    xhr.open("GET", url);
    xhr.onload = ()=> resolve(xhr.responseText);
    xhr.onerror = ()=> reject(xhr.statusTest);
    xhr.send();
  });
}

myAsyncFunction("www.baidu.com").then(function(){
    console.log("yeah");
}).catch((reason) => {
    console.log('fail:' + reason);
});