import requests
from bs4 import BeautifulSoup
from ast import literal_eval

URL = f"https://www.inflearn.com/courses/it-programming?order=recent&skill=javascript"


def get_last_page():
    result = requests.get(URL)
    soup = BeautifulSoup(result.text, 'html.parser')
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
        page = page+1
        # print(f'inflearn web Scrapping front Page : {page}')
        result = requests.get(f'{URL}&page={page}')
        soup = BeautifulSoup(result.text, 'html.parser')
        results = soup.find_all("div", {"class": "course_card_item"})

        for result in results:
            content = extract_course_content(result)
            course.append(content)

    return course


def extract_course_content(html):
    title = html.find("a", {"class": "course_card_front"}).find(
        "div", {"class": "course_title"}).string
    link = html.find("a")["href"]
    instructor = html.find("a", {"class": "course_card_front"}).find(
        "div", {"class": "instructor"}).string
    rating = extract_rating(html)
    price = literal_eval(html["fxd-data"])  # string to dict
    # html is "class": "course_card_item"
    price = price.get('reg_price')  # get 'get_price' key`s values

    return {
        "title": title,
        "course_link": f'https://www.inflearn.com{link}',
        "instructor": instructor,
        "rating": rating,
        "price": price,
    }


def extract_rating(html):
    result = html.find("a", {"class": "course_card_front"}).find(
        "div", {"class": "star_solid"})['style']
    result = float(result.lstrip("width: ").rstrip("%"))  # str to float
    rating = round(result)
    return rating


def get_course():
    last_page = get_last_page()
    course = extract_course(last_page)
    return course
