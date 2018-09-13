<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.2.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="24FJ1024GB606PT-E">
<packages>
<package name="TQFP64_10X10MC">
<smd name="1" x="-5.6134" y="3.75000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="2" x="-5.6134" y="3.25000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="3" x="-5.6134" y="2.75000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="4" x="-5.6134" y="2.250009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="5" x="-5.6134" y="1.750009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="6" x="-5.6134" y="1.250009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="7" x="-5.6134" y="0.7500125" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="8" x="-5.6134" y="0.2499875" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="9" x="-5.6134" y="-0.2499875" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="10" x="-5.6134" y="-0.7500125" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="11" x="-5.6134" y="-1.250009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="12" x="-5.6134" y="-1.750009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="13" x="-5.6134" y="-2.250009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="14" x="-5.6134" y="-2.75000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="15" x="-5.6134" y="-3.25000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="16" x="-5.6134" y="-3.75000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="17" x="-3.75000625" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="18" x="-3.25000625" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="19" x="-2.75000625" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="20" x="-2.250009375" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="21" x="-1.750009375" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="22" x="-1.250009375" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="23" x="-0.7500125" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="24" x="-0.2499875" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="25" x="0.2499875" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="26" x="0.7500125" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="27" x="1.250009375" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="28" x="1.750009375" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="29" x="2.250009375" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="30" x="2.75000625" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="31" x="3.25000625" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="32" x="3.75000625" y="-5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="33" x="5.6134" y="-3.75000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="34" x="5.6134" y="-3.25000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="35" x="5.6134" y="-2.75000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="36" x="5.6134" y="-2.250009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="37" x="5.6134" y="-1.750009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="38" x="5.6134" y="-1.250009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="39" x="5.6134" y="-0.7500125" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="40" x="5.6134" y="-0.2499875" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="41" x="5.6134" y="0.2499875" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="42" x="5.6134" y="0.7500125" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="43" x="5.6134" y="1.250009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="44" x="5.6134" y="1.750009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="45" x="5.6134" y="2.250009375" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="46" x="5.6134" y="2.75000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="47" x="5.6134" y="3.25000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="48" x="5.6134" y="3.75000625" dx="0.2794" dy="1.4732" layer="1" rot="R270"/>
<smd name="49" x="3.75000625" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="50" x="3.25000625" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="51" x="2.75000625" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="52" x="2.250009375" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="53" x="1.750009375" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="54" x="1.250009375" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="55" x="0.7500125" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="56" x="0.2499875" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="57" x="-0.2499875" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="58" x="-0.7500125" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="59" x="-1.250009375" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="60" x="-1.750009375" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="61" x="-2.250009375" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="62" x="-2.75000625" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="63" x="-3.25000625" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<smd name="64" x="-3.75000625" y="5.6134" dx="0.2794" dy="1.4732" layer="1" rot="R180"/>
<wire x1="-4.2164" y1="5.1308" x2="-5.1308" y2="5.1308" width="0.1524" layer="51"/>
<wire x1="5.1308" y1="4.2164" x2="5.1308" y2="5.1308" width="0.1524" layer="51"/>
<wire x1="4.2164" y1="-5.1308" x2="5.1308" y2="-5.1308" width="0.1524" layer="51"/>
<wire x1="-5.1308" y1="-5.1308" x2="-4.2164" y2="-5.1308" width="0.1524" layer="51"/>
<wire x1="5.1308" y1="-5.1308" x2="5.1308" y2="-4.2164" width="0.1524" layer="51"/>
<wire x1="5.1308" y1="5.1308" x2="4.2164" y2="5.1308" width="0.1524" layer="51"/>
<wire x1="-5.1308" y1="5.1308" x2="-5.1308" y2="4.2164" width="0.1524" layer="51"/>
<wire x1="-5.1308" y1="-4.2164" x2="-5.1308" y2="-5.1308" width="0.1524" layer="51"/>
<wire x1="-6.858" y1="-0.5588" x2="-6.858" y2="-0.9398" width="0.1524" layer="51"/>
<wire x1="-6.858" y1="-0.9398" x2="-6.604" y2="-0.9398" width="0.1524" layer="51"/>
<wire x1="-6.604" y1="-0.9398" x2="-6.604" y2="-0.5588" width="0.1524" layer="51"/>
<wire x1="-6.604" y1="-0.5588" x2="-6.858" y2="-0.5588" width="0.1524" layer="51"/>
<wire x1="-2.4384" y1="-6.604" x2="-2.4384" y2="-6.858" width="0.1524" layer="51"/>
<wire x1="-2.4384" y1="-6.858" x2="-2.0574" y2="-6.858" width="0.1524" layer="51"/>
<wire x1="-2.0574" y1="-6.858" x2="-2.0574" y2="-6.604" width="0.1524" layer="51"/>
<wire x1="-2.0574" y1="-6.604" x2="-2.4384" y2="-6.604" width="0.1524" layer="51"/>
<wire x1="2.5654" y1="-6.604" x2="2.5654" y2="-6.858" width="0.1524" layer="51"/>
<wire x1="2.5654" y1="-6.858" x2="2.9464" y2="-6.858" width="0.1524" layer="51"/>
<wire x1="2.9464" y1="-6.858" x2="2.9464" y2="-6.604" width="0.1524" layer="51"/>
<wire x1="2.9464" y1="-6.604" x2="2.5654" y2="-6.604" width="0.1524" layer="51"/>
<wire x1="6.858" y1="-0.0508" x2="6.858" y2="-0.4318" width="0.1524" layer="51"/>
<wire x1="6.858" y1="-0.4318" x2="6.604" y2="-0.4318" width="0.1524" layer="51"/>
<wire x1="6.604" y1="-0.4318" x2="6.604" y2="-0.0508" width="0.1524" layer="51"/>
<wire x1="6.604" y1="-0.0508" x2="6.858" y2="-0.0508" width="0.1524" layer="51"/>
<wire x1="3.048" y1="6.604" x2="3.048" y2="6.858" width="0.1524" layer="51"/>
<wire x1="3.048" y1="6.858" x2="3.429" y2="6.858" width="0.1524" layer="51"/>
<wire x1="3.429" y1="6.858" x2="3.429" y2="6.604" width="0.1524" layer="51"/>
<wire x1="3.429" y1="6.604" x2="3.048" y2="6.604" width="0.1524" layer="51"/>
<wire x1="-1.9304" y1="6.604" x2="-1.9304" y2="6.858" width="0.1524" layer="51"/>
<wire x1="-1.9304" y1="6.858" x2="-1.5494" y2="6.858" width="0.1524" layer="51"/>
<wire x1="-1.5494" y1="6.858" x2="-1.5494" y2="6.604" width="0.1524" layer="51"/>
<wire x1="-1.5494" y1="6.604" x2="-1.9304" y2="6.604" width="0.1524" layer="51"/>
<text x="-7.5692" y="3.7338" size="1.27" layer="51" ratio="6" rot="SR0">*</text>
<wire x1="3.6068" y1="5.0038" x2="3.8862" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="3.8862" y1="5.0038" x2="3.8862" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="3.8862" y1="5.9944" x2="3.6068" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="3.6068" y1="5.9944" x2="3.6068" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="3.0988" y1="5.0038" x2="3.3782" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="3.3782" y1="5.0038" x2="3.3782" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="3.3782" y1="5.9944" x2="3.0988" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="3.0988" y1="5.9944" x2="3.0988" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="2.6162" y1="5.0038" x2="2.8956" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="2.8956" y1="5.0038" x2="2.8956" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="2.8956" y1="5.9944" x2="2.6162" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="2.6162" y1="5.9944" x2="2.6162" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="2.1082" y1="5.0038" x2="2.3876" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="2.3876" y1="5.0038" x2="2.3876" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="2.3876" y1="5.9944" x2="2.1082" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="2.1082" y1="5.9944" x2="2.1082" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="1.6002" y1="5.0038" x2="1.8796" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="1.8796" y1="5.0038" x2="1.8796" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="1.8796" y1="5.9944" x2="1.6002" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="1.6002" y1="5.9944" x2="1.6002" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="1.1176" y1="5.0038" x2="1.397" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="1.397" y1="5.0038" x2="1.397" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="1.397" y1="5.9944" x2="1.1176" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="1.1176" y1="5.9944" x2="1.1176" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="0.6096" y1="5.0038" x2="0.889" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="0.889" y1="5.0038" x2="0.889" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="0.889" y1="5.9944" x2="0.6096" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="0.6096" y1="5.9944" x2="0.6096" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="0.1016" y1="5.0038" x2="0.381" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="0.381" y1="5.0038" x2="0.381" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="0.381" y1="5.9944" x2="0.1016" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="0.1016" y1="5.9944" x2="0.1016" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-0.381" y1="5.0038" x2="-0.1016" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-0.1016" y1="5.0038" x2="-0.1016" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-0.1016" y1="5.9944" x2="-0.381" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-0.381" y1="5.9944" x2="-0.381" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-0.889" y1="5.0038" x2="-0.6096" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-0.6096" y1="5.0038" x2="-0.6096" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-0.6096" y1="5.9944" x2="-0.889" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-0.889" y1="5.9944" x2="-0.889" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-1.397" y1="5.0038" x2="-1.1176" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-1.1176" y1="5.0038" x2="-1.1176" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-1.1176" y1="5.9944" x2="-1.397" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-1.397" y1="5.9944" x2="-1.397" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-1.8796" y1="5.0038" x2="-1.6002" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-1.6002" y1="5.0038" x2="-1.6002" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-1.6002" y1="5.9944" x2="-1.8796" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-1.8796" y1="5.9944" x2="-1.8796" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-2.3876" y1="5.0038" x2="-2.1082" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-2.1082" y1="5.0038" x2="-2.1082" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-2.1082" y1="5.9944" x2="-2.3876" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-2.3876" y1="5.9944" x2="-2.3876" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-2.8956" y1="5.0038" x2="-2.6162" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-2.6162" y1="5.0038" x2="-2.6162" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-2.6162" y1="5.9944" x2="-2.8956" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-2.8956" y1="5.9944" x2="-2.8956" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-3.3782" y1="5.0038" x2="-3.0988" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-3.0988" y1="5.0038" x2="-3.0988" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-3.0988" y1="5.9944" x2="-3.3782" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-3.3782" y1="5.9944" x2="-3.3782" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-3.8862" y1="5.0038" x2="-3.7338" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-3.7338" y1="5.0038" x2="-3.6068" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-3.6068" y1="5.0038" x2="-3.6068" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-3.6068" y1="5.9944" x2="-3.8862" y2="5.9944" width="0.1524" layer="25"/>
<wire x1="-3.8862" y1="5.9944" x2="-3.8862" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="3.6068" x2="-5.0038" y2="3.7338" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="3.7338" x2="-5.0038" y2="3.8862" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="3.8862" x2="-5.9944" y2="3.8862" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="3.8862" x2="-5.9944" y2="3.6068" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="3.6068" x2="-5.0038" y2="3.6068" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="3.0988" x2="-5.0038" y2="3.3782" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="3.3782" x2="-5.9944" y2="3.3782" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="3.3782" x2="-5.9944" y2="3.0988" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="3.0988" x2="-5.0038" y2="3.0988" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="2.6162" x2="-5.0038" y2="2.8956" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="2.8956" x2="-5.9944" y2="2.8956" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="2.8956" x2="-5.9944" y2="2.6162" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="2.6162" x2="-5.0038" y2="2.6162" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="2.1082" x2="-5.0038" y2="2.3876" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="2.3876" x2="-5.9944" y2="2.3876" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="2.3876" x2="-5.9944" y2="2.1082" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="2.1082" x2="-5.0038" y2="2.1082" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="1.6002" x2="-5.0038" y2="1.8796" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="1.8796" x2="-5.9944" y2="1.8796" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="1.8796" x2="-5.9944" y2="1.6002" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="1.6002" x2="-5.0038" y2="1.6002" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="1.1176" x2="-5.0038" y2="1.397" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="1.397" x2="-5.9944" y2="1.397" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="1.397" x2="-5.9944" y2="1.1176" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="1.1176" x2="-5.0038" y2="1.1176" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="0.6096" x2="-5.0038" y2="0.889" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="0.889" x2="-5.9944" y2="0.889" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="0.889" x2="-5.9944" y2="0.6096" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="0.6096" x2="-5.0038" y2="0.6096" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="0.1016" x2="-5.0038" y2="0.381" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="0.381" x2="-5.9944" y2="0.381" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="0.381" x2="-5.9944" y2="0.1016" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="0.1016" x2="-5.0038" y2="0.1016" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-0.381" x2="-5.0038" y2="-0.1016" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-0.1016" x2="-5.9944" y2="-0.1016" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-0.1016" x2="-5.9944" y2="-0.381" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-0.381" x2="-5.0038" y2="-0.381" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-0.889" x2="-5.0038" y2="-0.6096" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-0.6096" x2="-5.9944" y2="-0.6096" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-0.6096" x2="-5.9944" y2="-0.889" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-0.889" x2="-5.0038" y2="-0.889" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-1.397" x2="-5.0038" y2="-1.1176" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-1.1176" x2="-5.9944" y2="-1.1176" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-1.1176" x2="-5.9944" y2="-1.397" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-1.397" x2="-5.0038" y2="-1.397" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-1.8796" x2="-5.0038" y2="-1.6002" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-1.6002" x2="-5.9944" y2="-1.6002" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-1.6002" x2="-5.9944" y2="-1.8796" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-1.8796" x2="-5.0038" y2="-1.8796" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-2.3876" x2="-5.0038" y2="-2.1082" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-2.1082" x2="-5.9944" y2="-2.1082" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-2.1082" x2="-5.9944" y2="-2.3876" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-2.3876" x2="-5.0038" y2="-2.3876" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-2.8956" x2="-5.0038" y2="-2.6162" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-2.6162" x2="-5.9944" y2="-2.6162" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-2.6162" x2="-5.9944" y2="-2.8956" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-2.8956" x2="-5.0038" y2="-2.8956" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-3.3782" x2="-5.0038" y2="-3.0988" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-3.0988" x2="-5.9944" y2="-3.0988" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-3.0988" x2="-5.9944" y2="-3.3782" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-3.3782" x2="-5.0038" y2="-3.3782" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-3.8862" x2="-5.0038" y2="-3.6068" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-3.6068" x2="-5.9944" y2="-3.6068" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-3.6068" x2="-5.9944" y2="-3.8862" width="0.1524" layer="25"/>
<wire x1="-5.9944" y1="-3.8862" x2="-5.0038" y2="-3.8862" width="0.1524" layer="25"/>
<wire x1="-3.6068" y1="-5.0038" x2="-3.8862" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-3.8862" y1="-5.0038" x2="-3.8862" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-3.8862" y1="-5.9944" x2="-3.6068" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-3.6068" y1="-5.9944" x2="-3.6068" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-3.0988" y1="-5.0038" x2="-3.3782" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-3.3782" y1="-5.0038" x2="-3.3782" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-3.3782" y1="-5.9944" x2="-3.0988" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-3.0988" y1="-5.9944" x2="-3.0988" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-2.6162" y1="-5.0038" x2="-2.8956" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-2.8956" y1="-5.0038" x2="-2.8956" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-2.8956" y1="-5.9944" x2="-2.6162" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-2.6162" y1="-5.9944" x2="-2.6162" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-2.1082" y1="-5.0038" x2="-2.3876" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-2.3876" y1="-5.0038" x2="-2.3876" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-2.3876" y1="-5.9944" x2="-2.1082" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-2.1082" y1="-5.9944" x2="-2.1082" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-1.6002" y1="-5.0038" x2="-1.8796" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-1.8796" y1="-5.0038" x2="-1.8796" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-1.8796" y1="-5.9944" x2="-1.6002" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-1.6002" y1="-5.9944" x2="-1.6002" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-1.1176" y1="-5.0038" x2="-1.397" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-1.397" y1="-5.0038" x2="-1.397" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-1.397" y1="-5.9944" x2="-1.1176" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-1.1176" y1="-5.9944" x2="-1.1176" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-0.6096" y1="-5.0038" x2="-0.889" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-0.889" y1="-5.0038" x2="-0.889" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-0.889" y1="-5.9944" x2="-0.6096" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-0.6096" y1="-5.9944" x2="-0.6096" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-0.1016" y1="-5.0038" x2="-0.381" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="-0.381" y1="-5.0038" x2="-0.381" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-0.381" y1="-5.9944" x2="-0.1016" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="-0.1016" y1="-5.9944" x2="-0.1016" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="0.381" y1="-5.0038" x2="0.1016" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="0.1016" y1="-5.0038" x2="0.1016" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="0.1016" y1="-5.9944" x2="0.381" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="0.381" y1="-5.9944" x2="0.381" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="0.889" y1="-5.0038" x2="0.6096" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="0.6096" y1="-5.0038" x2="0.6096" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="0.6096" y1="-5.9944" x2="0.889" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="0.889" y1="-5.9944" x2="0.889" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="1.397" y1="-5.0038" x2="1.1176" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="1.1176" y1="-5.0038" x2="1.1176" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="1.1176" y1="-5.9944" x2="1.397" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="1.397" y1="-5.9944" x2="1.397" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="1.8796" y1="-5.0038" x2="1.6002" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="1.6002" y1="-5.0038" x2="1.6002" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="1.6002" y1="-5.9944" x2="1.8796" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="1.8796" y1="-5.9944" x2="1.8796" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="2.3876" y1="-5.0038" x2="2.1082" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="2.1082" y1="-5.0038" x2="2.1082" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="2.1082" y1="-5.9944" x2="2.3876" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="2.3876" y1="-5.9944" x2="2.3876" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="2.8956" y1="-5.0038" x2="2.6162" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="2.6162" y1="-5.0038" x2="2.6162" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="2.6162" y1="-5.9944" x2="2.8956" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="2.8956" y1="-5.9944" x2="2.8956" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="3.3782" y1="-5.0038" x2="3.0988" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="3.0988" y1="-5.0038" x2="3.0988" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="3.0988" y1="-5.9944" x2="3.3782" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="3.3782" y1="-5.9944" x2="3.3782" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="3.8862" y1="-5.0038" x2="3.6068" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="3.6068" y1="-5.0038" x2="3.6068" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="3.6068" y1="-5.9944" x2="3.8862" y2="-5.9944" width="0.1524" layer="25"/>
<wire x1="3.8862" y1="-5.9944" x2="3.8862" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-3.6068" x2="5.0038" y2="-3.8862" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-3.8862" x2="5.9944" y2="-3.8862" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-3.8862" x2="5.9944" y2="-3.6068" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-3.6068" x2="5.0038" y2="-3.6068" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-3.0988" x2="5.0038" y2="-3.3782" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-3.3782" x2="5.9944" y2="-3.3782" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-3.3782" x2="5.9944" y2="-3.0988" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-3.0988" x2="5.0038" y2="-3.0988" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-2.6162" x2="5.0038" y2="-2.8956" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-2.8956" x2="5.9944" y2="-2.8956" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-2.8956" x2="5.9944" y2="-2.6162" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-2.6162" x2="5.0038" y2="-2.6162" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-2.1082" x2="5.0038" y2="-2.3876" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-2.3876" x2="5.9944" y2="-2.3876" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-2.3876" x2="5.9944" y2="-2.1082" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-2.1082" x2="5.0038" y2="-2.1082" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-1.6002" x2="5.0038" y2="-1.8796" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-1.8796" x2="5.9944" y2="-1.8796" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-1.8796" x2="5.9944" y2="-1.6002" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-1.6002" x2="5.0038" y2="-1.6002" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-1.1176" x2="5.0038" y2="-1.397" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-1.397" x2="5.9944" y2="-1.397" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-1.397" x2="5.9944" y2="-1.1176" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-1.1176" x2="5.0038" y2="-1.1176" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-0.6096" x2="5.0038" y2="-0.889" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-0.889" x2="5.9944" y2="-0.889" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-0.889" x2="5.9944" y2="-0.6096" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-0.6096" x2="5.0038" y2="-0.6096" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-0.1016" x2="5.0038" y2="-0.381" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-0.381" x2="5.9944" y2="-0.381" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-0.381" x2="5.9944" y2="-0.1016" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="-0.1016" x2="5.0038" y2="-0.1016" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="0.381" x2="5.0038" y2="0.1016" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="0.1016" x2="5.9944" y2="0.1016" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="0.1016" x2="5.9944" y2="0.381" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="0.381" x2="5.0038" y2="0.381" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="0.889" x2="5.0038" y2="0.6096" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="0.6096" x2="5.9944" y2="0.6096" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="0.6096" x2="5.9944" y2="0.889" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="0.889" x2="5.0038" y2="0.889" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="1.397" x2="5.0038" y2="1.1176" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="1.1176" x2="5.9944" y2="1.1176" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="1.1176" x2="5.9944" y2="1.397" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="1.397" x2="5.0038" y2="1.397" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="1.8796" x2="5.0038" y2="1.6002" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="1.6002" x2="5.9944" y2="1.6002" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="1.6002" x2="5.9944" y2="1.8796" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="1.8796" x2="5.0038" y2="1.8796" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="2.3876" x2="5.0038" y2="2.1082" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="2.1082" x2="5.9944" y2="2.1082" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="2.1082" x2="5.9944" y2="2.3876" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="2.3876" x2="5.0038" y2="2.3876" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="2.8956" x2="5.0038" y2="2.6162" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="2.6162" x2="5.9944" y2="2.6162" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="2.6162" x2="5.9944" y2="2.8956" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="2.8956" x2="5.0038" y2="2.8956" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="3.3782" x2="5.0038" y2="3.0988" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="3.0988" x2="5.9944" y2="3.0988" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="3.0988" x2="5.9944" y2="3.3782" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="3.3782" x2="5.0038" y2="3.3782" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="3.8862" x2="5.0038" y2="3.6068" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="3.6068" x2="5.9944" y2="3.6068" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="3.6068" x2="5.9944" y2="3.8862" width="0.1524" layer="25"/>
<wire x1="5.9944" y1="3.8862" x2="5.0038" y2="3.8862" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="3.7338" x2="-3.7338" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="-5.0038" x2="5.0038" y2="-5.0038" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="-5.0038" x2="5.0038" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="5.0038" y1="5.0038" x2="-5.0038" y2="5.0038" width="0.1524" layer="25"/>
<wire x1="-5.0038" y1="5.0038" x2="-5.0038" y2="-5.0038" width="0.1524" layer="25"/>
<text x="-5.207" y="3.3528" size="1.27" layer="25" ratio="6" rot="SR0">*</text>
<text x="-2.8702" y="-0.635" size="1.27" layer="25" ratio="6" rot="SR0">&gt;NAME</text>
<text x="-3.4544" y="-0.635" size="1.27" layer="27" ratio="6" rot="SR0">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="PIC24FJXXXGB606-X_PT">
<pin name="IC4/CTED4/PMD5/RE5" x="0" y="0"/>
<pin name="SCL3/IC5/PMD6/RE6" x="0" y="-2.54"/>
<pin name="SDA3/IC6/PMD7/RE7" x="0" y="-5.08"/>
<pin name="C1IND/RP21/ICM1/OCM1A/PMA5/RG6" x="0" y="-7.62"/>
<pin name="C1INC/RP26/OCM1B/PMA4/RG7" x="0" y="-10.16"/>
<pin name="C2IND/RP19/ICM2/OCM2A/PMA3/RG8" x="0" y="-12.7"/>
<pin name="*MCLR" x="0" y="-15.24" direction="pas"/>
<pin name="C1INC/C2INC/C3INC/RP27/OCM2B/PMA2/PMALU/RG9" x="0" y="-17.78"/>
<pin name="VSS_2" x="0" y="-20.32" direction="pwr"/>
<pin name="VDD_2" x="0" y="-22.86" direction="pwr"/>
<pin name="PGEC3/AN5/C1INA/RP18/ICM3/OCM3A/RB5" x="0" y="-25.4"/>
<pin name="PGED3/AN4/C1INB/RP28/*USBOEN/OCM3B/RB4" x="0" y="-27.94"/>
<pin name="AN3/C2INA/RB3" x="0" y="-30.48"/>
<pin name="AN2/CTCMP/C2INB/RP13/CTED13/RB2" x="0" y="-33.02"/>
<pin name="PGEC1/ALTCVREF-/ALTVREF-/AN1/RP1/CTED12/RB1" x="0" y="-35.56"/>
<pin name="PGED1/ALTCVREF+/ALTVREF+/AN0/RP0/PMA6/RB0" x="0" y="-38.1"/>
<pin name="PGEC2/AN6/RP6/RB6" x="0" y="-40.64"/>
<pin name="PGED2/AN7/RP7/U6TX/RB7" x="0" y="-43.18"/>
<pin name="AVDD" x="0" y="-45.72" direction="pwr"/>
<pin name="AVSS" x="0" y="-48.26" direction="pwr"/>
<pin name="AN8/RP8/PWRGT/RB8" x="0" y="-50.8"/>
<pin name="AN9/*TMPR/RP9/T1CK/PMA7/RB9" x="0" y="-53.34"/>
<pin name="TMS/CVREF/AN10/PMA13/RB10" x="0" y="-55.88"/>
<pin name="TDO/AN11/REFI/PMA12/RB11" x="0" y="-58.42"/>
<pin name="VSS_3" x="0" y="-60.96" direction="pwr"/>
<pin name="VDD_3" x="0" y="-63.5" direction="pwr"/>
<pin name="TCK/AN12/U6RX/CTED2/PMA11/RB12" x="0" y="-66.04"/>
<pin name="TDI/AN13/CTED1/PMA10/RB13" x="0" y="-68.58"/>
<pin name="AN14/RP14/CTED5/CTPLS/PMA1/PMALH/RB14" x="0" y="-71.12"/>
<pin name="AN15/RP29/CTED6/PMA0/PMALL/RB15" x="0" y="-73.66"/>
<pin name="RP10/SDA2/PMA9/RF4" x="0" y="-76.2"/>
<pin name="RP17/SCL2/PMA8/RF5" x="0" y="-78.74"/>
<pin name="RP16/USBID/RF3" x="208.28" y="-78.74" rot="R180"/>
<pin name="VBUS/RF7" x="208.28" y="-76.2" rot="R180"/>
<pin name="VUSB3V3" x="208.28" y="-73.66" direction="pwr" rot="R180"/>
<pin name="D-/RG3" x="208.28" y="-71.12" rot="R180"/>
<pin name="D+/RG2" x="208.28" y="-68.58" rot="R180"/>
<pin name="VDD" x="208.28" y="-66.04" direction="pwr" rot="R180"/>
<pin name="OSCI/CLKI/RC12" x="208.28" y="-63.5" rot="R180"/>
<pin name="OSCO/CLKO/RC15" x="208.28" y="-60.96" rot="R180"/>
<pin name="VSS" x="208.28" y="-58.42" direction="pwr" rot="R180"/>
<pin name="CLC4OUT/RP2/*U6RTS/U6BCLK/ICM5/RD8" x="208.28" y="-55.88" rot="R180"/>
<pin name="RP4/SDA1/PMACK2/RD9" x="208.28" y="-53.34" rot="R180"/>
<pin name="RP3/SCL1/PMA15/PMCS2/RD10" x="208.28" y="-50.8" rot="R180"/>
<pin name="RP12/PMA14/PMCS1/RD11" x="208.28" y="-48.26" rot="R180"/>
<pin name="CLC3OUT/RP11/*U6CTS/ICM6/INT0/RD0" x="208.28" y="-45.72" rot="R180"/>
<pin name="SOSCI/C3IND/RC13" x="208.28" y="-43.18" rot="R180"/>
<pin name="SOSCO/C3INC/RPI37/PWRLCLK/RC14" x="208.28" y="-40.64" rot="R180"/>
<pin name="RP24/U5TX/ICM4/RD1" x="208.28" y="-38.1" rot="R180"/>
<pin name="RP23/PMACK1/RD2" x="208.28" y="-35.56" rot="R180"/>
<pin name="RP22/ICM7/PMBE0/RD3" x="208.28" y="-33.02" rot="R180"/>
<pin name="RP25/PMWR/PMENB/RD4" x="208.28" y="-30.48" rot="R180"/>
<pin name="RP20/PMRD/*PMWR/RD5" x="208.28" y="-27.94" rot="R180"/>
<pin name="C3INB/U5RX/OC4/RD6" x="208.28" y="-25.4" rot="R180"/>
<pin name="C3INA/*U5RTS/U5BCLK/OC5/RD7" x="208.28" y="-22.86" rot="R180"/>
<pin name="VCAP" x="208.28" y="-20.32" direction="pwr" rot="R180"/>
<pin name="NC" x="208.28" y="-17.78" direction="nc" rot="R180"/>
<pin name="*U5CTS/OC6/RF0" x="208.28" y="-15.24" rot="R180"/>
<pin name="RF1" x="208.28" y="-12.7" direction="pas" rot="R180"/>
<pin name="PMD0/RE0" x="208.28" y="-10.16" rot="R180"/>
<pin name="PMD1/RE1" x="208.28" y="-7.62" rot="R180"/>
<pin name="PMD2/RE2" x="208.28" y="-5.08" rot="R180"/>
<pin name="CTED9/PMD3/RE3" x="208.28" y="-2.54" rot="R180"/>
<pin name="HLVDIN/CTED8/PMD4/RE4" x="208.28" y="0" rot="R180"/>
<wire x1="7.62" y1="5.08" x2="7.62" y2="-83.82" width="0.1524" layer="94"/>
<wire x1="7.62" y1="-83.82" x2="200.66" y2="-83.82" width="0.1524" layer="94"/>
<wire x1="200.66" y1="-83.82" x2="200.66" y2="5.08" width="0.1524" layer="94"/>
<wire x1="200.66" y1="5.08" x2="7.62" y2="5.08" width="0.1524" layer="94"/>
<text x="99.4156" y="9.1186" size="2.0828" layer="95" ratio="6" rot="SR0">&gt;NAME</text>
<text x="98.4758" y="6.5786" size="2.0828" layer="96" ratio="6" rot="SR0">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="PIC24FJXXXGB606-X_PT" prefix="U">
<gates>
<gate name="A" symbol="PIC24FJXXXGB606-X_PT" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TQFP64_10X10MC">
<connects>
<connect gate="A" pin="*MCLR" pad="7"/>
<connect gate="A" pin="*U5CTS/OC6/RF0" pad="58"/>
<connect gate="A" pin="AN14/RP14/CTED5/CTPLS/PMA1/PMALH/RB14" pad="29"/>
<connect gate="A" pin="AN15/RP29/CTED6/PMA0/PMALL/RB15" pad="30"/>
<connect gate="A" pin="AN2/CTCMP/C2INB/RP13/CTED13/RB2" pad="14"/>
<connect gate="A" pin="AN3/C2INA/RB3" pad="13"/>
<connect gate="A" pin="AN8/RP8/PWRGT/RB8" pad="21"/>
<connect gate="A" pin="AN9/*TMPR/RP9/T1CK/PMA7/RB9" pad="22"/>
<connect gate="A" pin="AVDD" pad="19"/>
<connect gate="A" pin="AVSS" pad="20"/>
<connect gate="A" pin="C1INC/C2INC/C3INC/RP27/OCM2B/PMA2/PMALU/RG9" pad="8"/>
<connect gate="A" pin="C1INC/RP26/OCM1B/PMA4/RG7" pad="5"/>
<connect gate="A" pin="C1IND/RP21/ICM1/OCM1A/PMA5/RG6" pad="4"/>
<connect gate="A" pin="C2IND/RP19/ICM2/OCM2A/PMA3/RG8" pad="6"/>
<connect gate="A" pin="C3INA/*U5RTS/U5BCLK/OC5/RD7" pad="55"/>
<connect gate="A" pin="C3INB/U5RX/OC4/RD6" pad="54"/>
<connect gate="A" pin="CLC3OUT/RP11/*U6CTS/ICM6/INT0/RD0" pad="46"/>
<connect gate="A" pin="CLC4OUT/RP2/*U6RTS/U6BCLK/ICM5/RD8" pad="42"/>
<connect gate="A" pin="CTED9/PMD3/RE3" pad="63"/>
<connect gate="A" pin="D+/RG2" pad="37"/>
<connect gate="A" pin="D-/RG3" pad="36"/>
<connect gate="A" pin="HLVDIN/CTED8/PMD4/RE4" pad="64"/>
<connect gate="A" pin="IC4/CTED4/PMD5/RE5" pad="1"/>
<connect gate="A" pin="NC" pad="57"/>
<connect gate="A" pin="OSCI/CLKI/RC12" pad="39"/>
<connect gate="A" pin="OSCO/CLKO/RC15" pad="40"/>
<connect gate="A" pin="PGEC1/ALTCVREF-/ALTVREF-/AN1/RP1/CTED12/RB1" pad="15"/>
<connect gate="A" pin="PGEC2/AN6/RP6/RB6" pad="17"/>
<connect gate="A" pin="PGEC3/AN5/C1INA/RP18/ICM3/OCM3A/RB5" pad="11"/>
<connect gate="A" pin="PGED1/ALTCVREF+/ALTVREF+/AN0/RP0/PMA6/RB0" pad="16"/>
<connect gate="A" pin="PGED2/AN7/RP7/U6TX/RB7" pad="18"/>
<connect gate="A" pin="PGED3/AN4/C1INB/RP28/*USBOEN/OCM3B/RB4" pad="12"/>
<connect gate="A" pin="PMD0/RE0" pad="60"/>
<connect gate="A" pin="PMD1/RE1" pad="61"/>
<connect gate="A" pin="PMD2/RE2" pad="62"/>
<connect gate="A" pin="RF1" pad="59"/>
<connect gate="A" pin="RP10/SDA2/PMA9/RF4" pad="31"/>
<connect gate="A" pin="RP12/PMA14/PMCS1/RD11" pad="45"/>
<connect gate="A" pin="RP16/USBID/RF3" pad="33"/>
<connect gate="A" pin="RP17/SCL2/PMA8/RF5" pad="32"/>
<connect gate="A" pin="RP20/PMRD/*PMWR/RD5" pad="53"/>
<connect gate="A" pin="RP22/ICM7/PMBE0/RD3" pad="51"/>
<connect gate="A" pin="RP23/PMACK1/RD2" pad="50"/>
<connect gate="A" pin="RP24/U5TX/ICM4/RD1" pad="49"/>
<connect gate="A" pin="RP25/PMWR/PMENB/RD4" pad="52"/>
<connect gate="A" pin="RP3/SCL1/PMA15/PMCS2/RD10" pad="44"/>
<connect gate="A" pin="RP4/SDA1/PMACK2/RD9" pad="43"/>
<connect gate="A" pin="SCL3/IC5/PMD6/RE6" pad="2"/>
<connect gate="A" pin="SDA3/IC6/PMD7/RE7" pad="3"/>
<connect gate="A" pin="SOSCI/C3IND/RC13" pad="47"/>
<connect gate="A" pin="SOSCO/C3INC/RPI37/PWRLCLK/RC14" pad="48"/>
<connect gate="A" pin="TCK/AN12/U6RX/CTED2/PMA11/RB12" pad="27"/>
<connect gate="A" pin="TDI/AN13/CTED1/PMA10/RB13" pad="28"/>
<connect gate="A" pin="TDO/AN11/REFI/PMA12/RB11" pad="24"/>
<connect gate="A" pin="TMS/CVREF/AN10/PMA13/RB10" pad="23"/>
<connect gate="A" pin="VBUS/RF7" pad="34"/>
<connect gate="A" pin="VCAP" pad="56"/>
<connect gate="A" pin="VDD" pad="38"/>
<connect gate="A" pin="VDD_2" pad="10"/>
<connect gate="A" pin="VDD_3" pad="26"/>
<connect gate="A" pin="VSS" pad="41"/>
<connect gate="A" pin="VSS_2" pad="9"/>
<connect gate="A" pin="VSS_3" pad="25"/>
<connect gate="A" pin="VUSB3V3" pad="35"/>
</connects>
<technologies>
<technology name="">
<attribute name="MANUFACTURER_PART_NUMBER" value="pic24fjxxxgb606-x_pt" constant="no"/>
<attribute name="VENDOR" value="Microchip" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U1" library="24FJ1024GB606PT-E" deviceset="PIC24FJXXXGB606-X_PT" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U1" gate="A" x="-15.24" y="83.82"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
