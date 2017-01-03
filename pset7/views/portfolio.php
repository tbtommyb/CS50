<div>
    <table>
        <tr>
            <th>Symbol</th>
            <th>Number of shares</th>
            <th>Price</th>
        </tr>
        <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= $position["price"] ?></td>
            </tr>
        <?php endforeach ?>
    </table>
    <p>Cash balance: <?= number_format($cash, 2); ?>.</p>
</div>