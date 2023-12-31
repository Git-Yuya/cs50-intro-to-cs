# TOKYO2020オリンピック～水泳～
#### ビデオデモ：[YouTube](https://youtu.be/-vMqXXmzFvE)
#### 詳細：

**機能**
* 種目別の結果<br>
    競技種目を選択して決定ボタンを押すと、選択した種目の結果が表示される。
* メダルの個数<br>
    メダルの総数順に各チームの獲得したメダルの個数が表示される。
* 得点<br>
    得点順に各チームがそれぞれの競技で獲得した得点が表示される。
* 選手別の結果<br>
    選手を選択して決定ボタンを押すと、選択した選手の結果が表示される。
* チーム別の結果<br>
    チームを選択して決定ボタンを押すと、選択したチームの全選手の結果が表示される。

**実装**
* Flask（Pythonフレームワーク）
* HTML / CSS
* JavaScript
* SQL

**各ファイルの説明**
* application.py：メインファイル
* conversion.py：tokyo2020.csvファイルの内容をtokyo2020.dbファイルに挿入
* tokyo2020.db：results(id, sport, event, rank, athletes, team, record)
* tokyo2020.csv：1~8位のデータ
* index.html：21世紀のオリンピックの開催年、都市、国の表示
* layout.html：メタ情報やナビゲーションメニュー
* select_event.html：競技・種目の選択フォーム
* result.html：選択された種目の結果を表示
* medal.html：チーム別のメダルの個数
* score.html：チーム別の各競技で獲得した得点
* select_athlete.html：選手の選択フォーム
* athlete.html：選択された選手の結果を表示
* select_team.html：チームの選択フォーム
* team.html：選択されたチームの全結果を表示

*得点配分*
|順位|得点|
|:---:|:---:|
|1|8|
|2|7|
|3|6|
|4|5|
|5|4|
|6|3|
|7|2|
|8|1|
<br>

<br>

# TOKYO 2020 Olympic Games - Aquatics
#### Video Demo: [YouTube](https://youtu.be/-vMqXXmzFvE)
#### Description:

**Function**
* Results by event<br>
    When you select a competition event and click the decision button, the results of the selected event will be displayed.
* Number of medals<br>
    Displays the number of medals won by each team in order of total number of medals.
* Score<br>
    Displays the points scored by each team in each event in order of score.
* Results by player<br>
    Select a player and click the decision button to display the results for the selected player.
* Results by team<br>
    Select a team and click the decision button to see the results of all players of the selected team.

**Implementation**
* Flask (Python framework)
* HTML / CSS
* JavaScript
* SQL

**Description of each file**.
* application.py: Main file
* conversion.py: Insert contents of tokyo2020.csv file into tokyo2020.db file
* tokyo2020.db: results(id, sport, event, rank, athletes, team, record)
* tokyo2020.csv: Data of 1~8 ranks
* index.html: Display year, city, and country of the 21st century Olympics
* layout.html: Meta information and navigation menu
* select_event.html: Selection form for events and disciplines
* result.html: Display of results for the selected event
* medal.html: Number of medals by team
* score.html: Scores won in each event by team
* select_athlete.html: Athlete selection form
* athlete.html: Display results of selected athlete
* select_team.html: Team selection form
* team.html: Display all results for the selected team

*Score distribution*
|rank|score|
|:---:|:---:|
|1|8|
|2|7|
|3|6|
|4|5|
|5|4|
|6|3|
|7|2|
|8|1|
<br>
