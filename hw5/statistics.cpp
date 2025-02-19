#include <iostream>
#include <limits>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		if (m_min == std::numeric_limits<double>::max())
			return -1;
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};


class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::lowest()} {
	}
	
	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}
	
	double eval() const override {
		if (m_max == std::numeric_limits<double>::lowest())
			return -1;
		return m_max;
	}
	
	const char * name() const override {
		return "max";
	}
	
private:
	double m_max;
};


class Mean : public IStatistics {
public:
	Mean() : m_sum{0.}, count{0} {
	}
		
	void update(double next) override {
		count++;
		m_sum += next;
	}
		
	double eval() const override {
		if (count != 0) {
			return m_sum / count;
		}
		else 
			return -1;
	}
		
	const char * name() const override {
		return "mean";
	}
		
	private:
		double m_sum;
		int count;
};


class Std : public IStatistics {
public:
	Std() : m_std{0.} {
	}
				
	void update(double next) override {
		m_mean.update(next);
		values.push_back(next);
	}
				
	double eval() const override {

		double s(0.);
	
		if (values.size() == 0) 
			return -1;

		for(double val : values) {
			s += std::pow((val - m_mean.eval()), 2);
		}
		s /= values.size();

		return std::sqrt(s);
	}
				
	const char * name() const override {
		return "std";
	}
				
	private:
		double m_std;
		std::vector<double> values;
		Mean m_mean;
};

int main() {

	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}