
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1330.39 | 0.111962 | 697.986ms | 8051 | 80 | 3340.19 | 5771.25 | 0.0216638 | 1.85396 | 1(Win) | true |
| Jsonifier | 1250.62 | 0.0663348 | 741.777ms | 8051 | 160 | 2653.69 | 6139.38 | 0.0508751 | 1.97249 | 2(Loss) | true |
| Glaze | 1177.84 | 0.0709213 | 780.106ms | 8051 | 160 | 3419.81 | 6518.75 | 0.0767607 | 2.09323 | 3(Loss) | true |
| simdjson (ondemand) | 924.786 | 0.180346 | 961.034ms | 8051 | 40 | 8967.95 | 8302.5 | 0.19107 | 2.66853 | 4(Loss) | true |
