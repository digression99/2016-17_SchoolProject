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
			System.out.println("�Ʒ����� ������ ������ �����ϼ���. �����÷��� 0�� �����ּ���.");
			System.out.println("1. ���� ���� \t 2. ���� ����" );
			
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
				System.out.println("���α׷��� ����Ǿ����ϴ�.");
				break;
			}
		}
	}
	public static void buyProducts(Buyer b, Bank bk, Scanner sc)
	{
		int num = 0;
		Product p = null;
		System.out.println("�Ʒ����� ������ ��ǰ�� �����ϼ���.");
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
		System.out.println("�Ʒ����� ������ ������ �����ϼ���. �����÷��� 0�� �����ּ���");
		System.out.println("1 : ��� \t 2 : �Ա� \t 3 : �ܰ�");
		num = sc.nextInt();
		
		switch (num)
		{
		case 0:
			return;
		case 1:
			System.out.println("����� �ݾ��� �Է��ϼ���.");
			num = sc.nextInt();
			if (num < bk.getBalance())
			{
				bk.withdraw(num);
				b.plusCash(num);
				System.out.println("Buyer�� ���� �ܾ��� " + b.getRemainingCash());
			}
			else
			{
				System.out.println("�ܰ� �����մϴ�.");
			}
			bk.checkTheBalance();
			break;
		case 2:
			System.out.println("�Ա��� �ݾ��� �Է��ϼ���.");
			num = sc.nextInt();
			if (num < b.getRemainingCash())
			{
				bk.deposit(num);
				b.minusCash(num);
				System.out.println("Buyer�� ���� �ܾ��� " + b.getRemainingCash());
			} 
			else
			{
				System.out.println("������ �ݾ��� �����մϴ�.");
			}
			bk.checkTheBalance();
			break;
		case 3:
			bk.checkTheBalance();
			break;
		}
	}
}
