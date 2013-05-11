import java.util.*;
import java.lang.*;
import java.util.Locale;
import java.text.DateFormat;
import java.util.Date;
import java.text.Collator;
import java.text.DateFormatSymbols;
import java.text.Normalizer;
import java.text.SimpleDateFormat;

public class Localizer
{
	public static void main (String[] args) throws java.lang.Exception
	{
        Locale[] locales = Locale.getAvailableLocales();
        
        //sorting locales
        sortArray(Collator.getInstance(Locale.ENGLISH), locales);
        
        int i = 0;
        int j = 0;
        List<Lang> langs = new ArrayList<Lang>();
        List<Order> orders = new ArrayList<Order>();
        
        for(Locale l : locales){
            i++;
            if(blacklisted(i))continue;
            SimpleDateFormat sf = (SimpleDateFormat) DateFormat.getDateInstance(DateFormat.LONG, l);
            String pattern = clearPattern(sf.toPattern());
            //String pattern = sf.toPattern();
            Order order = hasOrder(orders, pattern);
            if(order == null){
            	j++;
            	order = new Order(j, pattern);
            	orders.add(order);
            }
            Lang main = hasMainCountry(langs, l.getLanguage());
        	Lang lang = hasOrderCountry(langs, order, l.getLanguage());
        	if(lang==null){
        		if(main==null){
            		if(l.getCountry().equals(""))langs.add(new Lang(i, l, l.getDisplayLanguage(), l.getLanguage(), order));
            		else langs.add(new Lang(i, l, l.getDisplayLanguage() + "_" + l.getCountry(), l.getLanguage(), order));
        		}else{
            		if(l.getCountry().equals(""))langs.add(new Lang(main.i, l, l.getDisplayLanguage(), l.getLanguage(), order));
            		else langs.add(new Lang(main.i, l, l.getDisplayLanguage() + "_" + l.getCountry(), l.getLanguage(), order));
        		}
        	}else{
        		if(!l.getCountry().equals(""))lang.screen_name += "_" + l.getCountry();
        	}
        }

        System.out.println("/*");
        int k = 0;
        for(Lang l: langs){
        	if(!l.screen_name.contains("_"))continue;
        	k++;
        	System.out.println(" * -" + k + " " + l.i + " " + l.order.order + " " + l.screen_name);
        }
        System.out.println(" */");
        
        Set<Integer> done_langs = new HashSet<Integer>();
        for(Lang l: langs){
        	//System.out.println(l.i + " " + l.order.order + " " + l.screen_name + " " + l.order.order_details);
        	
        	if(!l.screen_name.contains("_"))continue;
        	
        	if(!done_langs.contains(l.i))done_langs.add(l.i);
        	else continue;
        	
            DateFormatSymbols symbols = new DateFormatSymbols(l.l);
            
            
            String[] dayNames = symbols.getShortWeekdays();
            String[] monthNames = symbols.getMonths();
            
            //precompiler condition
            System.out.println("#if LANG == " + l.i);
            System.out.println("// " + l.l.getDisplayLanguage());
            
            //day array body
            System.out.println("static const char* const DAYS[] = {");
            for (String s : dayNames) { 
                if(s.length()==0)continue;
               String norm = Normalizer
                .normalize(s, Normalizer.Form.NFD)
                .replaceAll("[^\\p{ASCII}]", "");
               System.out.print("\"" + norm.toUpperCase() + "\",");
               System.out.println(" /* " + s + " */");
            }
            System.out.println("};");
            System.out.println();
            
            //month array body
            System.out.println("static const char* const MONTHS[] = {");
            for (String s : monthNames) { 
                if(s.length()==0)continue;
               String norm = Normalizer
                .normalize(s, Normalizer.Form.NFD)
                .replaceAll("[^\\p{ASCII}]", "");
               System.out.print("\"" + norm.toUpperCase() + "\",");
               System.out.println(" /* " + s + " */");
            }
            System.out.println("};");
            
            System.out.println("#endif ");
            System.out.println();
        }
    	
    	for(Order o: orders){
            //precompiler condition
            System.out.println("#if ORDER == " + o.order);
            System.out.println("// " + o.order_details);
            
            System.out.println("void draw_date(PblTm* t) {");
            
            System.out.println("char day[] = \"14\";");
            System.out.println("string_format_time(day, sizeof(day), \"%d\", t);");
            
            System.out.println("size_t size = sizeof(date_text);");
            System.out.println("memset(date_text, 0, size);");
            	  
            System.out.println("strncat(date_text, DAYS[t->tm_wday], size);");
            System.out.println("size -= strlen(DAYS[t->tm_wday]);");
            System.out.println("strncat(date_text, \", \", size);");
            System.out.println("size -= strlen(\", \");");
            
            if(o.order_details.startsWith("D")){
                System.out.println("strncat(date_text, day, size);");
                System.out.println("size -= strlen(\"12\");");
                
                System.out.println("strncat(date_text, \"" + o.order_details.substring(1, o.order_details.length()-1) + "\", size);");
                System.out.println("size -= strlen(\"" + o.order_details.substring(1, o.order_details.length()-1) + "\");");
                
                System.out.println("strncat(date_text, MONTHS[t->tm_mon], size);");
            }else{
                System.out.println("strncat(date_text, MONTHS[t->tm_mon], size);");
                System.out.println("size -= strlen(MONTHS[t->tm_mon]);");
                
                System.out.println("strncat(date_text, \"" + o.order_details.substring(1, o.order_details.length()-1) + "\", size);");
                System.out.println("size -= strlen(\"" + o.order_details.substring(1, o.order_details.length()-1) + "\");");
                
                System.out.println("strncat(date_text, day, size);");
            }
            System.out.println("text_layer_set_text(&date_layer, date_text);");
            
            System.out.println("}");
            
            System.out.println("#endif ");
            System.out.println();
    	}
        
        System.out.println();
	}
	
