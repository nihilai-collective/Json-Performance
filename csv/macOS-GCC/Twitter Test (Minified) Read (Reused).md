
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2285.96 | 1.2593 | 5922.99ms | 466906 | 80 | 4.81356e+08 | 194787 | 0.296469 | 1(Win) | true |
| Glaze | 1888.88 | 0.1601 | 7071.52ms | 466906 | 160 | 2.27905e+07 | 235736 | 0.391796 | 2(Loss) | true |
| Jsonifier (two-stage) | 1730.1 | 1.35822 | 7257.66ms | 466906 | 80 | 9.77568e+08 | 257370 | 2.33351 | 3(Loss) | true |
| simdjson (reflection) | 1346.98 | 0.168326 | 9462.85ms | 466906 | 30 | 9.28871e+06 | 330573 | 0.177798 | 4(Loss) | true |
| simdjson (ondemand) | 1060.83 | 0.143954 | 5741.7ms | 466906 | 320 | 1.16832e+08 | 419742 | 1.03562 | 5(Loss) | true |
