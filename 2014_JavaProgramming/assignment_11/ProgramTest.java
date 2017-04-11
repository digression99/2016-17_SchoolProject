package javajava;

import java.util.*;

public class ProgramTest {
	public static void main(String[] args)
	{
		Buyer byr = new Buyer();
		Bank bk = new Bank();
		Scanner sc = new Scanner(System.in);
		int num = 0;
		
		while (true)
		{
			System.out.println("아래에서 진행할 업무를 선택하세요. 나가시려면 0을 눌러주세요.");
			System.out.println("1. 물건 구매 \t 2. 은행 업무" );
			
			num = sc.nextInt();
			
			switch (num)
			{
			case 1:
				buyProducts(byr, bk, sc);
				break;
			case 2:
				bankWork(byr, bk, sc);
				break;
			}
			
			if (num == 0)
			{
				System.out.println("프로그램이 종료되었습니다.");
				break;
			}
		}
	}
	public static void buyProducts(Buyer b, Bank bk, Scanner sc)
	{
		int num = 0;
		Product p = null;
		System.out.println("아래에서 구매할 상품을 선택하세요.");
		System.out.println(
				"1 : TV \t 2 : Computer \t 3 : Printer \t 4 : Laptop");
		num = sc.nextInt();
		
		switch (num)
		{
		case 1:
			p = new TV();
			break;
		case 2:
			p = new Computer();
			break;
		case 3:
			p = new Printer();
			break;
		case 4:
			p = new Laptop();
			break;
		}
		System.out.println(p);
		b.buy(p);	
	}
	public static void bankWork(Buyer b, Bank bk, Scanner sc)
	{
		int num;
		System.out.println("아래에서 진행할 업무를 선택하세요. 나가시려면 0을 눌러주세요");
		System.out.println("1 : 출금 \t 2 : 입금 \t 3 : 잔고");
		num = sc.nextInt();
		
		switch (num)
		{
		case 0:
			return;
		case 1:
			System.out.println("출금할 금액을 입력하세요.");
			num = sc.nextInt();
			if (num < bk.getBalance())
			{
				bk.withdraw(num);
				b.plusCash(num);
				System.out.println("Buyer의 현금 잔액은 " + b.getRemainingCash());
			}
			else
			{
				System.out.println("잔고가 부족합니다.");
			}
			bk.checkTheBalance();
			break;
		case 2:
			System.out.println("입금할 금액을 입력하세요.");
			num = sc.nextInt();
			if (num < b.getRemainingCash())
			{
				bk.deposit(num);
				b.minusCash(num);
				System.out.println("Buyer의 현금 잔액은 " + b.getRemainingCash());
			} 
			else
			{
				System.out.println("소지한 금액이 부족합니다.");
			}
			bk.checkTheBalance();
			break;
		case 3:
			bk.checkTheBalance();
			break;
		}
	}
}
