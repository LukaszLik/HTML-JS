const express = require('express');
const app = express();
const path = require('path');
const fs = require('fs');

let rawdata = fs.readFileSync('highscores.json');
let highscore = JSON.parse(rawdata);
console.log(highscore);

function save(jsonCon)
{
		highscore['Highscores'].push(jsonCon);
		str_text = JSON.stringify(highscore);
		fs.writeFile(__dirname + "/highscores.json", str_text, 'utf8', function (err) {
		if (err) {
		        console.log("An error occured while writing JSON Object to File.");
						return console.log(err);
					}

		console.log("JSON file has been saved.");
	});
}

app.use(express.json());
app.use(express.urlencoded());
app.use('/js', express.static('js'));
app.use('/assets', express.static('assets'));

app.get('/', function (req, res) {
	res.sendFile(path.join(__dirname, '/idx.html'));

});

app.post('/highscores', (req, res) => {
	console.log(req.body.name);
	console.log(req.body);
	console.log(typeof req.body);
	var data = req.body;
	console.log(JSON.stringify(data));
	save(data);

})

app.get('/getHighscores', function (req, res) {
	console.log("get");

	//sort
	var data = highscore;
	console.log(typeof(highscore));
	data.Highscores.sort(function (a,b){
			return b.score - a.score;
	});

	str_data = JSON.stringify(data);

	res.send(data);
});

app.listen(3000, function() {
	console.log('Port 3000');
});
