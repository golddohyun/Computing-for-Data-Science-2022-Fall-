#pragma once
class Bear {
        protected:
        float weight;
        
        public:
        Bear();
        Bear(float aWeight);

        void SetWeight(float aWeight);
        float GetWeight(void);
        float Aggressiveness(void);
        virtual void PrintSelf(void);
		~Bear();
};


class Polar: public Bear{
        public:
        Polar();
        Polar(float aWeight);
        float Aggressiveness(void);
        void PrintSelf(void);
		~Polar();
};

class Grizzly : public Bear{
        public:
        Grizzly();
        Grizzly(float aWeight);
        float Aggressiveness(void);
        void PrintSelf(void);
		~Grizzly();
};


class Black : public Bear{
        public:
        Black();
        Black(float aWeight);
        float Aggressiveness(void);
        void PrintSelf(void);
        ~Black();
};

class Black_Momma : public Black {
		protected:
		float cubweight;
		int cub;
		Bear *aCub;
		
        public :
        Black_Momma();
        Black_Momma(float aWeight);
        void AddCub(Black *aCub);
        float TotalAggressiveness(void);
        float Aggressiveness(void);
        void PrintSelf(void);
        ~Black_Momma();
        
};

