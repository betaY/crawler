import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import org.jsoup.*;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.lang.System.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by Beta on 16/9/10.
 */


public class Crawler {
    private Queue<String> urlQ;
    private Queue<String> visitQ;
    int times = 1000;
    Crawler(String url) {
        urlQ = new LinkedList();
        visitQ = new LinkedList();
        urlQ.add(url);
        visitQ.add(url);
    }


    public void parsePage(){
        times--;

        if (times < 0) {
            return;
        }
//        if (visitQ.size() > 1000) return;
        System.out.printf("visitQ size(): %d\t", visitQ.size() );

        Document doc;
        if (urlQ.size() == 0) {
            return;
        }
        String url = urlQ.remove();
        System.out.println(url);



        try {
            doc = Jsoup.connect(url).get();
//            System.out.println(doc);
            Elements links = doc.select("a[href]");
            for(Element link: links) {
                String temp = link.attr("abs:href");
                temp = temp.split("#")[0];
//                System.out.println(temp);
//                System.out.printf("\turlQ size: %d\n", urlQ.size());

//                Pattern href = Pattern.compile("href=\".*\"");
//                m = href.matcher(link);
                if (visitQ.contains(temp) || temp.equals(url) || temp.contains("mailto")) {
//
//                    System.out.printf("urlQ size: %d\n", urlQ.size());
                    //parsePage();
                }
                else  {
                    urlQ.add(temp);
                    visitQ.add(temp);
//                    System.out.println(temp);
//                    parsePage();
                }
                // bfs
//                parsePage();
            }
        } catch (Exception e) {
//            e.printStackTrace();
        }
        // dfs
        parsePage();
        return;
    }

    public static void main(String[] args) {
        System.out.println("Enter the Url you want to crawl: ");
        Scanner sc = new Scanner(System.in);
        Pattern html = Pattern.compile("[a-zA-z]+://[^\\s]*");
        String url = "";
        url = sc.next();
        Matcher m = html.matcher(url);
        while (m.matches() == false) {
            System.out.println("Format is not correct.");
            System.out.println("Enter the Url you want to crawl: ");
            url = sc.next();
            m = html.matcher(url);
        }
        Crawler crawler = new Crawler(url);
//        crawler.urlQ.add(url)
//        System.out.println(url);
        crawler.parsePage();
    }
}
