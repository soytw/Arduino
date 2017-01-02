// TODO: melody and harmony

#include <string.h>
#include <ctype.h>
#include <math.h>

namespace Music {
    struct Note {
        int8_t pitch, octave, sharp;
        int freq;
        long dur;
    };
    double frequency(int pitch, int octave, int sharp=0) {
        /**
         * get frequency (Hz) of a pitch
         * the pitch should be described in scientific pitch notation
         * for example, "D5#" of C tone get be described as (2,5,1)
         * @param pitch 1-7 note pitch in numeric notation
         *              or 0 if it is a rest
         * @param octave 0-10
         * @param sharp sharp if positive, flat if negative
         * @return the frequency the pitch represent, in Hertz
         *         0 when rest
         */
        if (pitch == 0) return 0;
        // MIDI's standard
        int mp[] = {0,60,62,64,65,67,69,71};
        int p = mp[pitch] + sharp + (octave-4)*12;
        return pow(2, (p-69)/12.0) * 440;
    }
    double duration(int notelen, int bpm) {
        /**
         * get duration of a pitch, in milliseconds
         * @param notelen how many beats the pitch occupied
         * @param bpm beats per second
         * @return duration in milliseconds
         */
        return notelen * 60000.0 / bpm;
    }
    size_t fromstr(const char src[], Note res[], int bpm, int sharp=0) {
        /**
         * translate numeric music notation into frequency and duration
         * example: 5-1234 5-1-1- 6-4567 1^-1-1- 4-5432 3-4321 2-3217.1-
         * #: sharp
         * b: flat
         * ^: higher octave
         * .: lower octave
         * -: lengthen
         * @param src a string describing the music in numeric notation
         * @param res a Note array, which contains freq and dur
         * @param bpm beats per second
         * @param sharp used to change mode
         * @return length of res array
         */
        size_t srclen = strlen(src);
        size_t reslen = 0;
        for (size_t i=0; i<srclen; ) {
            int pitch = src[i] - '0';
            if (pitch<1 || pitch>7) pitch = 0;
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
            res[reslen].pitch = pitch;
            res[reslen].octave = octave;
            res[reslen].sharp = sharp;
            res[reslen].freq = frequency(pitch, octave, sharp);
            res[reslen].dur = duration(notelen, bpm);
            reslen++;
        }
        return reslen;
    }
}
