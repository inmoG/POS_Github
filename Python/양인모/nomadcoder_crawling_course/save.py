import csv

def save_to_file(jobs):
  file = open('jobs.csv', mode="w")
  writer = csv.writer(file)
  writer.writerow(['title', 'company', 'location', 'link'])
  for job in jobs:
    #writer.writerow(job.value()) # dict get only value 
    writer.writerow(list(job.values()))

  return