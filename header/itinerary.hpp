class Route
{
public:
    std::string in;

    std::string out;

    Route(std::string in, std::string out)
    {
        this->in = in;
        this->out = out;
    }

    ~Route() { };
};

std::string itinerary(std::vector<Route> travel);