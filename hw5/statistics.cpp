#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

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
		m_isEmpty = false;
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		if (m_isEmpty)
			throw std::logic_error("No data");
		return m_min;
	}

	const char * name() const override {
		return "Min";
	}

private:
	double m_min;
	bool m_isEmpty = true;
};

class Max : public IStatistics {
public:
	Max() : m_max{ -std::numeric_limits<double>::min() } {
	}

	void update(double next) override {
		m_isEmpty = false;
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		if (m_isEmpty)
			throw std::logic_error("No data");
		return m_max;
	}

	const char* name() const override {
		return "Max";
	}

private:
	double m_max;
	bool m_isEmpty = true;
};

class Mean : public IStatistics {
public:
	Mean()  {
	}

	void update(double next) override {
		m_isEmpty = false;
		m_sum += next;
		++m_count;
		m_mean = m_sum / m_count;
	}

	double eval() const override {
		if (m_isEmpty)
			throw std::logic_error("No data");
		return m_mean;
	}

	const char* name() const override {
		return "Mean";
	}

private:
	double m_mean = 0;
	double m_sum = 0;
	int m_count = 0;
	bool m_isEmpty = true;
};

class StandardDeviation : public IStatistics {
public:
	StandardDeviation() {
	}

	void update(double next) override {
		m_isEmpty = false;
		m_mean.update(next);
		m_sq_mean.update(next * next);
		m_std = std::sqrt(m_sq_mean.eval() - m_mean.eval() * m_mean.eval());
	}

	double eval() const override {
		if (m_isEmpty)
			throw std::logic_error("No data");
		return m_std;
	}

	const char* name() const override {
		return "Standard Deviation";
	}

private:
	double m_std = 0;
	Mean m_mean;
	Mean m_sq_mean;
	bool m_isEmpty = true;
};


int main() {

	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new StandardDeviation{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
		break;
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
