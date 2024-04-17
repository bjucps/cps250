FROM python:3.11-slim

# copy/install Python requirements manifest
WORKDIR /app
COPY requirements.txt /app
RUN python3 -m pip install -r requirements.txt

# copy static assets
COPY img/ /app/img/
COPY sounds/ /app/sounds/

# copy code
COPY dukehunt.py /app

# Public port metadata
EXPOSE 3000

# Secret key 
ENV SECRET_KEY=please-replace-me-with-the-real-one

# Entryport: run flask app in non-debug mode
ENTRYPOINT ["flask", "--app", "dukehunt", "run", "-h", "0.0.0.0", "-p", "3000", "--with-threads"]

