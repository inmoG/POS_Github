import requests
from bs4 import BeautifulSoup

LIMIT = 50
URL = f"https://kr.indeed.com/jobs?q=Python&l=&limit={LIMIT}"


def get_last_pages():
    result = requests.get(URL)
    soup = BeautifulSoup(result.text, "html.parser")
    pagination = soup.find("div", {"class": "pagination"})  # this is list
    links = pagination.find_all("a")

    page = []

    for link in links[:-1]:  # 다음"은 스트링이여서 정수로 변환이 불가함 아예 제외하고 for문을 돌리는 것
        page.append(int(link.string))

    MAX_page = page[-1]  # last_page
    return MAX_page
    # 페이지가 0~12번까지라면 12번은 안나옴
    # anchor(요소)안에 요소가 하나뿐이며 스트링만 가지고 있으면 anchor(요소)만  뽑아와도 스트링을 뽑아줌
    # [2,3,4,5,6,7,8,9,10,11,next]
    # reverse [next,11,10,9,8,7,6,5,4,3,2] -1,-2,-3,-4,-5
    # -1 = next, -2 = 11, -3 = 10 을 뜻한다. 따라서 [:-1]은
    # -1인 next를 제외하고 뽑아달라는 의미다. -2 까지라면 11, next를 제외한다.


def extract_job(html):
    title = html.find("div", {"class": "title"}).find("a")["title"]
    company = html.find("span", {"class": "company"})
    company_anchor = company.find("a")
    location = html.find("div", {"class": "recJobLoc"})["data-rc-loc"]
    job_id = html["data-jk"]

    if company:
        if company_anchor is not None:
            company = str(company_anchor.string)
        else:
            company = str(company.string)
        ompany = company.strip()
    else:
        company = None

    return {
        "title": title,
        "company": company,
        "location": location,
        "link": f"https://kr.indeed.com/viewjob?jk={job_id}",
    }


def extract_jobs(last_page):
    jobs = []
    for page in range(last_page):
        print(f"indeed Web Scrraping Page : {page}")
        result = requests.get(f"{URL}&start={page*LIMIT}")
        # 페이지당 50개의 구인공고를 출력하고 페이지가  넘어갈 때 마다 start = page * 50
        soup = BeautifulSoup(result.text, "html.parser")
        results = soup.find_all("div", {"class": "jobsearch-SerpJobCard"})
        # results는 Soup의 리스트다.
        # find all = 모든 리스트를 가져온다
        # find = 첫번째 찾은 결과를 보여준다.
        for result in results:
            job = extract_job(result)
            jobs.append(job)
    return jobs


def get_jobs():
    last_page = get_last_pages()
    jobs = extract_jobs(last_page)
    return jobs
