package com.example.connectfour;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class GameOptions extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game_options);
    }

    public void onDifficultySelected(View view) {
        int difficultyId = R.id.easyDifficultyOption;
        String difficultyString = "Easy";

        if (view.getId() == R.id.mediumDifficultyOption) {
            difficultyString = "Medium";
        } else if (view.getId() == R.id.hardDifficultyOption) {
            difficultyString = "Hard";
        }

        Intent intent = new Intent();
        intent.putExtra("selectedDifficulty", difficultyString);
        setResult(RESULT_OK, intent);
        finish();
    }
}