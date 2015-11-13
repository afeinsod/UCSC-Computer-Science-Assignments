// Alix Feinsod
// CruzID: afeinsod
// due October 27, 2014
// CMPS 12B/M
// Lab3
// Calc.java
// RPN Calculator

import java.lang.Exception;

class Stack {

    private Double[] stack;
    private int size;

    // Constructor for stack
    Stack () {
	stack = new Double[100];
    }

    public void push(Double d) {
	stack[size++] = d;
    }

    public Double pop() {
	Double temp = stack[size - 1];
	stack[size - 1] = null;
	size --;
	return temp;
    }

    public Double peek() {
	return stack[size - 1];
    }

    public int size() {
	return size;
    }

}


public class Calc {

    public Stack st;

    Calc() {
	st = new Stack();
	}


    public void  push(double n) {
	if (st.size() > 100) {
		throw new RuntimeException();
	}
	else {
       		st.push(n);
	}
    }


    public double pop() {
	if(st.size() <= 0) {
		throw new RuntimeException();
	}
	else {
		return st.pop();}
    }

    public double  peek() {
	if(st.size() <= 0) {
		throw new RuntimeException();
	}
	else {
		return st.peek();}
    }



    public void  add() {
	if (st.size() < 2) {
		throw new RuntimeException();
		}
	else {
		double temp = st.pop() + st.pop();
		st.push(temp);
		}	
	}	
	

    public void subtract() {
	if (st.size() < 2) {
		throw new RuntimeException();
		}
	else{
		double temp = -(st.pop() - st.pop());
		st.push(temp);
		}	
    }


    public void multiply() {
	if (st.size() < 2) {
			throw new RuntimeException();
		}
	else {
		double temp = st.pop() * st.pop();
		st.push(temp);
		}
    	}


    public void divide() {
	if (st.size() < 2) {
		throw new RuntimeException();
		}
	else {
		double tempDenom = st.pop();
		double tempNum = st.pop();
		double temp = tempNum / tempDenom;
		st.push(temp);
		}	
    }

    public int depth() {
	return st.size();
    }

    public void  reciprocal() {
	if (st.size() < 1) {
		throw new RuntimeException();
	}
	else {
       		double temp = st.pop();
		temp = 1/temp;
		st.push(temp);
	}
    }

}
