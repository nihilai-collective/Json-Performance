
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1954.05 | 0.0601717 | 569.722ms | 11579 | 30 | 346.878 | 5651.13 | 0.218723 | 1.26073 | 1(Win) | true |
| Jsonifier | 1891.17 | 0.0449553 | 593.892ms | 11579 | 40 | 275.615 | 5839.02 | 0.12159 | 1.30342 | 2(Loss) | true |
| simdjson (ondemand) | 1770.81 | 0.113296 | 626.649ms | 11579 | 4890 | 244080 | 6235.89 | 0.0036649 | 1.39227 | 3(Loss) | true |
| Glaze | 1637.58 | 0.238226 | 680.07ms | 11579 | 1280 | 330313 | 6743.24 | 0.00413626 | 1.50612 | 4(Loss) | true |
