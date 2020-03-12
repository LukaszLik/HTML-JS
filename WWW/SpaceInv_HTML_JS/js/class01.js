class Alien {
	constructor(x, y) {
	this.x = x;
	this.y = y;
	this.alive = true;
	}

	test() {
	alert("czesc");
	}

	kill() {
	this.alive = false;
	}
}

class Bullet {
	constructor(x, y) {
	this.x = x;
	this.y = y;
	this.visible = false;
	this.active = false;
	}

	mouveUp() {
	this.y = this.y - 12;
	this.visible = true;
	if (this.y <= 0) {
	this.kill();
	}
	}

	start(x, y) {
	this.visible = true;
	this.active = true;
	this.x = x;
	this.y = y;
	}

	kill() {
	this.visible = false;
	this.active = false;
	}
}

function clear()
{
	var context = canvas.getContext('2d');
	context.clearRect(0, 0, canvas.width, canvas.height);
}

function spawnAlien(posX, posY)
{


	alien = new Alien(posX, posY);
	if (canvas.getContext)
	{
		var c = canvas.getContext('2d');
		//c.clearRect(posX-1,50,52,52)
		var img = new Image()
		img.src = "/js/alien2.png"

		img.onload = function()
		{
			console.log("alien")
			c.drawImage(img, alien.x , alien.y, 35,35)
		}
	}

	return alien;
}

function moveShip(posX = 50)
{

	if (canvas.getContext)
	{
		var c = canvas.getContext('2d')
		var img2 = new Image()
		img2.src = "/js/ship.png"
		img2.onload = function()
		{
			c.clearRect(posX-1,750,52,52)
			c.drawImage(img2, posX,750,50,50)
		}
	}
}

function moveShipLeft()
{
	if (posX > 25)
	{	posX--;
		moveShip(posX);
	}
}

function moveShipRight()
{
	if ( posX < 750)
	{	posX++;
		moveShip(posX);
	}
}

function moveAlien(alien)
{
		alien.y += 1;

		if (canvas.getContext && alien.alive)
		{
			var c = canvas.getContext('2d');
			var img = new Image()
			img.src = "/js/alien2.png"
			img.onload = function()
			{
				c.clearRect(alien.x ,alien.y -16 , 35, 35)
				c.drawImage(img, alien.x ,alien.y , 35, 35)
			}
		}

		else
		{
			var c = canvas.getContext('2d');
			c.clearRect(alien.x ,alien.y -1, 51, 51)
		}
}

function isLost(alien)
{
		if (alien.y >= 750 && canvas.getContext && alien.alive)
		{
			var c = canvas.getContext('2d')
			c.clearRect(0,50, canvas.width, canvas.height)

			c.font = "italic bold 100px Arial ";
			c.fillStyle = 'red';
			c.fillText('GAME OVER', 110, 250);

			//alien.alive = false;
			var form = document.getElementById("inputDiv");
			form.style.visibility = 'initial';
		 	highscoreBtn.style.visibility = 'initial';
			startBtn.style.display = 'initial';
			startBtn.textContent = "Replay!";
			startBtn.setAttribute('clicked', '0');

			lostFlag = 1;
			//clearInterval(intervalLost);
		}
}

function isWon(alien)
{
	var deadAlienNumber = 0;
	var i;
	for ( i =0 ; i <alienNbr; i++)
		if(!alien[i].alive)
			deadAlienNumber++;

		if (deadAlienNumber == alienNbr)
		{
			var c = canvas.getContext('2d')
			c.clearRect(0,0, canvas.width, canvas.height)

			c.font = "italic bold 100px Arial ";
			c.fillStyle = 'green';
			c.fillText('You won', 150, 250);

			startBtn.textContent = "Next Wave!";
			startBtn.style.display = 'initial';
			startBtn.setAttribute('clicked', '0');

			clearInterval(intervalWon);
			alienNbr++;
		}
}

function shoot(posX,posY)
{
	bullet = new Bullet(posX + 22, posY -25);
	bullet.active = true;

	if (canvas.getContext)
	{
		var c = canvas.getContext('2d');
		var img = new Image();
		img.src = "/js/bullet.png";
		img.onload = function()
		{
			c.drawImage(img, bullet.x, bullet.y, 5, 25);
		}
	}

	return bullet;
}

function moveBullet(bullet, alienArray)
{
	bullet.y -= 2;

	if (bullet.y < 10 && bullet.active)
	{
		var c = canvas.getContext('2d');
		c.clearRect(bullet.x-5 ,bullet.y -5, 15, 35)

		alreadyShot = false;
		clearInterval(activeBullet);
	}


	else if (canvas.getContext && bullet.active)
	{
		var c = canvas.getContext('2d');
		var img = new Image();
		img.src = "/js/bullet.png";
		img.onload = function()
		{
			c.clearRect(bullet.x -1 ,bullet.y +1, 7, 27)
			c.drawImage(img, bullet.x, bullet.y, 5, 25);
		}
	}

	//detecting collison with an alien
	var i;
	for (i = 0; i< alienNbr; i++)
		if (bullet.x < (alienArray[i].x + 35) && bullet.x >= (alienArray[i].x) && alienArray[i].alive)
		{
			if(bullet.y < alienArray[i].y +25)
			{
				++score;
				var c = canvas.getContext('2d');
				c.clearRect(bullet.x ,bullet.y, 100, 100)

				alienArray[i].alive = false;
				bullet.active = false;

				alreadyShot = false;
				clearInterval(activeBullet);
			}
		}
}

function trackScore()
{
	//console.log("SCORE " + score);
	var c = canvas.getContext('2d')
	c.clearRect(0,0, 150, 25)

	var scoreText = "Score: " + score;
	c.font = "italic bold 20px Arial ";
	c.fillStyle = 'black';
	c.fillText(scoreText, 10, 15);
}

function sendScore()
{
	var name = document.getElementById("name").value;
	if (name.length == 0)
		name = "Bezimienny";

	console.log("Nazwa = " + name);
	var xmlr = new XMLHttpRequest();

	xmlr.open("POST", "/highscores", true);
	xmlr.setRequestHeader("Content-type", "application/json");

	var data = JSON.stringify({"name":name, "score":score});
	console.log(data);
	xmlr.send(data);
}

function showHighscores()
{
	var dataJSON;
	console.log("Highscores = ");

	var xmlr = new XMLHttpRequest();
	xmlr.open("GET", '/getHighscores', true);
	xmlr.setRequestHeader("Content-Type", "application/json");

	xmlr.onreadystatechange = function (aEvt) {
	  if (xmlr.readyState == 4) {
	     if(xmlr.status == 200)
			 	{
					dataJSON = JSON.parse(xmlr.responseText);
					console.log(dataJSON +"\n" + typeof(dataJSON));

					highscoreDiv.style.visibility = 'initial';
					var table = document.getElementById("highscoreTable");
					table.innerHTML = "";

					var row = table.insertRow(0);

					var cell1 = row.insertCell(0);
					var cell2 = row.insertCell(1);

					cell1.innerHTML = "<b>Nick</b>";
					cell2.innerHTML = "<b>Score</b>";

					for (var i =0; i < dataJSON.Highscores.length; i++)
					{
						row = table.insertRow(i+1);

						cell1 = row.insertCell(0);
						cell2 = row.insertCell(1);

						cell1.innerHTML = dataJSON.Highscores[i].name;
						cell2.innerHTML = dataJSON.Highscores[i].score;
					}
				}

	     else
	      console.log("Błąd podczas ładowania strony\n");
	  }
	};
	xmlr.send(null);
}
