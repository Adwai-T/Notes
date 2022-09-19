# Stalker COC modification Guide

## Modified Trader Files

Place the file that we create here in `../rootStalkerGameFolder/gamedata\configs\misc\trade`. The files should be placed exactly in the location specified.

> Name of the file determines to which trader the file applies. So just by changing the name of the file we can edit the traded items of the trader. eg `trade_sidorovich.ltx` is for **Sidorovich**.

Whatever is after `;` is a comment and extends till the end of the line. We can have code before `;` that will be considered.
eg `ammo_guass = 10, 0.3 ;guass ammo`. The part guass ammo is a comment.

Lastly `#include "trade_discounts.ltx"` needs to be added at the top of every trader file we create.
Dont exactly know what this is, but probably this is a game file that determines the discounts according to the faction and is present in the games default files itself, which means we dont have to add it ourseld, refer to it in the file that we create.

### Trader Configuration [Trader]

In below file we see configuration for Sidorovich(`trade_sidorovich.ltx`).

```ltx
#include "trade_discounts.ltx"

;All the values below should be kept as is and are default values.

[trader]
buy_condition                            = trade_generic_buy
buy_item_condition_factor                = 0
buy_supplies                             = supplies_generic
discounts                                = discount_0
price_profile                            = default
sell_condition                           = trade_generic_sell
```

Traders usually in the default game will not buy weapons and armor that are damaged for any price. The above value for `buy_item_condition_factor` has been changed so that the trader will buy items at any condition. The prices will scale according to the weapon condition.

For different traders we can also set `discounts`. Sidorovich does not belong to any faction so he does not discount any faction that you might belong to. Discount can be configured as below, configured discount for Hawaiian who belong to the freedom faction. As the players reputation with the faction improves the discount on the items will also improve.

```ltx
discounts                                = {=actor_goodwill_ge(freedom:2000)} discount_10, {=actor_goodwill_ge(freedom:1800)} discount_9, {=actor_goodwill_ge(freedom:1600)} discount_8, {=actor_goodwill_ge(freedom:1400)} discount_7, {=actor_goodwill_ge(freedom:1200)} discount_6, {=actor_goodwill_ge(freedom:1000)} discount_5, {=actor_goodwill_ge(freedom:800)} discount_4, {=actor_goodwill_ge(freedom:600)} discount_3, {=actor_goodwill_ge(freedom:400)} discount_2, {=actor_goodwill_ge(freedom:200)} discount_1, discount_0
```

`price_profile` will always be set to the value of `default` as we want that to be the base configuration.

### Traders Selling Prices [trade_generic_sell]

Determines at what price the trader will sell that particular item for.
eg. vodka = 1, 3

The base price of the item is fixed in the list of items file in the game configuration. The below formula uses that base price to determine the traders price.

The formula used to determine value is as `1+2=3 => 3/2=1.5 => 1.5*base price`.

The values can be set to extremely low value to change the selling price of the item.
eg vodka = 0.0003, 0.00025

### Traders Buy Prices [trade_generic_buy]

Determines at what price the trader will buy the item from a player.
eg. vodka 0.7, 0.2

The same formula as above applies. `0.7+0.2=0.9 => 0.9/2=0.45 => 0.45*base price`.

> Usually the default values for the traders for salling will be above 1 and for buy will below 1 as the trader will want to make profit.

### Trader Stock [supplies_generic]

Determines what the trader can sell and how many of the trader can sell at any time.
eg. bandage = 2, 0.55

So trader can have maximum 2 bandages each with a 55% probablity that he will have it.

### Trader Stock with Heavy Pockets achievement [supplies_heavy_pockets]

This works exactly the same way as above stock but only activated once the player has the Heavy Pockets achievement. If this section is not added to a trader above section will be used to determine his stock.
