#ifndef COORDS_H
#define COORDS_H
class coords {
    private:
        int x;
        int y;
    public:
        coords();
        coords(int, int);
        coords operator = (coords const& c) {
            coords temp;
            temp.x = c.x;
            temp.y = c.y;
            return temp;
        }
        int getX();
        int getY();
        void setCoords(int, int);
};
#endif //COORDS_H