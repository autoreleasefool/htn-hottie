$(document).ready(function() {
	$('a[href^="#"]').on('click', function(event) {
	    var target = $( $(this).attr('href') );
	    if( target.length ) {
	        event.preventDefault();
	        $('html, body').animate({
	            scrollTop: target.offset().top
	        }, 1000);
	    }
	});
});

var guys = [];
var girls = [];
var map;

var girlHotspots = {
	timmys: {
		center: {lat: 43.475105, lng: -80.530479 },
		radius: 250
	},
	laurier: {
		center: {lat: 43.462099, lng: -80.518395},
		radius: 300
	},
	lake: {
		center: {lat: 43.460969, lng: -80.552698},
		radius: 400
	},
	research: {
		center: {lat: 43.469443, lng: -80.547410},
		radius: 200
	},
	other: {
		center: {lat: 43.485965, lng: -80.560706},
		radius: 400
	}
};

var girlColdspots = {
	timmys: {
		center: {lat: 43.484561, lng: -80.537252},
		radius: 400
	},
	laurier: {
		center: {lat: 43.463418, lng: -80.559012},
		radius: 200
	},
	lake: {
		center: {lat: 43.465030, lng: -80.536515},
		radius: 200
	}
};

var guyHotspots = {
	timmys: {
		center: {lat: 43.474783, lng: -80.550242},
		radius: 300
	},
	laurier: {
		center: {lat: 43.478859, lng: -80.538613},
		radius: 250
	}
};

var guyColdspots = {
	timmys: {
		center: {lat: 43.488704, lng: -80.550023},
		radius: 400
	},
	laurier: {
		center: {lat: 43.469101, lng: -80.565879},
		radius: 200
	},
	lake: {
		center: {lat: 43.470499, lng: -80.531826},
		radius: 200
	},
	research: {
		center: {lat: 43.483558, lng: -80.563912},
		radius: 300
	}
};

function showGuys(hide) {
 if (hide) {
	 for (var spot in girls) {
		 girls[spot].setMap(null);
	 }
	 girls = [];
 }

 if (guys[0] == null) {
	 guys = [];
	 for (var spot in guyColdspots) {
		 var spotCircle = new google.maps.Circle({
			 strokeColor: '#0000FF',
			 strokeOpacity: 0.8,
			 strokeWeight: 2,
			 fillColor: '#0000FF',
			 fillOpacity: 0.35,
			 map: map,
			 radius: guyColdspots[spot].radius,
			 center: guyColdspots[spot].center,
		 });
		 guys.push(spotCircle);
	 }
	 for (var spot in guyHotspots) {
		 var spotCircle = new google.maps.Circle({
			 strokeColor: '#FF0000',
			 strokeOpacity: 0.8,
			 strokeWeight: 2,
			 fillColor: '#FF0000',
			 fillOpacity: 0.35,
			 map: map,
			 radius: guyHotspots[spot].radius,
			 center: guyHotspots[spot].center,
		 });
		 guys.push(spotCircle);
	 }
 }
}

function showGirls(hide) {
	if (hide) {
		for (var spot in guys) {
			guys[spot].setMap(null);
		}
		guys = [];
	}

  if (girls[0] == null) {
		girls = [];
		for (var spot in girlHotspots) {
	 	 var spotCircle = new google.maps.Circle({
	 		 strokeColor: '#FF0000',
	 		 strokeOpacity: 0.8,
	 		 strokeWeight: 2,
	 		 fillColor: '#FF0000',
	 		 fillOpacity: 0.35,
	 		 map: map,
	 		 radius: girlHotspots[spot].radius,
	 		 center: girlHotspots[spot].center,
	 	 });
		 girls.push(spotCircle);
	  }
		for (var spot in girlColdspots) {
	 	 var spotCircle = new google.maps.Circle({
	 		 strokeColor: '#0000FF',
	 		 strokeOpacity: 0.8,
	 		 strokeWeight: 2,
	 		 fillColor: '#0000FF',
	 		 fillOpacity: 0.35,
	 		 map: map,
	 		 radius: girlColdspots[spot].radius,
	 		 center: girlColdspots[spot].center,
	 	 });
		 girls.push(spotCircle);
	  }
	}
}

function showBoth() {
	for (var spot in guys) {
		guys[spot].setMap(null);
	}
	for (var spot in girls) {
		girls[spot].setMap(null);
	}
	girls = [];
	guys = [];
	showGuys(false);
	showGirls(false);
}

