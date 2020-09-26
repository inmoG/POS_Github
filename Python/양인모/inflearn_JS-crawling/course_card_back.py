import requests
from bs4 import BeautifulSoup

URL = f"https://www.inflearn.com/courses/it-programming?order=seq&skill=javascript"


def get_last_page():
    result = requests.get(URL)
    soup = BeautifulSoup(result.text, "html.parser")
    pagination = soup.find("div", {"class": "pagination_container"})
    links = pagination.find_all("a")

    page = []

    for link in links[1:]:
        page.append(int(link.string))

    MAX_page = page[-1]
    return MAX_page


def extract_course(last_page):
    course = []

    for page in range(last_page):
        page = page + 1
        # print(f'inflearn web Scrapping back Page : {page}')
        result = requests.get(f"{URL}&page={page}")
        soup = BeautifulSoup(result.text, "html.parser")
        results = soup.find_all("div", {"class": "course_card_back"})

        for result in results:
            content = extract_course_content(result)
            course.append(content)

    return course


def extract_course_content(html):
    description = html.find("p", {"class": "course_description"}).text
    # .replace('\n', ' ').replace('\r', ' ').replace('\x01', ' ')
    level = html.find("div", {"class": "course_level"}).span.get_text()
    skills = html.find("div", {"class": "course_skills"}).span.get_text()

    return {
        "description": description,
        "level": level,
        "skills": skills,
    }


def get_course():
    last_page = get_last_page()
    course = extract_course(last_page)
    return course
