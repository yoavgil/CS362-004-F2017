/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
	   UrlValidator val = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   for (int scheme = 0; scheme < schemeArray.length; scheme++) {
		   for (int authority = 0; authority < authorityArray.length; authority++) {
			   for (int path = 0; path < pathArray.length; path++) {
				   for (int query = 0; query < queryArray.length; query++) {
					   for (int fragment = 0; fragment < fragmentArray.length; fragment++) {
						   
						   String url = schemeArray[scheme].item + authorityArray[authority].item +
								        pathArray[path].item + queryArray[query].item + fragmentArray[fragment].item;
						   
						   boolean expected = schemeArray[scheme].valid && authorityArray[authority].valid &&
							        pathArray[path].valid && queryArray[query].valid && fragmentArray[fragment].valid;
						   
						   boolean result = val.isValid(url);
						   
						   /*
						    * The "assertEquals" statement causes the test to stop after the first failure.
						    * Instead, use the "if" statement to print all failing tests to the console.
						    */
						   
						   //if (expected != result) System.out.println(url);
						   assertEquals(url, expected, result);
					   }
				   }
			   }
		   }
		   
	   }	   
   }
   
   ResultPair[] schemeArray = {new ResultPair("http://", true),
		                  new ResultPair("", true),
		                  new ResultPair("ftp://", true),
		                  new ResultPair("://", false),
		                  new ResultPair("http", false)
   };
		   
   ResultPair[] authorityArray = {new ResultPair("www.google.com", true),
		                     new ResultPair("wikipedia.org", true),
		                     new ResultPair("google.ca", true),
		                     new ResultPair("google.com:1", true),
		                     new ResultPair("", false),
		                     new ResultPair(".", false)
   };

	ResultPair[] pathArray = {new ResultPair("/path", true),
			             new ResultPair("", true)
	};
	
	ResultPair[] queryArray = {new ResultPair("?query", true),
			              new ResultPair("", true)
			
	};
	
	ResultPair[] fragmentArray = {new ResultPair("#fragment", true),
			                 new ResultPair("", true)
			
	};
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
