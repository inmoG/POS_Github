import requests
from bs4 import BeautifulSoup

URL = f"https://stackoverflow.com/jobs?q=python&sort=i"


def get_last_page():

    result = requests.get(URL)
    soup = BeautifulSoup(result.text, 'html.parser')
    pages = soup.find("div", {"class": "pagination"}).find_all("a")
    # pagination is one, pagination`anchor is many so pagination tag use find(), anchor tag use find_all()
    last_page = pages[-2].get_text(strip=True)
    # get_text() returns all the text in a document or beneath a tag.
    # string works only if a tag has only one child the child is made available as string
    return int(last_page)


def extract_job(html):
    title = html.find("div", {"class": "-title"}).find('h2').find('a')['title']
    company, location = html.find(
        "div", {"class": "-company"}).find_all("span", recursive=False)
    # The span tag contains a span tag. Using recursive brings only the first span.
    company = company.get_text(strip=True)
    location = location.get_text(strip=True).strip('-').rstrip().lstrip()
    # rstrip clear rightspace, lstrip clear leftspace and strip clear whitespace
    #location = location.get_text(strip=True).strip('-').strip(' \r').strip('\n')
    job_id = html['data-jobid']
    return {'title': title,
            'company': company,
            'location': location,
            'apply_link': f'https://stackoverflow.com/jobs/{job_id}'}


def extract_jobs(last_page):
    jobs = []  # include title, location, link

    for page in range(last_page):
        print(f'SO Scrapping Page : {page}')
        result = requests.get(f"{URL}&pg={page}")
        soup = BeautifulSoup(result.text, 'html.parser')
        results = soup.find_all("div", {"class": "-job"})

        for result in results:
            job = extract_job(result)
            jobs.append(job)
    return jobs


def get_jobs():
    last_page = get_last_page()
    jobs = extract_jobs(last_page)
    return jobs
