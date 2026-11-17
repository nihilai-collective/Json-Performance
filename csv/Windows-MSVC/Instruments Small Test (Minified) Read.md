
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1415.24 | 0.187045 | 326.423ms | 4669 | 80 | 2770.57 | 3146.25 | 0.438947 | 1.72983 | 1(Win) | true |
| Jsonifier (two-stage) | 1027.6 | 0.216327 | 441.61ms | 4669 | 4890 | 429665 | 4333.11 | 0.0256186 | 2.39354 | 2(Loss) | true |
| Glaze | 892.326 | 0.104545 | 517.367ms | 4669 | 80 | 2177.22 | 4990 | 0.0501253 | 2.7594 | 3(Loss) | true |
| simdjson (ondemand) | 673.972 | 0.124295 | 684.619ms | 4669 | 30 | 2022.99 | 6606.67 | 0.151592 | 3.65728 | 4(Loss) | true |
