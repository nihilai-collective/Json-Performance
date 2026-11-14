
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 926.344 | 0.167511 | 596.049ms | 4630 | 40 | 2550.14 | 4766.6 | 0.293545 | 1(Win) | true |
| Jsonifier (two-stage) | 730.906 | 0.524448 | 682.989ms | 4630 | 640 | 642427 | 6041.15 | 0.0817677 | 2(Loss) | true |
| Glaze | 550.739 | 0.125187 | 914.074ms | 4630 | 4890 | 492601 | 8017.43 | 0.0340476 | 3(Loss) | true |
| simdjson (ondemand) | 505.577 | 0.135571 | 981.72ms | 4630 | 4890 | 685540 | 8733.62 | 0.101688 | 4(Loss) | true |
