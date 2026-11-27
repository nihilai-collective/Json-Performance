
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2733.98 | 0.0778333 | 142.508ms | 3808 | 160 | 171.024 | 1328.32 | 0.108572 | 0.887392 | 1(Win) | true |
| Jsonifier (two-stage) | 2493.88 | 0.142701 | 151.017ms | 3808 | 30 | 129.545 | 1456.2 | 0.0458022 | 0.975639 | 2(Loss) | true |
| simdjson (reflection) | 2464.6 | 0.151947 | 146.949ms | 3808 | 40 | 200.513 | 1473.5 | 0.32245 | 0.987743 | 3(Loss) | true |
| Glaze | 2054.92 | 0.0917199 | 181.999ms | 3808 | 30 | 78.823 | 1767.27 | 0.173225 | 1.18662 | 4(Loss) | true |
| simdjson (ondemand) | 1470.41 | 0.0754378 | 297.059ms | 3808 | 160 | 555.408 | 2469.78 | 0.222173 | 1.66593 | 5(Loss) | true |
