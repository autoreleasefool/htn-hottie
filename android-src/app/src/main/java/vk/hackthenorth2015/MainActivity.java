package vk.hackthenorth2015;

import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.support.v4.app.NotificationCompat;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


public class MainActivity extends ActionBarActivity implements LocationListener {

    private EditText mText;
    private TextView textView;
    private boolean male, female;
    public static final int nID = 1342;
    NotificationCompat.Builder notif;
    private Button button2, yesButton, noButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = (TextView) findViewById(R.id.textView2);
        //mText = (EditText) findViewById(R.id.editText1);
        notif = new NotificationCompat.Builder(this);
        button2 = (Button) findViewById(R.id.button2);
        yesButton = (Button)findViewById(R.id.yesButton);
        noButton = (Button)findViewById(R.id.noButton);

        //gets info from startscreen
        Bundle bundle = getIntent().getExtras();
        int pref = bundle.getInt("pref");

        if (pref == 0) {
            male = true;
            female = false;
            Male();
        }

        if (pref == 1) {
            female = true;
            male = false;
            Female();
        }

        if (pref == 2) {
            male = true;
            female = true;
            Both();
        }

    }


    void Male() {

        textView.setText("You are interested in males.");


        //long futureInMillis = SystemClock.elapsedRealtime() + delay;
        //AlarmManager alarmManager = (AlarmManager)getSystemService(Context.ALARM_SERVICE);
        //alarmManager.set(AlarmManager.ELAPSED_REALTIME_WAKEUP, futureInMillis, pendingIntent);


    }

    public void bam(View view) {

        Intent intent1 = new Intent(this,StartScreen.class);
        intent1.setAction("yes");
        Intent intent2 = new Intent(this,StartScreen.class);
        intent2.setAction("no");
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent1, PendingIntent.FLAG_UPDATE_CURRENT);
        PendingIntent pendingIntent2 = PendingIntent.getActivity(this, 0, intent2, PendingIntent.FLAG_UPDATE_CURRENT);


        Notification notif = new Notification.Builder(this)
                .setSmallIcon(R.mipmap.ic_launcher)
                .setContentIntent(pendingIntent)
                .setTicker("HOTTY ALERT!")
                .setWhen(System.currentTimeMillis())
                .setContentTitle("Spot the Hottie")
                .setContentText("Are there any attractive people around?")
                .setPriority(Notification.PRIORITY_DEFAULT)
                .setAutoCancel(true)
                .addAction(R.drawable.tup, "Yes", pendingIntent)
                .addAction(R.drawable.tdown, "No", pendingIntent2)
                .build();

        NotificationManager notificationManager = (NotificationManager)
                getSystemService(NOTIFICATION_SERVICE);

        notificationManager.notify(0, notif);

        AlarmManager alarmManager = (AlarmManager)getSystemService(Context.ALARM_SERVICE);
        alarmManager.set(AlarmManager.ELAPSED_REALTIME_WAKEUP, 15000, pendingIntent);

    }




    void Female() {

        textView.setText("You are interested in females.");

    }

    void Both() {

        textView.setText("You are interested in both genders.");

    }


    public void yes(View view){

    }

    public void no(View view){

    }


    @Override
    public void onLocationChanged(Location loc) {

        LocationListener locationListener = new LocationListener();
        LocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 5000, 10, locationListener);

        Toast.makeText(
                getBaseContext(),
                "Location changed: Lat: " + loc.getLatitude() + " Lng: "
                        + loc.getLongitude(), Toast.LENGTH_SHORT).show();
        String longitude = "Longitude: " + loc.getLongitude();
        String latitude = "Latitude: " + loc.getLatitude();
    }



    @Override
    public void onStatusChanged(String provider, int status, Bundle extras) {

    }

    @Override
    public void onProviderEnabled(String provider) {

    }

    @Override
    public void onProviderDisabled(String provider) {

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
