#set the parent image as a official python runtime
FROM python:2.7-slim

#set the working directory to /app
WORKDIR /app

#copy the content of the current directory to the /app directory of the image
COPY . /app

#install any needed package defined in requirements.txt
RUN pip install --trusted-host pypi.python.org -r requirements.txt

#make port 80 available to the world outside the container
EXPOSE 80

#define environment variable NAME
ENV NAME World

#run app.py when the container launches
CMD ["python", "app.py"]
