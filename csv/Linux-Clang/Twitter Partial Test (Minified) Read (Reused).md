
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 10490.3 | 0.0914712 | 4329.28ms | 466906 | 2560 | 3.85913e+06 | 42446.4 | 0.175038 | 0.235859 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 10483.8 | 0.0741305 | 4358.56ms | 466906 | 2560 | 2.5378e+06 | 42472.9 | 0.412157 | 0.236006 | 1(Tie) | true |
| simdjson (ondemand) | 8081.82 | 0.10592 | 5577.95ms | 466906 | 1280 | 4.35916e+06 | 55096 | 0.000747281 | 0.306187 | 3(Loss) | true |
| Glaze | 3512.52 | 0.155797 | 6616.01ms | 466906 | 160 | 6.24112e+06 | 126768 | 0.0821838 | 0.704717 | 4(Loss) | true |
