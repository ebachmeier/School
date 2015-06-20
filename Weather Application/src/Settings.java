import java.io.Serializable;

/**
 * Class for storing the users settings while using the application
 * 
 * @author Marc Stahl
 *
 */

public class Settings implements Serializable
{

	private static final long serialVersionUID = 1L;
	static Settings instance;
	String location;
	String[] elements;
	String unit;
	String[] htmlList;
	String [] commaList;
	int index;
	int numCities;
	
	public Settings(){
	}
	
	// should it be protected?
	public Settings(String[] html, String[] comma, String u, String l, int i, int num, String[] e) {
		this.htmlList = html;
		this.commaList = comma;
		this.location = l;
		this.numCities = num;
		this.unit = u;
		this.elements = e;
		this.index = i;
	}
	
	public String getLocation() {
//		System.out.println("SINGLETON: Get location:"+location);
		return location;
	}
	
	public void setLocation(String l) {
//		System.out.println("SINGLETON: Set location:"+l);
		this.location = l;
	}
	
	public int getLocationIndex()
	{
//		System.out.println("SINGLETON: Get location indx:"+index);
		return index;
	}
	
	public void setLocationIndex(int locationIndex)
	{
//		System.out.println("SINGLETON: Set location indx:"+locationIndex);
		this.index = locationIndex;
	}
	
	public void setElements(String[] e) {
		this.elements = e;
	}
	
	public String[] getElements() {
		return elements;
	}
	public void setUnit(String u) {
		this.unit = u;
	}
	public String getUnit() {
		return unit;
	}
	public void setHTMLList(String[] h) {
		this.htmlList = h;
	}
	
	public String[] getHTMLList() {
		return htmlList;
	}
	
	public void setCommaList(String[] c) {
		this.commaList = c;
	}
	
	public String[] getCommaList() {
		return commaList;
	}
	
	public void setNumCities(int n) {
		this.numCities = n;
	}
	
	public int getNumCities() {
		return numCities;
	}
	
}