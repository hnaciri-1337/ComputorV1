namespace ft {
    double pow(double x, int y) {
        double result = 1;
        for (int i = 0; i < y; i++)
            result *= x;
        return result;
    }

    double sqrt(double number) {
        if (number < 0)
            return -1;
        if (number == 0 || number == 1)
            return number;

        const double epsilon = 0.0000001;
        
        double low = 0;
        double high = number;
        
        while (high - low > epsilon) {
            double mid = low + (high - low) / 2;
            double square = mid * mid;
            
            if (square == number)
                return mid;
                
            if (square < number)
                low = mid;
            else
                high = mid;
        }
        
        return low + (high - low) / 2;
    }
}
