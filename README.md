# jfifo

This is a circular byte buffer that encodes the entire state of the buffer using only two non-constant variables "added" and "removed."
These do exactly what their names imply: the total number of bytes added and removed all other information needed to add or remove data can be derived from these two values. 

## Features of this implementaion:
  * No lost bytes: buffer can hold exactly "capacity" bytes with no compromise
  * Thread safe single direction transfer*: Data can be added without modifying removed, removed without modifying added.
  * Records total added/removed(up to max value of index_type)
  * All non constant variables are initialized to zero

*assuming that JFIFO_INDEX_TYPE is set to a type(default unsigend int) that is atomic on the target platfrom. Unsigned int is not garunteed to be atomic by any ANSI C standard, but it pretty much always is. You can chaged the type by setting the JFIFO_INDEX_TYPE macro when compileing.
## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites
ANSI C compiler. 


```
Give examples
```


## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc

memoro
