package javajava;

public class Buyer {
	private int cash;
	private int point;
	public Buyer()
	{
		this.cash = 1000;
		this.point = 10;
	}
	void buy(Product p)
	{
		if (p.pr <= this.cash)
		{
			this.cash -= p.pr;
			this.point += p.bp;
		}
		else
		{
			System.out.println("현금이 부족합니다.");
			System.out.println("Buyer의 현금 잔액은 " + this.cash);
			System.out.println("Buyer의 보너스 잔액은 " + this.point);
		}
	}
	int getRemainingCash()
	{
		return this.cash;
	}
	int getSavedBonusPoint()
	{
		return this.point;
	}
	void plusCash(int c)
	{
		this.cash += c;
	}
	void minusCash(int c)
	{
		this.cash -= c;
	}
}