	private static Lang hasMainCountry(List<Lang> langs, String lang) {
		for(Lang l: langs){
			if(l.lang == lang){
				return l;
			}
		}
		return null;
	}

	private static String clearPattern(String pattern){
		String cleared = "";
		boolean apostrophe = false;
		boolean month = false;
		boolean day = false;
		for(int i = 0; i<pattern.length(); i++){
			if(pattern.charAt(i)=='\''){
				if(apostrophe==true)apostrophe=false;
				else apostrophe=true;
				continue;
			}else if(!apostrophe){
				if(pattern.charAt(i)=='M'&&!month){
					month = true;
					cleared += pattern.charAt(i);
				}
				if(pattern.charAt(i)=='d'&&!day){
					day = true;
					cleared += pattern.charAt(i);
				}
				if(pattern.charAt(i)==' '){
					if(month&&day){
						//skippin
					}else if(month||day){
						//between month and day
						cleared += pattern.charAt(i);
					}
				}
			}else{
				if(month&&day){
					//skippin
				}else if(month||day){
					//between month and day
					cleared += pattern.charAt(i);
				}
			}
		}
		return cleared.toUpperCase();
	}

	private static Lang hasOrderCountry(List<Lang> langs, Order order, String lang) {
		for(Lang l: langs){
			if(l.order == order && l.lang == lang){
				return l;
			}
		}
		return null;
	}

	public static Order hasOrder(List<Order> orders, String order){
		for(Order o: orders){
			if(o.order_details.equals(order)){
				return o;
			}
		}
		return null;
	}
    
  public static void sortArray(Collator collator, Locale[] strArray) {
  Locale tmp;
  if (strArray.length == 1) return;
  for (int i = 0; i < strArray.length; i++) {
    for (int j = i + 1; j < strArray.length; j++) {
      if( collator.compare(strArray[i].getDisplayName(), strArray[j].getDisplayName() ) > 0 ) {
        tmp = strArray[i];
        strArray[i] = strArray[j];
        strArray[j] = tmp;
        }
      }
    }
  }
  
  public static boolean blacklisted(int i){
      if(i>=3&&i<=24)return true;
      if(i>=27&&i<=31)return true;
      if(i>=68&&i<=73)return true;
      if(i>=85&&i<=89)return true;
      if(i>=94&&i<=95)return true;
      if(i>=110&&i<=113)return true;
      if(i>=118&&i<=120)return true;
      if(i>=148&&i<=150)return true;
      if(i>=153&&i<=154)return true;
      return false;
  }
}

class Lang{
	
	public int i;
	public Locale l;
	public String screen_name;
	public String lang;
	public Order order;
	
	public Lang(){
		//nothing here
	}
	
	public Lang(int i, Locale l, String screen_name, String lang, Order o){
		this.i =i;
		this.l = l;
		this.screen_name = screen_name;
		this.lang = lang;
		this.order = o;
	}
}

class Order{
	public int order;
	public String order_details;
	
	public Order(){
		//nothing here
	}
	
	public Order(int order, String order_details){
		this.order = order;
		this.order_details = order_details;
	}
}
