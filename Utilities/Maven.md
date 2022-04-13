# Maven

## Apache Maven helps to manage

1. Builds
2. Documentation
3. Reporing
4. SCMs
5. Releases
6. Distribution

## Maven Repositories

### Local Repository

Stored in local computer at %USER_HOME%/.m2

This is the default code of the setting.xml located `MAVEN_HOME/conf/settings.xml`

To change the default directory of the local repository from `${user.home}/.m2/repository`  to `E:\mavenlocalrepository` we change the maven config file `MAVEN_HOME/conf/settings.xml`.

```xml

    <settings xmlns="http://maven.apache.org/SETTINGS/1.0.0"   
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"   
    xsi:schemaLocation="http://maven.apache.org/SETTINGS/1.0.0 http://maven.apache.org/xsd/settings-1.0.0.xsd">  
    <localRepository>e:/mavenlocalrepository</localRepository>  
  
    </settings> 
```

### Central Repository

Path to the central repository : [Central Repository](http://repo1.maven.org/maven2/).

Libraries that are stored on the Central repository can be searched at : [Maven Repository](http://search.maven.org/#browse).

### Remote Repository

Some libraries might be missing from the central repository.

We can find these libraries at other remote maven repositories like the [MVN Repostory](mvnrepository.com). The search and index more repositories than the maven central repository.

## Maven pom.xml

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
  
  <!-- Project Coordinates -->
  <groupId>in.adwait</groupId><!--Name of the company/Organization-->
  <artifactId>website</artifactId><!--Name of the project-->  
  <version>1.0-SNAPSHOT</version><!--SNAPSHOT meaning the project is under active development-->
  <packaging>jar</packaging>  
  
  <name>spring-website</name>
  <url>http://maven.apache.org</url>  

  <properties>
    <!-- Set the compiler to compile with Java 8 as target -->
    <maven.compiler.target>1.8</maven.compiler.target>
    <!-- Set the accepted level of Java for the source  -->
    <maven.compiler.source>1.8</maven.compiler.source>
  </properties>
  
  <dependencies>  
    <dependency>  
      <groupId>junit</groupId>  
      <artifactId>junit</artifactId>  
      <version>4.8.2</version>  
      <scope>test</scope>  
    </dependency> 
    <!--We can have any number of dependencies--> 
  </dependencies>  
  
</project>   
```

## Maven Archetypes

Archetypes can be used to create new Maven projects.

They contain template files for a given Maven project to get us started.

We can think of maven Archetypes like a collection of starter files for a project such as Java Project or Web Project, etc.

Commonly Used Archetypes

* maven-archetype-quickstart : Genereate a sample maven project. Good for standalone projects.
* maven-archetype-webapp : An archetype to generate a sample Maven Web Project.
* We can find more [archetype here](http://maven.apache.org/archetypes).

Let take maven-archetype-webapp for example. When we generate a project with maven using this archetype, it will get us started with a file structure suited for web-app development and also add the common files need in the project.

Like `pom.xml` for maven, `index.jsp` to get us