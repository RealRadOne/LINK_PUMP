# Link Pump
Pump links out from LINK_DUMP

LINK_DUMP is a personal telegram group which my friends and I use to dump links from the internet which we find intriguing.
Link_Pump is made in an attempt to make our collection of links available in a neat and organized fashion.

## Build
`sh build.sh`

## Usage
Currently the usage is very specific but could be generalised for curating knowledge. 

## How it works
Every link has the following structure:
```
Link
- Date
- Username
- Tags: [Tag1, Tag2, Tag3]
- Link
- Title
```
We used Mizi, our home grown SSGenerator to generate the website.
The links are stored in a map `Taglist` which maps a tag with a list of pages corresponding to it. For example: `tagList['ML']` gives a list of all the pages tagged as 'ML'.

## Contribute
Feel free to open a PR / issue related to the project. Maintainers of this repo are fairly occupied currently and contribute in the leisure/weekends.
