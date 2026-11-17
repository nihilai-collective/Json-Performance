
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 819.387 | 1.69841 | 710.283ms | 4630 | 80 | 670126 | 5388.8 | 0.236967 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 674.632 | 1.34821 | 831.278ms | 4630 | 30 | 233594 | 6545.07 | 0 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 671.295 | 0.389693 | 871.965ms | 4630 | 640 | 420494 | 6577.6 | 0.207191 | 2(Tie) | true |
| Glaze | 612.449 | 0.73784 | 911.024ms | 4630 | 80 | 226379 | 7209.6 | 0.044405 | 4(Loss) | true |
| simdjson (ondemand) | 526.86 | 0.244726 | 943.592ms | 4630 | 2560 | 1.07689e+06 | 8380.8 | 1.77049 | 5(Loss) | true |
