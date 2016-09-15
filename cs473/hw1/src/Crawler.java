import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import org.jsoup.*;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import java.io.*;

import java.lang.System.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.tartarus.snowball.ext.englishStemmer;
/**
 * Created by Beta on 16/9/10.
 */


public class Crawler {
    private Queue<String> urlQ;
    private Queue<String> visitQ;
    BufferedWriter file;
    private String text = "";
    int times = 250;
    int dup = 0;
    boolean bfs = false, dfs = false;
    int depth = 0, maxDepth = 0, nodesize = 0;
    Crawler(String url) {
        urlQ = new LinkedList();
        visitQ = new LinkedList();
        urlQ.add(url);
        visitQ.add(url);
    }


    public void parsePage(){


        if (times < 0) {
            return;
        }

        // for bfs
//        if (bfs) {
//            if(visitQ.size() <= 1000) {
//                depth++;
//            }
//        }
        // end for bfs
//        if (times == 999) {
//            nodesize = urlQ.size();
//        }
//        if (visitQ.size() > 1000) return;
        System.out.printf("nodesize: %d\t", nodesize);
        System.out.printf("i:%d  Qsize: %d\turlQ: %d\tdup: %d\tdepth: %d\tMaxD: %d\t",
                times, visitQ.size(), urlQ.size(), dup, depth, maxDepth);


        Document doc;
        if (urlQ.size() == 0) {
            System.out.println();
            return;
        }
//        if (bfs) {
            String url = urlQ.remove();
            System.out.println(url);
//        }



        try {
            doc = Jsoup.connect(url).get();
//            file = new BufferedWriter(new FileWriter("text.txt"));
//            file.write(doc.text().toLowerCase());
            text = text+doc.text();

//            System.out.println(doc.text());
            Elements links = doc.select("a[href]");
            for(Element link: links) {
                String temp = link.attr("abs:href");
                temp = temp.split("#")[0];
//                System.out.println(temp);
//                System.out.printf("\turlQ size: %d\n", urlQ.size());

//                Pattern href = Pattern.compile("href=\".*\"");
//                m = href.matcher(link);
                if (visitQ.contains(temp) || temp.equals(url) || temp.contains("mailto")) {
                    if (temp.contains("mailto") == false) {
                        dup++;
                    }
//                    System.out.printf("urlQ size: %d\n", urlQ.size());
//                    times--;
//                    if(dfs) {
//                        depth--;
//                    }
//                    parsePage();
//                    if (maxDepth < depth) {
//                        maxDepth = depth;
//                    }
//                    depth = 0;
                }
                else  {
                    urlQ.add(temp);
                    visitQ.add(temp);
//                    if (times == 0) {
//                        nodesize++;
//                    } else
//                    System.out.println(temp);
                    // start dfs
                    if(dfs) {
                        times--;
                        depth++;
                        parsePage();

                    }
                    // end dfs
                }
            }
            if (dfs) {
                if (maxDepth < depth) {
                    maxDepth = depth;
                }
                depth--;
            }
        } catch (Exception e) {
//            e.printStackTrace();
        }
        // start bfs
        if(bfs) {
            times--;
            depth++;
            parsePage();
            if (maxDepth < depth) {
                maxDepth = depth;
            }
            depth = 0;
        }
        // end bfs

        return;
    }
    public static <K, V> void printMap(Map<K, V> map) {
        for (Map.Entry<K, V> entry : map.entrySet()) {
            System.out.println(entry.getKey()
                    + "," + entry.getValue()+ ",");
        }
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Enter the Url you want to crawl: ");
        long start = System.nanoTime();
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
//        crawler.dfs = true;
        crawler.bfs = true;
//        crawler.urlQ.add(url)
//        System.out.println(url);
        String temp;
        crawler.parsePage();
        try {
            crawler.file = new BufferedWriter(new FileWriter("text.txt"));
            temp = crawler.text.toLowerCase();

            crawler.file.write(crawler.text.toLowerCase());
            crawler.file.close();
        } catch (IOException e) {
//            e.printStackTrace();
        }

        System.out.printf("Qsize: %d\turlQ size: %d\tduplicate number: %d\tdepth: %d\tMaxD: %d\n",
                crawler.visitQ.size(), crawler.urlQ.size(), crawler.dup, crawler.depth, crawler.maxDepth);
        long elapsedTime = System.nanoTime() - start;
        System.out.printf("Time: %d\n", elapsedTime);
        HashMap<String, Integer> hmap = new HashMap<String, Integer>();

        englishStemmer stemmer = new englishStemmer();
        String[] token =  crawler.text.toLowerCase().split(" ");

        for(String s: token) {
            stemmer.setCurrent(s);
            if (stemmer.stem())  {
                s = stemmer.getCurrent();
            }
        }
        for (int i = 0; i < token.length; i++) {
            stemmer.setCurrent(token[i]);
            if(stemmer.stem()) {
                token[i] = stemmer.getCurrent();
            }
        }

        List asList = Arrays.asList(token);
        Set<String> mySet = new HashSet<String>(asList);
        int max = 0, totalWord = 0;

        for (String s: mySet) {
//            System.out.println(s + " " +Collections.frequency(asList,s));
//            max = Collections.frequency(asList,s));
            hmap.put(s, Collections.frequency(asList,s));
            totalWord += Collections.frequency(asList,s);
        }
        System.out.printf("Average: %d, %d\n\n", token.length, hmap.size());

//        Map<String, Integer> treem = new TreeMap<String, Integer>(hmap);
//        printMap(treem);
    }
}
