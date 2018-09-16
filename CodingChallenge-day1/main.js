const readline = require("readline");
const r1 = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
r1.setPrompt('Test> ');
r1.prompt();
let arr = [];
r1.on('line', function (line) {
    switch (line.trim()) {
        case 'hello':
            r1.write("Hello ");
            console.log('world!');
            break;
        case 'close':
            r1.close();
            break;
        default:
            arr.push(line.trim());
            console.log("data:", arr);
            break;
    }
    r1.prompt();
});

r1.on('close', function () {
    let res = 0;
    arr.forEach(e => res+=parseInt(e));
    console.log('result:', res);
    process.exit(0);
})