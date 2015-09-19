package vk.hackthenorth2015;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.TextView;


public class MainActivity extends ActionBarActivity {

    private EditText mText;
    private TextView textView;
    private boolean male, female;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = (TextView)findViewById(R.id.textView2);
        mText = (EditText)findViewById(R.id.editText1);

        //gets info from startscreen
        Bundle bundle = getIntent().getExtras();
        int pref = bundle.getInt("pref");

        if(pref == 0){
            male = true;
            female = false;
            Male();
        }

        if(pref == 1){
            female = true;
            male = false;
            Female();
        }

        if(pref == 2){
            male = true;
            female = true;
            Both();
        }

    }


    void Male(){

        textView.setText("You are interested in males.");


    }



    void Female(){

        textView.setText("You are interested in females.");

    }

    void Both(){

        textView.setText("You are interested in both genders.");

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
