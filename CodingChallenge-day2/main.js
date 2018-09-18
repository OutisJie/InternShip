var [n, m, k] = read_line().split(" ").map(Number);

function getLessThan(num) {
    num = Number(num);
    var min = Math.min(n, m);
    var max = Math.max(n, m);
    var result = 0;
    for (var i = 1; i <= min; i++) {
        result += Math.min(Math.floor(num / i), max);
    }
    return result;
}

var start = 1;
var end = n * m;
var currentNum = (start + end) / 2;
while (getLessThan(currentNum) < k || getLessThan(currentNum - 1) >= k) {
    if (getLessThan(currentNum) < k) {
        start = currentNum;
        currentNum = (start + end) / 2;
    } else {
        end = currentNum;
        currentNum = (start + end) / 2;
    }
}
print(Math.floor(currentNum))