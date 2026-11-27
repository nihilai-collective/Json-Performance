
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1788.27 | 0.580317 | 5041.68ms | 5373214 | 40 | 1.1061e+10 | 2.86551e+06 | 0.334152 | 1(Win) | true |
| Jsonifier (two-stage) | 1646.8 | 0.0700782 | 5509.58ms | 5373214 | 30 | 1.4265e+08 | 3.11166e+06 | 0.0335977 | 2(Loss) | true |
| Glaze | 1398.87 | 0.066341 | 6301.14ms | 5373214 | 40 | 2.36231e+08 | 3.66316e+06 | 0.396607 | 3(Loss) | true |
| simdjson (ondemand) | 1345.24 | 0.388209 | 6653.92ms | 5373214 | 30 | 6.56029e+09 | 3.80921e+06 | 0.704579 | 4(Loss) | true |
