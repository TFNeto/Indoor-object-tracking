#ifndef MARKER_H
#define MARKER_H

class marker {
    public:
        marker();
        int get_xPOS();
        int get_yPOS();
        void set_xPOS(int x);
        void set_yPOS(int y);

    private:
        int xPOS, yPOS;
};

#endif // MARKER_H
