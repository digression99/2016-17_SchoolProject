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
			System.out.println("������ �����մϴ�.");
			System.out.println("Buyer�� ���� �ܾ��� " + this.cash);
			System.out.println("Buyer�� ���ʽ� �ܾ��� " + this.point);
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
