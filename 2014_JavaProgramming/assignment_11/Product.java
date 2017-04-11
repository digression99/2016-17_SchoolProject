package javajava;

abstract public class Product {
	protected int pr;
	protected int bp;
	abstract public int price();
	abstract public int bonusPoint();
}

class TV extends Product
{
	public TV()
	{
		this.pr = 500;
		this.bp = 10;
	}
	public int price()
	{
		return this.pr;
	}
	public int bonusPoint()
	{
		return this.bp;
	}
	public String toString()
	{
		return new String("TV의 가격은 " + this.pr + "TV의 보너스 포인트는 " + this.bp);
	}
}

class Computer extends Product
{
	public Computer()
	{
		this.pr = 1000;
		this.bp = 20;
	}
	public int price()
	{
		return this.pr;
	}
	public int bonusPoint()
	{
		return this.bp;
	}
	public String toString()
	{
		return new String("Computer의 가격은 " + this.pr + 
				"Computer의 보너스 포인트는 " + this.bp);
	}
}

class Printer extends Product
{
	public Printer()
	{
		this.pr = 300;
		this.bp = 5;
	}
	public int price()
	{
		return this.pr;
	}
	public int bonusPoint()
	{
		return this.bp;
	}
	public String toString()
	{
		return new String("Printer의 가격은 " + this.pr + 
				"Printer의 보너스 포인트는 " + this.bp);
	}
}

class Laptop extends Product
{
	public Laptop()
	{
		this.pr = 900;
		this.bp = 50;
	}
	public int price()
	{
		return this.pr;
	}
	public int bonusPoint()
	{
		return this.bp;
	}
	public String toString()
	{
		return new String("Laptop의 가격은 " + this.pr + 
				"Laptop의 보너스 포인트는 " + this.bp);
	}
}