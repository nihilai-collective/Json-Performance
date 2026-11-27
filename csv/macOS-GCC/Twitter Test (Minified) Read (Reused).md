
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2083.81 | 0.358613 | 7346.57ms | 264040 | 30 | 5.63376e+06 | 120841 | 0.701213 | 1(Win) | true |
| simdjson (ondemand) | 1486.01 | 0.197997 | 9851.17ms | 264040 | 80 | 9.00543e+06 | 169453 | 0.143315 | 2(Loss) | true |
