const SELECTORS = {
    section: "section",
    scrollTo: ".link",
    scrollDir: ".scrollctrl"
}

const sectionsArray = Array.from(document.querySelectorAll(SELECTORS.section));
const scrollToElements = document.querySelectorAll(SELECTORS.scrollTo);
const scrollDirElements = document.querySelectorAll(SELECTORS.scrollDir);

let currentSectionIndex = 0;

console.log(sectionsArray)