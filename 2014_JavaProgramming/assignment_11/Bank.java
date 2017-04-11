package javajava;

public class Bank {
	private int saveAccount;
	public Bank()
	{
		this.saveAccount = 10000;
	}
	void withdraw(int money)
	{
		this.saveAccount -= money;
	}
	void deposit(int money)
	{
		this.saveAccount += money;
	}
	void checkTheBalance()
	{
		System.out.println(
				"Buyer의 은행 잔액은 " +
		this.saveAccount);
	}
	int getBalance()
	{
		return this.saveAccount;
	}
}