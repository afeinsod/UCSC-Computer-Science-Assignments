//Alix Feinsod
//CruzID: afeinsod
//Class: CMPS 12B
// dllistTest.java
// Unit tests for dllist for Assignment 2

import org.junit.*;
import static org.junit.Assert.assertEquals;
import java.util.NoSuchElementException;

public class dllistTest {

    @Test
    public void startsEmptyTest() {
        dllist lst = new dllist();
        assertEquals(true, lst.isEmpty());
    }

	@Test
    public void notEmptyTest() {
        dllist lst = new dllist();
	lst.insert("test", dllist.position.LAST);
        assertEquals(false, lst.isEmpty());
    }

	@Test
    public void insertLastGetItemTest() {
        dllist lst = new dllist();
	lst.insert("test", dllist.position.LAST);
        assertEquals("test", lst.getItem());
    }

	@Test
    public void insertLastGetItemSecondTest() {
        dllist lst = new dllist();
	lst.insert("test", dllist.position.LAST);
	lst.insert("test2", dllist.position.LAST);
        assertEquals("test2", lst.getItem());
    }

	@Test
    public void insertFirstGetItemTest() {
        dllist lst = new dllist();
	lst.insert("test", dllist.position.FIRST);
        assertEquals("test", lst.getItem());
    }

	@Test
    public void insertFirstGetItemSecondTest() {
        dllist lst = new dllist();
	lst.insert("test", dllist.position.FIRST);
	lst.insert("test2", dllist.position.FIRST);
        assertEquals("test2", lst.getItem());
    }

	@Test
    public void setPositionTest() {
        dllist lst = new dllist();
	lst.insert("test", dllist.position.LAST);
	lst.insert("test2", dllist.position.LAST);
	lst.setPosition(dllist.position.FIRST);
        assertEquals("test", lst.getItem());
    }

	@Test
    public void setPositionSecondTest() {
        dllist lst = new dllist();
	lst.insert("test", dllist.position.FIRST);
	lst.insert("test2", dllist.position.FIRST);
	lst.setPosition(dllist.position.LAST);
	assertEquals("test", lst.getItem());
    }

	@Test
    public void insertPreviousTest() {
        dllist lst = new dllist();
	lst.insert("A", dllist.position.LAST);
	lst.insert("B", dllist.position.LAST);
	lst.insert("C", dllist.position.LAST);
	lst.insert("D", dllist.position.PREVIOUS);
	lst.setPosition(dllist.position.LAST);
	assertEquals("C", lst.getItem());
    }
	@Test
	public void insertFollowingTest() {
        dllist lst = new dllist();
	lst.insert("A", dllist.position.FIRST);
	lst.insert("B", dllist.position.FIRST);
	lst.insert("C", dllist.position.FIRST);
	lst.insert("D", dllist.position.FOLLOWING);
	lst.setPosition(dllist.position.FIRST);
	assertEquals("C", lst.getItem());
    }
	@Test
	public void insertRandomTest() {
        dllist lst = new dllist();
	lst.insert("A", dllist.position.FIRST);
	lst.insert("B", dllist.position.LAST);
	lst.insert("C", dllist.position.PREVIOUS);
	lst.insert("D", dllist.position.FOLLOWING);
	lst.insert("E", dllist.position.FOLLOWING);
	assertEquals("E", lst.getItem());
	lst.setPosition(dllist.position.FIRST);
	assertEquals("A", lst.getItem());
	lst.setPosition(dllist.position.FOLLOWING);
	assertEquals("C", lst.getItem());
	lst.setPosition(dllist.position.FOLLOWING);
	assertEquals("D", lst.getItem());
	lst.setPosition(dllist.position.LAST);
	assertEquals("B", lst.getItem());
    }

	@Test
	public void getPositionTest() {
        dllist lst = new dllist();
	lst.insert("A", dllist.position.FIRST);
	lst.insert("B", dllist.position.LAST);
	lst.insert("C", dllist.position.PREVIOUS);
	lst.insert("D", dllist.position.FOLLOWING);
	lst.insert("E", dllist.position.FOLLOWING);
	assertEquals(3, lst.getPosition());
	lst.setPosition(dllist.position.FIRST);
	assertEquals(0, lst.getPosition());
	lst.setPosition(dllist.position.FOLLOWING);
	assertEquals(1, lst.getPosition());
	lst.setPosition(dllist.position.FOLLOWING);
	assertEquals(2, lst.getPosition());
	lst.setPosition(dllist.position.LAST);
	assertEquals(4, lst.getPosition());
    }

	@Test
	public void deleteTest() {
        dllist lst = new dllist();
	lst.insert("A", dllist.position.LAST);
	lst.insert("B", dllist.position.LAST);
	lst.insert("C", dllist.position.LAST);
	lst.insert("D", dllist.position.LAST);
	lst.insert("E", dllist.position.LAST);
	lst.delete();
	assertEquals(3, lst.getPosition());
	lst.setPosition(dllist.position.FIRST);
	assertEquals(0, lst.getPosition());
	assertEquals("A", lst.getItem());
	lst.delete();
	assertEquals(0, lst.getPosition());
	assertEquals("B", lst.getItem());
	lst.delete();
	assertEquals(0, lst.getPosition());
	assertEquals("C", lst.getItem());
	lst.delete();
	assertEquals(0, lst.getPosition());
	assertEquals("D", lst.getItem());
	lst.delete();
	assertEquals(true, lst.isEmpty());
    }

	@Test(expected=NoSuchElementException.class)
    public void emptyGetItemTest() {
        dllist lst = new dllist();
	lst.getItem();
    }

	@Test(expected=NoSuchElementException.class)
    public void emptyGetPositionTest() {
        dllist lst = new dllist();
	lst.getPosition();
    }

	@Test(expected=IllegalArgumentException.class)
    public void insertPreviousAtFirstTest() {
        dllist lst = new dllist();
	lst.insert("test", dllist.position.PREVIOUS);
    }

	@Test(expected=IllegalArgumentException.class)
    public void insertFollowingAtLastTest() {
        dllist lst = new dllist();
	lst.insert("test", dllist.position.FOLLOWING);
    }




}
