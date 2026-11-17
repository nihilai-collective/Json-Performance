
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2296.38 | 0.0981573 | 124.703ms | 2889 | 80 | 110.954 | 1199.79 | 0.126223 | 1.05272 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1975.94 | 0.0301549 | 143.857ms | 2889 | 640 | 113.147 | 1394.36 | 0.299982 | 1.22873 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1973 | 0.144724 | 145.037ms | 2889 | 30 | 122.53 | 1396.43 | 0.0716623 | 1.23111 | 2(Tie) | true |
| Glaze | 1960.9 | 0.138527 | 147.681ms | 2889 | 40 | 151.536 | 1405.05 | 0.376971 | 1.23831 | 4(Loss) | true |
| simdjson (ondemand) | 1177.34 | 0.0923848 | 245.438ms | 2889 | 160 | 747.848 | 2340.16 | 0.18075 | 2.07939 | 5(Loss) | true |
