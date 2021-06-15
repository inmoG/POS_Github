import csv


def save_to_file(course):
    file = open('course.csv', mode='w', encoding="utf-8", newline="")
    # UnicodeEncodeError: 'cp949' codec can't encode character '\xa0' in position 138: illegal multibyte sequence
    writer = csv.writer(file)
    writer.writerow(['title', 'course_link', 'instructor',
                     'rating', 'price', 'description', 'level', 'skills'])

    for course in course:
        writer.writerow(list(course.values()))  # list(course.values)

    return
