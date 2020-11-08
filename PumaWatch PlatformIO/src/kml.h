/*	KML exemple:
<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://www.opengis.net/kml/2.2">
  <Document>
    <name>KML Minimal</name>
    <open>1</open>
    <description>This is a test file for minimal kml file</description>
    <Style id="Flying">
      <LineStyle>
        <color>501400FF</color>
        <width>4</width>
      </LineStyle>
      <PolyStyle>
        <color>501400FF</color>
      </PolyStyle>
    </Style>
    <Style id="Running">
      <LineStyle>
        <color>5000FF14</color>
        <width>4</width>
      </LineStyle>
      <PolyStyle>
        <color>5000FF14</color>
      </PolyStyle>
    </Style>	
 <Folder>
      <name>Entrainement</name>
      <visibility>1</visibility>
      <description>Entrainement du jour en hikefly</description>
      <Placemark>
        <name>Absolute</name>
        <visibility>1</visibility>
        <styleUrl>#Flying</styleUrl>
        <LineString>
          <tessellate>1</tessellate>
          <altitudeMode>absolute</altitudeMode>
          <coordinates> 
			-112.265654928602,36.09447672602546,2357
            -112.2660384528238,36.09342608838671,2357
            -112.2668139013453,36.09251058776881,2260
            -112.2677826834445,36.09189827357996,2163
            -112.2688557510952,36.0913137941187,2063
            -112.2694810717219,36.0903677207521,2170
            -112.2695268555611,36.08932171487285,2375
            -112.2690144567276,36.08850916060472,2476
            -112.2681528815339,36.08753813597956,2270
            -112.2670588176031,36.08682685262568,2065
            -112.2657374587321,36.08646312301303,1860 
		  </coordinates>
        </LineString>
      </Placemark>
    </Folder>
  </Document>
</kml>
*/