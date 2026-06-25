# Rate Button
**<cr>ONLY useful on Geometry Dash Private Servers with permissions to rate levels.</c>**

**<co>This mod may not work as well on a different core than [MegaSa1nt's fork](https://github.com/MegaSa1nt/GMDprivateServer/tree/master).</c>**

----------

This mod lets Geometry Dash Private Servers owners/moderators <cj>rate levels more precisely</c> through a <cj>custom interface</c> instead of using the <co>`!rate` command</c> or the <co>moderator send popup</c>.

## Features
- <cj>Rate levels</c> & set their <cj>difficulty automatically</c>
- Set levels as <cj>rated only</c>, <cj>featured</c>, <cj>epic</c>, <cj>legendary</c>, or <cj>mythic</c>
- Toggle <cj>coins being verified or not</c>

*This mod is inspired from [how RobTop rates levels](https://www.youtube.com/watch?v=_wmWuymEZDs).*

## Current to-do
- Use the much more efficient [`rateLevel.php`](https://github.com/MegaSa1nt/GMDprivateServer/blob/master/dashboard/api/rateLevel.php) endpoint whenever the new core releases (and whenever I'm actually able to compile web requests)
    - Solves the huge limitations I have with commands (only verifying coins, only setting a feature tier (which also has an issue that's fixed on the new core, making `!feature` unable to override anything above it)...)

## Want to help?
Feel free to open a [Pull Request](https://github.com/M336G/RateButton/pulls) on GitHub!