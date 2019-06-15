import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException; 

public class WebCrawler {
	 public static void main(String[] args) throws IOException { 
		 WebCrawler crawler = new WebCrawler();
		 Scanner in = new Scanner(System.in);
		 System.out.println("Vendos faqen fillestare:");
	     String initialPage = in.next();
	     System.out.println("Vendos thellesine:");
	     int depth = in.nextInt();
	     System.out.println("Vendos direktorine qe do ruhen faqen e aksesuara:");
	     String outputPath = in.next();
	     
	     FileWriter fw=new FileWriter(outputPath + "\\rezultatet.txt"); 
	     
	     int level = 1;

	     Queue<WebPage> queue = new LinkedList<WebPage>();
	     queue.add(crawler.new WebPage(initialPage, level));
	     fw.write(initialPage + "\n");

	     HashSet<String> marked = new HashSet<String>();
	     marked.add(initialPage);

	     while (!queue.isEmpty() && level < depth) {
	    	 String nextPage = queue.remove().url;
	         System.out.println("Vendos numrin e fqinjeve per faqen: " + nextPage);
	         int n = in.nextInt();
	         if(n != 0)   
	        	 System.out.println("Vendos faqet qe lidhen me faqen: " + nextPage);
	         
	         for(int i = 0; i < n; i++) {
	        	 String neighbour = in.next();
	        	 if(marked.contains(neighbour)) {
	            	System.out.println("Faqja qe vendoset eshte kontrolluar tashme.");
	            } else {
	            	fw.write(neighbour + "\n");
	            	queue.add(crawler.new WebPage(neighbour, level));
	            	marked.add(neighbour);
	            }
	            }
	         level++;
	        }
	     fw.close();
	    }
	 
	 public class WebPage {
		 String url;
		 int depth;
		 
		 public WebPage(String url, int depth) {
			 this.url = url;
			 this.depth = depth;
		 }
		 
		 @Override
		    public boolean equals(Object obj) 
		    { 
		          
			    if(this == obj) 
			            return true; 
			     
			    if(obj == null || obj.getClass()!= this.getClass()) 
			            return false; 
			          
			    WebPage page = (WebPage) obj; 

			        return page.url.equals(this.url); 
		    } 
		      
		    @Override
		    public int hashCode() 
		    { 
		    	int value = 0;
		    	for(int i = 0; i < url.length(); i++) {
		    		value += (int) url.charAt(i);
		    	}
		        return value; 
		    } 
	 }
}
