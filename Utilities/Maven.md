# Maven

## Apache Maven helps to manage

1. Builds
2. Documentation
3. Reporing
4. SCMs
5. Releases
6. Distribution

## Maven Repository

* Local Repository : Stored at local computer in %USER_HOME%/.m2
    Change the local repository directory : 

    This is the original code of the setting.xml located at MAVEN_HOME/conf/settings.xml
```xml
        ...  
<settings xmlns="http://maven.apache.org/SETTINGS/1.0.0"   
   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"   
   xsi:schemaLocation="http://maven.apache.org/SETTINGS/1.0.0 http://maven.apache.org/xsd/settings-1.0.0.xsd">  
  <!-- localRepository  
   | The path to the local repository maven will use to store artifacts.  
   |  
   | Default: ${user.home}/.m2/repository  
  <localRepository>/path/to/local/repo</localRepository>  
  -->  
  
...  
</settings>  

```

This is the changed code to change the location of the local repository to e:/mavenlocalrepository

```xml

    <settings xmlns="http://maven.apache.org/SETTINGS/1.0.0"   
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"   
    xsi:schemaLocation="http://maven.apache.org/SETTINGS/1.0.0 http://maven.apache.org/xsd/settings-1.0.0.xsd">  
    <localRepository>e:/mavenlocalrepository</localRepository>  
    
    ...  
    </settings> 
```

* Central Repository : The path of central repository is: [Central Repository](http://repo1.maven.org/maven2/). Libraries that are stored on the Central repository can be serarched at [Maven Repository](http://search.maven.org/#browse).

* Remote Repository : Some libraries might be missing from the central repository. These repositories need to be added to the pom.xml

Example : Adding JUnit to the project :

```xml

<project xmlns="http://maven.apache.org/POM/4.0.0"   
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"  
xsi:schemaLocation="http://maven.apache.org/POM/4.0.0   http://maven.apache.org/xsd/maven-4.0.0.xsd">  
  
  <modelVersion>4.0.0</modelVersion>  
  
  <groupId>com.javatpoint.application1</groupId>  
  <artifactId>my-application1</artifactId>  
  <version>1.0</version>  
  <packaging>jar</packaging>  
  
  <name>Maven Quick Start Archetype</name>  
  <url>http://maven.apache.org</url>  
  
  <dependencies>  
    <dependency>  
      <groupId>junit</groupId>  
      <artifactId>junit</artifactId>  
      <version>4.8.2</version>  
      <scope>test</scope>  
    </dependency>  
  </dependencies>  
  
</project> 

```

### Any repository can be searched at mvnrepository.com

## Maven pom.xml :

POM is an acronym for Project Object Model. The pom.xml file contains information of project and configuration information for the maven to build the project such as dependencies, build directory, source directory, test source directory, plugin, goals etc.

### Elements of Maven pom.xml

| Element | Descriptions |
|:---- | :---- |
| Project | It is the root element of maven|
|modelVersion | It is the sub element of project. It specifies the modelVersion. It should be set to 4.0.0.|
|groupId| It is the sub element of project. It specifies the id for the project group.|
|artifactId | It is the sub element of project. It specifies the id for the artifact (project). An artifact is something that is either produced or used by a project. Examples of artifacts produced by Maven for a project include: JARs, source and binary distributions, and WARs.|
|version|It is the sub element of project. It specifies the version of the artifact under given group.|

### Additional properties of pom.xml

|Element | Descriptions |
|:----|:-----|
|packaging | defines packaging type such as jar, war etc.|
|name | defines name of the maven project.|
|url|defines url of the project.|
|dependencies|defines dependencies for this project.|
|dependency|defines a dependency. It is used inside dependencies.|
|scope|defines scope for this maven project. It can be compile, provided, runtime, test and system.|

### Example of pom.xml

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"   
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"  
  xsi:schemaLocation="http://maven.apache.org/POM/4.0.0   
http://maven.apache.org/xsd/maven-4.0.0.xsd">  
  
  <modelVersion>4.0.0</modelVersion>  
  
  <groupId>com.javatpoint.application1</groupId>  
  <artifactId>my-application1</artifactId>  
  <version>1.0</version>  
  <packaging>jar</packaging>  
  
  <name>Maven Quick Start Archetype</name>  
  <url>http://maven.apache.org</url>  
  
  <dependencies>  
    <dependency>  
      <groupId>junit</groupId>  
      <artifactId>junit</artifactId>  
      <version>4.8.2</version>  
      <scope>test</scope>  
    </dependency>  
  </dependencies>  
  
</project>   
```







