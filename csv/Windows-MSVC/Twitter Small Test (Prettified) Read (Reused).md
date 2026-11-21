
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2112.54 | 0.130497 | 190.286ms | 3808 | 320 | 1610.4 | 1719.06 | 0.0545058 | 1.15542 | 1(Win) | true |
| Jsonifier (two-stage) | 2028.82 | 0.307921 | 215.181ms | 3808 | 80 | 2430.38 | 1790 | 0.13986 | 1.19944 | 2(Loss) | true |
| Glaze | 1790.06 | 0.176923 | 229.444ms | 3808 | 160 | 2061.32 | 2028.75 | 0.123381 | 1.3683 | 3(Loss) | true |
| Jsonifier | 1670.9 | 0.119119 | 249.237ms | 3808 | 320 | 2144.89 | 2173.44 | 0.187266 | 1.46578 | 4(Loss) | true |
