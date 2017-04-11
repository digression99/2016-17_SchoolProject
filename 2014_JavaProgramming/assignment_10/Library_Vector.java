package javajava;

import java.util.*;
//
// 1. display a menu screen, the following is example
//
// (1). book collections
// (2). register new books
// (3). search a book
// (4). exit
//
// 2. select a number 
// 3. display all registered books when the user
// selects 1 and go back to the menu.
// 4. register new books when the user selects 2 and
// go back to the menu.
// 5. search registered books when the user selects 3.
// 6. quit the program when the user selects 4.
// 7. use a while loop and scanner for input.
// 8. formal parameters, return types, class names, and
// method names are up to me.
//
// 2 -> title, author, publisher
// 3 -> title search
//

class BookCollection extends Book
{
	private Vector<Book> v;
	BookCollection()
	{
		this.v = new Vector<Book>();
	}
	public Vector<Book> getV() {
		return v;
	}
	public void setV(Vector<Book> v) {
		this.v = v;
	}
}

class Book
{
	private String author;
	private String title;
	private String publisher;
	public Book(String author, String title, String publisher)
	{
		this.setAuthor(author);
		this.setTitle(title);
		this.setPublisher(publisher);
	}
	public Book()
	{
		this("" ,"" ,"");
	}
	public String getAuthor() {
		return author;
	}
	public void setAuthor(String author) {
		this.author = author;
	}
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public String getPublisher() {
		return publisher;
	}
	public void setPublisher(String publisher) {
		this.publisher = publisher;
	}
	public String toString()
	{
		return new String(
				"Title : " + this.title +
				"\nAuthor : " + this.author +
				"\nPublisher : " + this.publisher);
	}
	public boolean equals(Object o)
	{
		if (this.title.equals(((Book)o).title))
		{
			return true;
		} else
		{
			return false;
		}
	}
}

public class Library_Vector {
	public static void main(String[] args)
	{
		BookCollection bc = new BookCollection();
		Scanner sc = new Scanner(System.in);
		int num = 0;
		
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
				//v.add(registerBook());
				break;
			case 3:
				searchBook(bc, sc);
				break;
			}
		}
		sc.close();
	}
	public static void showBooks(BookCollection bc)//Vector<Book> v)
	{
		//bc.getV().iterator()
		Iterator<Book> i = bc.getV().iterator();
		int num = 1;
		
		if (!i.hasNext())
		{
			System.out.println("No Data");
			return;
		}
		
		while (i.hasNext())
		{
			System.out.println(
					"Book " + num + "\n" +
					i.next());
			num++;
		}
	}
	public static void registerBook(BookCollection bc, Scanner sc)//)
	{
		Book tb = new Book();
		
		System.out.print(
				">>Please input the title : ");
		tb.setTitle(sc.next());
		System.out.print(
				">>Please input the author : ");
		tb.setAuthor(sc.next());
		System.out.print(
				">>Please input the publisher : ");
		tb.setPublisher(sc.next());
		
		bc.getV().add(tb);
	}
	public static void searchBook(BookCollection bc, Scanner sc)//Vector<Book> v)
	{
		boolean check = false;
		String ts;
		Book tb = new Book();
		System.out.print(
				">>Please input the book title : ");
		ts = sc.next();
		tb.setTitle(ts);
		
		Iterator<Book> i = bc.getV().iterator();
		
		while(i.hasNext())
		{
			Book b = i.next();
			if (b.equals(tb))
			{
				System.out.println(b);
				check = true;
				break;
			}
		}
		if (!check)
		{
			System.out.println("There is no such book.");
		}
	}
	public static int getNum(Scanner sc)
	{
		int num;
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
		System.out.print(
				">>Please select menu : ");
		num = sc.nextInt();
		return num;
	}

}
