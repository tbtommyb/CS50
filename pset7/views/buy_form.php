<form action="buy.php" method="post">
    <fieldset>
        <p>Enter the stock symbol you want to buy:</p>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Symbol" type="text"/>
            <input autocomplete="off" class="form-control" name="shares" placeholder="Shares" type="number"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                Buy
            </button>
        </div>
    </fieldset>
</form>
