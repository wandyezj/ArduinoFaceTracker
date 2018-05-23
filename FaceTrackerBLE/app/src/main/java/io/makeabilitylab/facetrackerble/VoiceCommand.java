package io.makeabilitylab.facetrackerble;

import android.app.Activity;
import android.content.DialogInterface;
import android.content.Intent;
import android.speech.RecognizerIntent;
import android.util.Log;
import android.widget.ArrayAdapter;

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;

// https://stackoverflow.com/questions/11798337/how-to-voice-commands-into-an-android-application?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa

public class VoiceCommand extends Activity{


    public static final int VOICE_RECOGNITION_REQUEST_CODE = 1234;

    public AtomicBoolean m_is_listening = new AtomicBoolean(false);

    public void startVoiceRecognitionActivity() {

        if (m_is_listening.getAndSet(true)) {
            return;
        }

        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT,
                "Speech recognition demo");
        startActivityForResult(intent, VOICE_RECOGNITION_REQUEST_CODE);
    }

    private ArrayList<String> m_matches = new ArrayList<String>();

    public boolean Contains(String word) {
        return m_matches.contains(word);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == VOICE_RECOGNITION_REQUEST_CODE && resultCode == RESULT_OK) {
            // Fill the list view with the strings the recognizer thought it
            // could have heard
            m_matches = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);

            for (String match : m_matches) {
                Log.i("Voice", match);
            }


            // mList.setAdapter(new ArrayAdapter(this, android.R.layout.simple_list_item_1, matches));
            // matches is the result of voice input. It is a list of what the
            // user possibly said.
            // Using an if statement for the keyword you want to use allows the
            // use of any activity if keywords match
            // it is possible to set up multiple keywords to use the same
            // activity so more than one word will allow the user
            // to use the activity (makes it so the user doesn't have to
            // memorize words from a list)
            // to use an activity from the voice input information simply use
            // the following format;
            // if (matches.contains("keyword here") { startActivity(new
            // Intent("name.of.manifest.ACTIVITY")

            /*
            if (matches.contains("information")) {
                informationMenu();
            }
            */
        }

        m_is_listening.set(false);
    }
}
