package vk.hackthenorth2015;

import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;


public class StartScreen extends ActionBarActivity {

    private Spinner mSpinner;
    private Button mButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_start_screen);


        final SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(this);

        if (!settings.getBoolean("my_first_time", true)) {

            int preference = settings.getInt("pref", 0);

            Intent intent = new Intent(StartScreen.this, MainActivity.class);

            Bundle bundle = new Bundle();
            bundle.putInt("pref", preference);
            intent.putExtras(bundle);
            startActivity(intent);
            finish();
        }


        mSpinner = (Spinner)findViewById(R.id.spinner);
        mButton = (Button)findViewById(R.id.button);

        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.sex_preferences, android.R.layout.simple_spinner_dropdown_item);
        mSpinner.setAdapter(adapter);

        //Button retrieves preference choice and passes it to the main activity
        mButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int preference = mSpinner.getSelectedItemPosition();
                settings.edit()
                        .putBoolean("my_first_time", false)
                        .putInt("pref", preference)
                        .apply();

                Intent intent = new Intent(StartScreen.this, MainActivity.class);

                Bundle bundle = new Bundle();
                bundle.putInt("pref", preference);
                intent.putExtras(bundle);
                startActivity(intent);
            }
        });

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_start_screen, menu);
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

    @Override
    protected void onResume() {
        super.onResume();

    }
}
