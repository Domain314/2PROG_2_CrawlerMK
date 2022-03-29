#ifndef DOMAIN_H
#define DOMAIN_H
#pragma once
#include <cstdlib>
#include <string>

#define randomNum(max) (std::rand()%max)

namespace Domain
{
    typedef struct Vector2 {
        int x;
        int y;

        Vector2(int x = 0, int y = 0) {
            this->x = x;
            this->y = y;
        };

        void setAllSides(int x, int y) {
            this->x = x;
            this->y = y;
        }

        void setSideFromIndex(int index, int amount) {
            switch (index) {
                case 0: this->x += amount; break;
                case 1: this->y += amount; break;
                default: break;
            }
        }

        int getSideFromIndex(int index) {
            switch (index) {
                case 0: return x; break;
                case 1: return y; break;
                default: break;
            }
            return 0;
        }

    }Vector2;

    typedef struct Vector3 {
        int x;
        int y;
        int z;

        Vector3(int x = 0, int y = 0, int z = 0) {
            this->x = x;
            this->y = y;
            this->z = z;
        };

        void setAllSides(int x, int y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        void setSideFromIndex(int index, int amount) {
            switch (index) {
                case 0: this->x += amount; break;
                case 1: this->y += amount; break;
                case 2: this->z += amount; break;
                default: break;
            }
        }

        int getSideFromIndex(int index) {
            switch (index) {
                case 0: return x; break;
                case 1: return y; break;
                case 2: return z; break;
                default: break;
            }
            return 0;
        }

    }Vector3;

    /*
    int randomNum(int max) {
        return std::rand()%max;
    }
    */
}
#endif // DOMAIN_H