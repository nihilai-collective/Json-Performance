
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1203.21 | 0.145019 | 5031.16ms | 409725 | 320 | 7.09746e+07 | 324753 | 0.377583 | 1(Win) | true |
| simdjson (ondemand) | 675.503 | 0.280854 | 8301.94ms | 409725 | 30 | 7.91796e+07 | 578449 | 0.019174 | 2(Loss) | true |
