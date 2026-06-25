# Rate Button
> [!CAUTION]
> ONLY useful on Geometry Dash Private Servers with permissions to rate levels.

> [!WARNING]  
> This mod may not work as well on a different core than [MegaSa1nt's fork](https://github.com/MegaSa1nt/GMDprivateServer/tree/master).

----------

**This mod lets Geometry Dash Private Servers owners/moderators rate levels more precisely through a custom interface instead of using the `!rate` command or the moderator send popup.**
<div align="center">
  <img width="1920" height="1080" alt="Mod preview" src="https://github.com/M336G/RateButton/blob/main/previews/preview-1.png" />
</div>

## Features
- Rate/send levels & set their difficulty automatically
- Set/suggest levels as rated only, featured, epic, legendary, or mythic
- Toggle coins being verified or not
- Set levels for daily or weekly

*This mod is inspired from [how RobTop rates levels](https://www.youtube.com/watch?v=_wmWuymEZDs).*

## Current to-do
- Use the much more efficient [`rateLevel.php`](https://github.com/MegaSa1nt/GMDprivateServer/blob/master/dashboard/api/rateLevel.php) endpoint whenever the new core releases (and whenever I'm actually able to compile web requests)
    - Solves the huge limitations I have with commands (only verifying coins, only setting a feature tier (which also has an issue that's fixed on the new core, making `!feature` unable to override anything above it)...)

## Want to help?
Feel free to open a [Pull Request](https://github.com/M336G/RateButton/pulls) on GitHub!
