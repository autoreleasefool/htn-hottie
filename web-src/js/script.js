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

var hotspots = {
	timmys: {
		center: {lat: 43.476766, lng: -80.539120},
		radius: 400
	},
	laurier: {
		center: {lat: 43.475390, lng: -80.528445},
		radius: 200
	},
	lake: {
		center: {lat: 43.473462, lng: -80.559324},
		radius: 200
	},
	research: {
		center: {lat: 43.480493, lng: -80.551143},
		radius: 300
	}
};

var coldspots = {
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

function initialize() {
	var waterloo = new google.maps.LatLng(43.472622, -80.539538);
	var myOptions = {
		zoom: 14,
		center: waterloo,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	};

	var map = new google.maps.Map(
			document.getElementById("map_canvas"),
			myOptions);

  for (var spot in hotspots) {
		var marker = new google.maps.Marker({
		  map: map,
		  position: hotspots[spot].center,
		  title: 'Hot spot!'
		});
    var spotCircle = new google.maps.Circle({
      strokeColor: '#FF0000',
      strokeOpacity: 0.8,
      strokeWeight: 2,
      fillColor: '#FF0000',
      fillOpacity: 0.35,
      map: map,
      radius: hotspots[spot].radius
    });
		spotCircle.bindTo('center', marker, 'position');
  }

	for (var spot in coldspots) {
		var marker = new google.maps.Marker({
		  map: map,
		  position: coldspots[spot].center,
		  title: 'NOT spot!'
		});
    var spotCircle = new google.maps.Circle({
      strokeColor: '#0000FF',
      strokeOpacity: 0.8,
      strokeWeight: 2,
      fillColor: '#0000FF',
      fillOpacity: 0.35,
      map: map,
      radius: coldspots[spot].radius
    });
		spotCircle.bindTo('center', marker, 'position');
  }
}
