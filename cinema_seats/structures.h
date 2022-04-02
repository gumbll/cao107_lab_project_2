struct Order
{
  std::string custName;
  std::string color;
  std::vector<std::string> seatIds;
  bool sold {false};
};

struct Seat
{
  std::string id;
  bool available {true};
};
