This repository will contain historical data on the Bay Area Rapid
Transit, including ridership, fares, and route frequency.

The website for accessing the data online is
[bart.vipulnaik.com](https://bart.vipulnaik.com).

Sources I am using for data:

* [Ridership](http://www.bart.gov/about/reports/ridership)
* Historical fare and route data:
  [2016](https://www.bart.gov/sites/default/files/docs/F_S%20FEB%202016%20.pdf),
  [2014](https://www.bart.gov/sites/default/files/docs/Fare_Scheds%20Jan%202014.pdf),
  [2012](https://www.bart.gov/sites/default/files/docs/BART_FS_31.pdf),
  [2009](https://www.bart.gov/sites/default/files/docs/BART_FS_091409.pdf),
  [2008](https://www.bart.gov/sites/default/files/docs/BART010108.pdf),
  [2005](https://www.bart.gov/sites/default/files/docs/BART091205.pdf). The
  data is mirrored in the
  [faresandschedules](https://github.com/vipulnaik/bart/tree/master/faresandschedules/)
  folder here.

## Setting up

This section is for people who want to set up a local mirror of the
entertainment and self-education portal (e.g., for development
purposes) or want to load up the data into a local database to run
their own queries.

Note that the `passwordFile.inc` file in
`access-portal/backend/globalVariables` is excluded from the Git
repository, but you can modify a corresponding dummy password file at
[`dummyPasswordFile.inc`](https://github.com/vipulnaik/bart/blob/master/access-portal/backend/globalVariables/dummyPasswordFile.inc):

```bash
cp access-portal/backend/globalVariables/{dummyPasswordFile.inc,passwordFile.inc}
vi access-portal/backend/globalVariables/passwordFile.inc # change to add database login info
```

The database name is present both in dummyPasswordFile.inc and in the
Makefile, so if you want a name other than `bart`, you should edit the
name in both places.

You can create the `bart` database either directly in MySQL or by
running this from the root folder of this repository, after updating
MYSQL_ARGS in the Makefile (such as `-u<username> -p<password>`):

```bash
make init
```

Instead of editing the Makefile, you can also pass in the arguments to
make:

```bash
make MYSQL_ARGS=<args> init
```

### Loading and refreshing data

Once you already have the `ese` SQL database set up, you can update
the MYSQL_ARGS in the Makefile (such as `-u<username> -p<password>`)
and you can then load the data using:

```bash
make reset && make read
```

Instead of editing the Makefile, you can also pass in the arguments to
each make:

```bash
make MYSQL_ARGS=<args> reset && make MYSQL_ARGS=<args> read
```

### Just refreshing ridership data

If you just want to refresh the ridership data (that we do every few
months):

```bash
make refresh_ridership
```

### Table sorting

To get files for table sorting, run:

```bash
make fetch_table_sorting
```

You can remove these files with `make clean_table_sorting`.

### AnchorJS

To get AnchorJS, run:

```bash
make fetch_anchorjs
```

You can remove these files with `make clean_anchorjs`.

### Graphing

For the graphing, you need to make sure you have `python3` working,
and you also need to install some packages. You can install the
packages with `pip3` as follows:

```bash
pip3 install argparse pandas numpy matplotlib
```

If for whatever reason you don't have `pip3` installed, you need to
install it first.
