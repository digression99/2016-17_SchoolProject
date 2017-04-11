package javajava;

import java.util.*;

class BookCollection2
{
	private HashMap<String, Book> ht;
	BookCollection2()
	{
		ht = new HashMap<String, Book>();
		//this.setHt(new HashMap<String, Book>());
	}
	public HashMap<String, Book> getHt() {
		return ht;
	}
	public void setHt(HashMap<String, Book> ht) {
		this.ht = ht;
	}
}

public class Library_HashTable {
	public static void main(String[] args)
	{
		BookCollection2 bc = new BookCollection2();
		int num = 0;
		Scanner sc = new Scanner(System.in);
		
		while (true)
		{
			num = getNum(sc);
			if (num == 4) break;
			switch (num)
			{
			case 1:
				showBooks(bc);
				break;
			case 2:
				registerBook(bc, sc);
				break;
			case 3:
				searchBook(bc, sc);
				break;
			}
		}
		sc.close();
		
	}
	public static void showBooks(BookCollection2 bc)
	{
		String[] keys = bc.getHt().keySet().toArray(new String[0]);
		
		if (keys.length == 0)
		{
			System.out.println("No Data");
			return;
		}
		
		for(int i=0;i<keys.length;i++){
			 String key = keys[i];
			 Book val = bc.getHt().get(key);
			 
			 System.out.println(
					 "Book " + (i + 1) + "\n" +
					 val);
			}
	}
	public static void registerBook(BookCollection2 bc, Scanner sc)
	{
		Book tb = new Book();
		//Scanner sc = new Scanner(System.in);
		
		System.out.print(
				">>Please input the title : ");
		tb.setTitle(sc.next());
		System.out.print(
				">>Please input the author : ");
		tb.setAuthor(sc.next());
		System.out.print(
				">>Please input the publisher : ");
		tb.setPublisher(sc.next());
		
		bc.getHt().put(tb.getTitle(), tb);
		//sc.close();
	}
	public static void searchBook(BookCollection2 bc, Scanner sc)
	{
		//Scanner sc = new Scanner(System.in);
		String ts;
		Book tb = new Book();
		System.out.print(
				">>Please input the book title : ");
		ts = sc.next();
		
		tb = bc.getHt().get(ts);
		if (tb != null)
		{
			System.out.println(tb);
		}
		else
		{
			System.out.println("there is no such book.");
		}
		
		//sc.close();
	}
	public static int getNum(Scanner sc)
	{
		int num = 0;
		//Scanner sc = new Scanner(System.in);
		String[] menuStr = new String[4];
		menuStr[0] = "Book collections";
		menuStr[1] = "Register new Books";
		menuStr[2] = "Search a Book";
		menuStr[3] = "Exit";
		
		for (int i = 0; i < menuStr.length; i++)
		{
			System.out.println(
					(i + 1) + ". " + menuStr[i]);
		}
		System.out.println(
				">>Please select menu : ");
		num = sc.nextInt();
		//String s = sc.nextLine();
		//sc.close();
		return num;
	}
}