function GuyControl(controlDiv, map) {

  // Set CSS for the control border.
  var controlUI = document.createElement('div');
  controlUI.style.backgroundColor = '#fff';
  controlUI.style.border = '2px solid #fff';
  controlUI.style.borderRadius = '3px';
  controlUI.style.boxShadow = '0 2px 6px rgba(0,0,0,.3)';
  controlUI.style.cursor = 'pointer';
  controlUI.style.marginBottom = '22px';
	controlUI.style.marginLeft = '8px';
	controlUI.style.marginTop = '8px';
	controlUI.style.marginRight = '8px';
  controlUI.style.textAlign = 'center';
  controlUI.title = 'Click to show hot guy hotspots';
  controlDiv.appendChild(controlUI);

  // Set CSS for the control interior.
  var controlText = document.createElement('div');
  controlText.style.color = 'rgb(25,25,25)';
  controlText.style.fontFamily = 'Roboto,Arial,sans-serif';
  controlText.style.fontSize = '16px';
  controlText.style.lineHeight = '38px';
  controlText.style.paddingLeft = '5px';
  controlText.style.paddingRight = '5px';
  controlText.innerHTML = 'Guys';
  controlUI.appendChild(controlText);

  // Setup the click event listeners: simply set the map to Chicago.
  controlUI.addEventListener('click', function() {
    showGuys(true);
  });
}

function GirlControl(controlDiv, map) {

  // Set CSS for the control border.
  var controlUI = document.createElement('div');
  controlUI.style.backgroundColor = '#fff';
  controlUI.style.border = '2px solid #fff';
  controlUI.style.borderRadius = '3px';
  controlUI.style.boxShadow = '0 2px 6px rgba(0,0,0,.3)';
  controlUI.style.cursor = 'pointer';
  controlUI.style.marginBottom = '22px';
	controlUI.style.marginLeft = '8px';
	controlUI.style.marginTop = '8px';
	controlUI.style.marginRight = '8px';
  controlUI.style.textAlign = 'center';
  controlUI.title = 'Click to show hot girl hotspots';
  controlDiv.appendChild(controlUI);

  // Set CSS for the control interior.
  var controlText = document.createElement('div');
  controlText.style.color = 'rgb(25,25,25)';
  controlText.style.fontFamily = 'Roboto,Arial,sans-serif';
  controlText.style.fontSize = '16px';
  controlText.style.lineHeight = '38px';
  controlText.style.paddingLeft = '5px';
  controlText.style.paddingRight = '5px';
  controlText.innerHTML = 'Girls';
  controlUI.appendChild(controlText);

  // Setup the click event listeners: simply set the map to Chicago.
  controlUI.addEventListener('click', function() {
    showGirls(true);
  });
}

function BothControl(controlDiv, map) {

  // Set CSS for the control border.
  var controlUI = document.createElement('div');
  controlUI.style.backgroundColor = '#fff';
  controlUI.style.border = '2px solid #fff';
  controlUI.style.borderRadius = '3px';
  controlUI.style.boxShadow = '0 2px 6px rgba(0,0,0,.3)';
  controlUI.style.cursor = 'pointer';
  controlUI.style.marginBottom = '22px';
	controlUI.style.marginLeft = '8px';
	controlUI.style.marginTop = '8px';
	controlUI.style.marginRight = '8px';
  controlUI.style.textAlign = 'center';
  controlUI.title = 'Click to show hot guys and girls';
  controlDiv.appendChild(controlUI);

  // Set CSS for the control interior.
  var controlText = document.createElement('div');
  controlText.style.color = 'rgb(25,25,25)';
  controlText.style.fontFamily = 'Roboto,Arial,sans-serif';
  controlText.style.fontSize = '16px';
  controlText.style.lineHeight = '38px';
  controlText.style.paddingLeft = '5px';
  controlText.style.paddingRight = '5px';
  controlText.innerHTML = 'Both';
  controlUI.appendChild(controlText);

  // Setup the click event listeners: simply set the map to Chicago.
  controlUI.addEventListener('click', function() {
    showBoth();
  });
}

function initialize() {
	var waterloo = new google.maps.LatLng(43.472622, -80.539538);
	var myOptions = {
		zoom: 14,
		center: waterloo,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	};

	map = new google.maps.Map(
			document.getElementById("map_canvas"),
			myOptions);

	// Create the DIV to hold the control and call the CenterControl() constructor
  // passing in this DIV.
  var centerControlDiv = document.createElement('div');
  var centerControl = new GuyControl(centerControlDiv, map);
  centerControlDiv.index = 1;
  map.controls[google.maps.ControlPosition.TOP_CENTER].push(centerControlDiv);

	var centerControlDiv = document.createElement('div');
  var centerControl = new GirlControl(centerControlDiv, map);
  centerControlDiv.index = 1;
  map.controls[google.maps.ControlPosition.TOP_CENTER].push(centerControlDiv);

	var centerControlDiv = document.createElement('div');
  var centerControl = new BothControl(centerControlDiv, map);
  centerControlDiv.index = 1;
  map.controls[google.maps.ControlPosition.TOP_CENTER].push(centerControlDiv);
}
