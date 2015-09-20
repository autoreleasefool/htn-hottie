Pebble.addEventListener('ready',
  function(e) {
    console.log('JavaScript app ready and running!');
  }
);

var mostRecentMessageType = 0;
var mostRecentMessageYesNo = 0;
const KEY_POST_YES = 0;
const KEY_POST_NO = 1;

var locationOptions = {
  'timeout': 15000,
  'maximumAge': 60000
};

function ajax(url, method, data, callback) {
  var req = new XMLHttpRequest();
  req.open(method, url, true);
  req.onload = function(e) {
    console.log(req.readyState);
    console.log(req.status);
    if (req.readyState === 4 && req.status === 200) {
      if (req.status === 200) {
        callback(JSON.parse(req.responseText));
      } else {
        console.log("HTTP Error: " + JSON.stringify(req));
      }
    } else {
      console.log("HTTP Error: " + JSON.stringify(req));
    }
  };
  req.send(JSON.stringify(data));
}

function postResult(lat, long, type, yesNo) {
  timeSent = new Date().getTime();
  ajax('https://amber-inferno-1657.firebaseio.com/hotspots.json', 'POST',
  {
    "latitude": lat,
    "longitude": long,
    "ggb": type,
    "yes": yesNo,
    "time": timeSent
  },
  function(data) {
    console.log('The ajax request succeeded: ' + data);
  });
}

function locationSuccess(pos) {
  var coordinates = pos.coords;
  postResult(coordinates.latitude, coordinates.longitude, mostRecentMessageType, mostRecentMessageYesNo);
}

function locationError(err) {
  console.warn('location error (' + err.code + '): ' + err.message);
}

Pebble.addEventListener('appmessage', function (e) {
  mostRecentMessageType = e.payload.KEY_GUY_GIRL_BOTH;
  mostRecentMessageYesNo = e.payload.KEY_POST_ANSWER;
  window.navigator.geolocation.getCurrentPosition(locationSuccess, locationError,
    locationOptions);
  console.log('message!');
});
