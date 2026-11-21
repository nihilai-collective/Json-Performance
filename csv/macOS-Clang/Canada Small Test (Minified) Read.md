
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 653.651 | 0.091689 | 697.995ms | 4630 | 40 | 1534.49 | 6755.15 | 0.0985404 | 1(Win) | true |
| Jsonifier (two-stage) | 586.563 | 0.380297 | 790.539ms | 4630 | 30 | 24586.7 | 7527.77 | 4.7949 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 410.648 | 0.298077 | 1120.95ms | 4630 | 2560 | 2.62978e+06 | 10752.5 | 2.22387 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 404.156 | 1.06657 | 1092.33ms | 4630 | 160 | 2.1725e+06 | 10925.3 | 0.0307678 | 3(Tie) | true |
