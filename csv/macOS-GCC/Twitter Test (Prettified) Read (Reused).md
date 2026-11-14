
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2655.04 | 0.123899 | 6813.99ms | 631514 | 640 | 5.05524e+07 | 226836 | 0.236439 | 1(Win) | true |
| Jsonifier (two-stage) | 2513.4 | 0.311327 | 7257.39ms | 631514 | 160 | 8.90424e+07 | 239619 | 1.11978 | 2(Loss) | true |
| Glaze | 2367.93 | 0.100369 | 7439.63ms | 631514 | 1280 | 8.34131e+07 | 254340 | 0.0897242 | 3(Loss) | true |
| simdjson (reflection) | 1756.72 | 0.220198 | 9771.15ms | 631514 | 640 | 3.64727e+08 | 342831 | 0.51664 | 4(Loss) | true |
| simdjson (ondemand) | 1437.48 | 0.174618 | 5780.27ms | 631514 | 160 | 8.56364e+07 | 418968 | 0.0630517 | 5(Loss) | true |
