import os
import time

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError

from helpers import apology

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///tokyo2020.db")

# List of events
rows0 = db.execute("SELECT DISTINCT(event) FROM results")
events = []
for row0 in rows0:
    events.append(row0["event"])

# List of athletes from DB
rows1 = db.execute("SELECT DISTINCT(athletes) FROM results")
pre_athletes = []
for row1 in rows1:
    pre_athletes.append(row1["athletes"])

# List of each athlete
athletes = []
for pre_athlete in pre_athletes:
    for athlete in pre_athlete.split(","):
        # Store the name of each athlete
        buff = athlete.strip()
        if buff not in athletes:
            athletes.append(buff)
athletes.sort()

# List of teams
rows2 = db.execute("SELECT DISTINCT(team) FROM results")
teams = []
for row2 in rows2:
    teams.append(row2["team"])
teams.sort()


@app.route("/")
def index():
    """"Display Olympic host cities"""

    return render_template("index.html")


@app.route("/result", methods=["GET", "POST"])
def result():
    """Display the top 8 records"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get event value
        event = request.form.get("event")

        # Ensure the event was valid
        if event not in events:
            return apology("must have valid event", 400)

        else:
            # Query database for event
            rows = db.execute("SELECT rank, athletes, team, record FROM results WHERE event=?", event)

            # Dictionary array for results
            results = []
            for row in rows:
                results.append({
                    "rank": row["rank"],
                    "athletes": row["athletes"],
                    "team": row["team"],
                    "record": row["record"]
                })

            return render_template("result.html", results=results)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("select_event.html")


@app.route("/medal")
def medal():
    """Display the number of medals won"""

    # Query database for rank
    rows = db.execute("SELECT rank, team FROM results WHERE rank=1 OR rank=2 OR rank=3")

    # Dictionary array for storing the number of medals
    medals = []

    for row in rows:

        # Whether the team exists or not
        is_exist = False

        # Judge whether the team exists in the array
        for i in range(len(medals)):

            # If the team existed in the array
            if row["team"] in medals[i]["team"]:
                is_exist = True
                break

        # If the team did not exist in the array
        if is_exist == False:

            # Add to the array
            medals.append({
                "rank": 0,
                "team": row["team"],
                "gold": 0,
                "silver": 0,
                "bronze": 0,
                "total": 0
            })

    # Calculate the number of medals
    for row in rows:
        for j in range(len(medals)):

            if row["team"] in medals[j]["team"]:

                # If in first place
                if row["rank"] == 1:
                    medals[j]["gold"] += 1
                    medals[j]["total"] += 1
                    break

                # If in second place
                if row["rank"] == 2:
                    medals[j]["silver"] += 1
                    medals[j]["total"] += 1
                    break

                # If in third place
                if row["rank"] == 3:
                    medals[j]["bronze"] += 1
                    medals[j]["total"] += 1
                    break

    # Sort the array
    medals = sorted(medals, key=lambda x: (x["total"], x["gold"], x["silver"], x["bronze"]), reverse=True)

    # Store the rankings
    for r in range(len(medals)):
        if r >= 1 and medals[r]["gold"] == medals[r - 1]["gold"] and medals[r]["silver"] == medals[r - 1]["silver"] and medals[r]["bronze"] == medals[r - 1]["bronze"]:
            medals[r]["rank"] = medals[r - 1]["rank"]
        else:
            medals[r]["rank"] = r + 1

    return render_template("medal.html", medals=medals)


@app.route("/score", methods=["GET", "POST"])
def score():
    """Display the scores of each team"""

    # Query database for score
    rows = db.execute("SELECT sport, rank, team FROM results")

    # Dictionary array for each scores
    scores = []

    for row in rows:

        # Whether the team exists or not
        is_exist = False

        # Judge whether the team exists in the array
        for i in range(len(scores)):

            # If the team existed in the array
            if row["team"] in scores[i]["team"]:
                is_exist = True
                break

        # If the team did not exist in the array
        if is_exist == False:

            # Add to the array
            scores.append({
                "rank": 0,
                "team": row["team"],
                "競泳": 0,
                "飛び込み": 0,
                "水球": 0,
                "マラソンスイミング": 0,
                "アーティスティックスイミング": 0,
                "total": 0
            })

    # Score list
    score_list = [8, 7, 6, 5, 4, 3, 2, 1]

    # Calculate the scores of each sport
    for row in rows:
        for j in range(len(scores)):
            if row["team"] in scores[j]["team"]:

                if row["rank"] == "失格":
                    break

                scores[j][row["sport"]] += score_list[row["rank"] - 1]
                scores[j]["total"] += score_list[row["rank"] - 1]
                break

    # Sort the array
    scores = sorted(scores, key=lambda x: x["total"], reverse=True)

    # Store the rankings
    for r in range(len(scores)):
        if r >= 1 and scores[r]["total"] == scores[r - 1]["total"]:
            scores[r]["rank"] = scores[r - 1]["rank"]
        else:
            scores[r]["rank"] = r + 1

    return render_template("score.html", scores=scores)


@app.route("/athlete", methods=["GET", "POST"])
def athlete():
    """Display the results of athlete"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get athlete value
        athlete = request.form.get("athlete")

        # Ensure the athlete was valid
        if athlete not in athletes:
            return apology("must have valid athlete", 400)

        else:
            athlete = "%" + athlete + "%"
            # Query database for event
            rows = db.execute("SELECT sport, event, rank, athletes, team, record FROM results WHERE athletes LIKE ?", athlete)

            # Dictionary array for results of athlete
            results = []
            for row in rows:
                results.append({
                    "sport": row["sport"],
                    "event": row["event"],
                    "rank": row["rank"],
                    "athletes": row["athletes"],
                    "team": row["team"],
                    "record": row["record"]
                })

            return render_template("athlete.html", results=results)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("select_athlete.html", athletes=athletes)


@app.route("/team", methods=["GET", "POST"])
def team():
    """Display the results of team"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get team value
        team = request.form.get("team")

        # Ensure the team was valid
        if team not in teams:
            return apology("must have valid team", 400)

        else:
            # Query database for event
            rows = db.execute("SELECT sport, event, rank, athletes, record FROM results WHERE team=?", team)

            # Dictionary array for results
            results = []
            for row in rows:
                results.append({
                    "sport": row["sport"],
                    "event": row["event"],
                    "rank": row["rank"],
                    "athletes": row["athletes"],
                    "record": row["record"]
                })

            return render_template("team.html", results=results)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("select_team.html", teams=teams)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
