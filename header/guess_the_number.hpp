class Guesser
{
public:
    Guesser(int number, int lives);
    bool guess(int n);

private:
    int number, lives;
};