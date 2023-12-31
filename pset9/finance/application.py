import os
import time

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # User's cash (now)
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # Grand_total = cash + price * shares
    grand_total = 0
    grand_total += user_cash

    rows = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING total_shares > 0;",
        user_id=session["user_id"]
    )

    # Dictionary array for storing values
    holdings = []
    for row in rows:
        quote = lookup(row["symbol"])
        holdings.append({
            "symbol": quote["symbol"],
            "name": quote["name"],
            "shares": row["total_shares"],
            "price": usd(quote["price"]),
            "total": quote["price"] * row["total_shares"]
        })
        grand_total += quote["price"] * row["total_shares"]

    return render_template("index.html", holdings=holdings, user_cash=usd(user_cash), grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get values
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Lookup the stock symbol
        quote = lookup(symbol)

        # Ensure the symbol was valid
        if quote == None:
            return apology("must provide valid symbol", 400)

        # If user inputs invalid number of shares
        try:
            if int(shares) < 1:
                return apology("share must be a positive integer", 400)
        except:
            return apology("share must be a positive integer", 400)

        # User's cash (before)
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # All expence
        expence = quote["price"] * int(shares)

        # Ensure user can afford the stock
        if user_cash < expence:
            return apology("can't afford", 400)

        # User's cash (after)
        user_cash -= expence

        # Update user's cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, session["user_id"])

        # Add values into transaction table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, operation, transacted) VALUES(?, ?, ?, ?, ?, ?)",
            session["user_id"],
            symbol.upper(),
            int(shares),
            usd(quote["price"]),
            "buy",
            time.strftime("%Y/%m/%d %H:%M:%S")
        )

        # When you bought shares
        flash("Bought!")

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Table transactions
    rows = db.execute(
        "SELECT symbol, shares, price, operation, transacted FROM transactions WHERE user_id=:user_id",
        user_id=session["user_id"]
    )

    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Lookup the stock symbol
        quote = lookup(request.form.get("symbol"))

        # Ensure the symbol was valid
        if quote == None:
            return apology("must provide valid symbol", 400)
        else:
            # Get values
            name = quote["name"]
            symbol = quote["symbol"]
            price = quote["price"]

            return render_template("quoted.html", name=name, symbol=symbol, price=usd(price))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get the submitted value
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)
        # Ensure username doesn't exist
        elif len(rows) == 1:
            return apology("username already exists", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not confirmation:
            return apology("must provide the confirmation password", 400)

        # Ensure that the password and confirmation password match
        elif not password == confirmation:
            return apology("must match the password with the confirmation password", 400)

        # Add new user information into database
        else:
            # Generate hash of the user's password
            hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

            # Insert the new user information
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

            # Redirect to home page
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get values
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Number of shares
        rows = db.execute(
            "SELECT SUM(shares) FROM transactions WHERE user_id=:user_id AND symbol=:symbol GROUP BY symbol",
            user_id=session["user_id"],
            symbol=symbol
        )

        # Ensure the symbol was submitted
        if not symbol:
            return apology("must provide valid symbol", 400)

        # If user inputs invalid number of shares
        try:
            if int(shares) < 1:
                return apology("share must be a positive integer", 400)
        except:
            return apology("share must be a positive integer", 400)

        # Ensure user can hold enough shares
        if rows[0]["SUM(shares)"] < int(shares):
            return apology("You don't hold this number of shares", 400)

        # Lookup the stock symbol
        quote = lookup(symbol)

        # Value of shares
        value = 0
        value = quote["price"] * int(shares)

        # User's cash (before)
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # User's cash (after)
        user_cash += value

        # Update user's cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, session["user_id"])

        # Add values into transaction table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, operation, transacted) VALUES(?, ?, ?, ?, ?, ?)",
            session["user_id"],
            symbol.upper(),
            "-" + str(shares),
            usd(quote["price"]),
            "sell",
            time.strftime("%Y/%m/%d %H:%M:%S")
        )

        # When you sold shares
        flash("Sold!")

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        # Symbol of the company in which you hold shares
        rows = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ?", session["user_id"])
        for row in rows:
            symbol = row["symbol"]

        return render_template("sell.html", rows=rows)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add cash"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Amount of cash to add
        amount = request.form.get("cash")

        # Update user's cash
        db.execute(
            "UPDATE users SET cash = cash + :amount WHERE id=:user_id",
            amount=amount,
            user_id=session["user_id"]
        )

        # When you add cash
        flash("Add Cash!")

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("add_cash.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
