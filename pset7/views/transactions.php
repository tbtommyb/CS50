<div>
    <table>
        <tr>
            <th>Symbol</th>
            <th>Number of shares</th>
            <th>Buy/sell</th>
            <th>Price</th>
            <th>Time</th>
        </tr>
        <?php foreach ($transactions as $transaction): ?>
            <tr>
                <td><?= $transaction["symbol"] ?></td>
                <td><?= $transaction["shares"] ?></td>
                <td><?= $transaction["buy"] ? "Buy" : "Sell" ?></td>
                <td><?= $transaction["price"] ?></td>
                <td><?= $transaction["time"] ?></td>
            </tr>
        <?php endforeach ?>
    </table>
</div>