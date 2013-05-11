import java.util.Locale;
import java.text.DateFormatSymbols;
import java.text.Collator;
import java.text.Normalizer;
 
public class Localizer
{
  public static void main (String[] args) throws java.lang.Exception
  {
    Locale[] locales = Locale.getAvailableLocales();
    
    //sorting locales
    sortArray(Collator.getInstance(Locale.ENGLISH), locales);
    
    //comment first
    System.out.println("/*");
    int i = 0;
    for(Locale l : locales){
        i++;
        if(l.getDisplayName().contains("("))continue;
        if(blacklisted(i))continue;
        System.out.print(" * " + i + " " + l.getDisplayName());
        System.out.println();
    }
    System.out.println(" */");
    
    //body
    i = 0;
    for(Locale l : locales){
        i++;
        if(blacklisted(i))continue;
        if(l.getDisplayName().contains("("))continue;
        DateFormatSymbols symbols = new DateFormatSymbols(l);
        String[] dayNames = symbols.getShortWeekdays();
        
        //precompiler condition
        System.out.println("#if LANG == " + i);
        System.out.println("// " + l.getDisplayName());
        
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
        
        System.out.println("#endif ");
        System.out.println();
    }
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
