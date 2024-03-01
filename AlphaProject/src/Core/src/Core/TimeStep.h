namespace Core {

class TimeStep {
   private:
    float time;

   public:
    TimeStep(float _time = 0.0f) : time(_time) {}

    operator float() const { return time; }

    float GetSeconds() const { return time; }
    float GetMiliseconds() const { return time * 1000.0f; }
};

}  // namespace Core