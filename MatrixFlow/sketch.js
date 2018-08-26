
const fadeInterVal = 1.6; 
const symbolSize = 14;

let streams = [];
function setup() {
	createCanvas(windowWidth, windowHeight);
	background(0);

	let x = 0;
	for(let i = 0 ;i <= width/symbolSize; i++){
		let stream = new Stream();
		stream.generateStream(x, random(-1000, 0));
		streams.push(stream);
		x += symbolSize;
	}

	textFont('Consolas');
	textSize(symbolSize);
}

function draw() {
	background(0, 150);
	streams.forEach(element => {
		element.render();
	})
}

function Symbol(x, y, speed, first, opacity) {
	this.x = x;
	this.y = y;
	this.value = String.fromCharCode(0x03A0 + round(random(0,96)));//initial the text code

	this.switchInterVal = round(random(2, 25));
	this.speed = speed;
	this.first = first;
	this.opacity = opacity;

	this.setSymbolText = function(){

		let charType = round(random(0, 5));
		if(frameCount % this.switchInterVal === 0){
			if(charType > 1){
				//set text to katakana
				this.value = String.fromCharCode(0x30A0 + round(random(0, 96)));
			}else{
				//set it to numeric
				this.value = round(random(0, 9));
			}
		}
	}

	this.render = function(){

		this.setSymbolText();
		text(this.value, this.x, this.y);
		if(this.first){
			fill(140, 255, 170, this.opacity)
		}else{
			fill(0, 255, 50, this.opacity);
		}
		this.y  = this.y >= height ? 0 : this.y+=this.speed;
	}

}

function Stream(){
	this.symbols = [];
	this.streamLength = round(random(5, 30));
	this.speed = random(0, 10);

	this.generateStream = function(x, y){
		let opacity = 255;
		let first = round(random(0, 4)) === 1//每5个字符串的流中只有一个的首字符需要高亮

		for(let i = 0; i <= this.streamLength; i++){
			let symbol = new Symbol(x, y, this.speed, first, opacity);
			symbol.setSymbolText();
			this.symbols.push(symbol);

			opacity -= (255/this.streamLength)/fadeInterVal;
			y -= symbolSize;
			first = false;
		}
	}

	this.render = function(){
		this.symbols.forEach(element => {
			element.render();
		});
	}

}