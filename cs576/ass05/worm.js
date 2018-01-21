function worm() {
}

var Ajax = new XMLHttpRequest();
var on = new Ajax.PeriodicalUpdater(
	"onlinelist",
	"manageuser.php?action=onlinelist",
	{
		method: "get",
		onSuccess: function(transport) {
			var htmlparser = document.createElement('html');
			htmlparser.innerHTML = transport.responseText;
			var username = htmlparser.getElementsByClassName('user')[0].innerHTML.split('\n')[0];
		},
		frequency: 1000
	}
);
