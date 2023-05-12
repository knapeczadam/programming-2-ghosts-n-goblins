/* 
 * https://www.retrogames.cc/arcade-games/ghostsn-goblins-us.html
 * simulate the play button click in order to take screenshots
 */

const timer = ms => new Promise(res => setTimeout(res, ms))

async function load ($) { 
  for (var i = 0; i < 1000; i++) {
    $("body > div > div.ejs--1acedc5ed6816abe96dd27d910fd74 > button:nth-child(2)").click();
    	await timer(500);
	$("body > div > div.ejs--1acedc5ed6816abe96dd27d910fd74 > button:nth-child(2)").click();
	await timer(1);
  }
}
load($);
