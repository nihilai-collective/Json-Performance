
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2505.76 | 0.12478 | 306.568ms | 8051 | 40 | 584.746 | 3064.15 | 0.123319 | 0.979552 | 1(Win) | true |
| Jsonifier (two-stage) | 2330.44 | 0.112238 | 332.546ms | 8051 | 30 | 410.23 | 3294.67 | 0.284091 | 1.05364 | 2(Loss) | true |
| simdjson (reflection) | 1940.45 | 0.0887085 | 404.742ms | 8051 | 40 | 492.815 | 3956.82 | 0.129776 | 1.26745 | 3(Loss) | true |
| simdjson (ondemand) | 1912.78 | 0.181679 | 400.356ms | 8051 | 30 | 1595.51 | 4014.07 | 0.222883 | 1.28573 | 4(Loss) | true |
| Glaze | 1529.28 | 0.472264 | 493.384ms | 8051 | 320 | 179906 | 5020.68 | 0.0430534 | 1.61018 | 5(Loss) | true |
