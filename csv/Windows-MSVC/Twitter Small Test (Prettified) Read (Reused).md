
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1884.09 | 0.414858 | 217.828ms | 3808 | 40 | 2557.69 | 1927.5 | 0.0432526 | 1.29025 | 1(Win) | true |
| Glaze | 1650.72 | 0.230168 | 255.155ms | 3808 | 40 | 1025.64 | 2200 | 0 | 1.48315 | 2(Loss) | true |
| simdjson (ondemand) | 1632.18 | 0.218956 | 282.077ms | 3808 | 80 | 1898.73 | 2225 | 0.112486 | 1.49688 | 3(Loss) | true |
| Jsonifier | 1575.53 | 0.21692 | 256.173ms | 3808 | 40 | 1000 | 2305 | 0.0723589 | 1.55262 | 4(Loss) | true |
