package com.example.connectfour;

import android.content.Intent;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private final String TAG = "Lifecycle";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d(TAG, "onCreate");
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.d(TAG, "onStart");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d(TAG, "onStop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "onDestroy");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d(TAG, "onPause");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "onResume");
    }


    /** @noinspection deprecation*/
    public void onChangeDifficultyClick(View view) {
        Intent intent = new Intent(MainActivity.this, GameOptions.class);
        startActivityForResult(intent, 1);
    }

    public void onStartGameClick(View view) {
        Intent intent = new Intent(MainActivity.this, Board.class);
        startActivity(intent);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == 1 && resultCode == RESULT_OK) {  // Check if it's the result from GameOptions
            if (data != null) {
                String selectedDifficulty = data.getStringExtra("selectedDifficulty");
                Log.d(TAG, "Selected Difficulty: " + selectedDifficulty);
                TextView difficultyDisplayTextView = findViewById(R.id.difficultyMainMenuDisplay);
                difficultyDisplayTextView.setVisibility(View.VISIBLE);
                difficultyDisplayTextView.setText(selectedDifficulty);
            }
        }
    }


}