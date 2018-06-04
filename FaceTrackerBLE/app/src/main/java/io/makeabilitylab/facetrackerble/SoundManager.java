package io.makeabilitylab.facetrackerble;

import android.content.Context;
import android.media.MediaPlayer;

public class SoundManager {

    private MediaPlayer m_play_smile;
    private MediaPlayer m_play_frown;

    public  SoundManager(Context context) {

        m_play_frown = MediaPlayer.create(context, R.raw.frown);
        m_play_smile = MediaPlayer.create(context, R.raw.smile);
    }

    public boolean isPlaying(){
        return m_play_smile.isPlaying() || m_play_frown.isPlaying();
    }

    public void PlaySmile() {
        if (!isPlaying()) {
            m_play_smile.seekTo(0);
            m_play_smile.start();
        }
    }

    public void PlayFrown() {
        if (!isPlaying()) {
            m_play_frown.seekTo(0);
            m_play_frown.start();
        }
    }




}
