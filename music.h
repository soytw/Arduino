// TODO: melody and harmony

#include <string.h>
#include <ctype.h>
#include <math.h>
struct Note {
    double freq, dur;
};
double frequency(int pitch, int octave, int sharp=0) {
    /**
    * get frequency (Hz) of a pitch
    * the pitch should be described in scientific pitch notation
    * for example, "D5#" of C tone get be described as (2,5,1)
    * ARGS:
    *   pitch: 1-7 note pitch in numeric notation
    *   octave: 0-10
    *   sharp: sharp if positive, flat if negative
    */
    int mp[] = { 0,60,62,64,65,67,69,71 };
    double p = mp[pitch] + sharp + (octave - 4) * 12;
    return pow(2, (p - 69) / 12) * 440;
}
double duration(int notelen, int bpm) {
    /**
    * get duration (millisecond) of a pitch
    * ARGS:
    *   notelen: how many beats the pitch occupied
    *   bpm: beats per second
    */
    return notelen * 60000.0 / bpm;
}
int fromstr(const char src[], Note res[], int bpm, int sharp=0) {
    /**
     * translate numeric music notation into frequency and duration
     * example: 5-1234 5-1-1- 6-4567 1^-1-1- 4-5432 3-4321 2-3217.1-
     * #: sharp
     * b: flat
     * ^: higher octave
     * .: lower octave
     * -: lengthen
     *
     * ARGS:
     *   src: a string
     *   res: a Note array, which contains freq and dur
     *   bpm: beats per second
     *   sharp: used to change mode
     * RETURN:
     *   length of res array
     */
    int srclen = strlen(src);
    int reslen = 0;
    for (int i = 0; i<srclen; ) {
        int pitch = src[i] - '0';
        int octave = 5;
        int notelen = 1;
        i++;
        while (!isdigit(src[i]) && i<srclen) {
            if (src[i] == '#')
                sharp++;
            else if (src[i] == 'b')
                sharp--;
            else if (src[i] == '^')
                octave++;
            else if (src[i] == '.')
                octave--;
            else if (src[i] == '-')
                notelen++;
            i++;
        }
        res[reslen].freq = frequency(pitch, octave, sharp);
        res[reslen].dur = duration(notelen, bpm);
        reslen++;
    }
    return reslen;
}
