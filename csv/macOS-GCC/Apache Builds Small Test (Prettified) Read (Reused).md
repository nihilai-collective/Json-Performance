
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2107.17 | 0.505134 | 192.322ms | 3370 | 4890 | 290258 | 1525.22 | 3.35727 | 1(Win) | true |
| Glaze | 1961.24 | 0.839571 | 187.013ms | 3370 | 2560 | 484567 | 1638.7 | 2.31643 | 2(Loss) | true |
| Jsonifier | 1762.41 | 0.526293 | 201.77ms | 3370 | 4890 | 450409 | 1823.57 | 1.29537 | 3(Loss) | true |
| simdjson (reflection) | 1346.3 | 1.20562 | 244.789ms | 3370 | 320 | 265061 | 2387.2 | 0.336247 | 4(Loss) | true |
| simdjson (ondemand) | 1255.82 | 1.33016 | 311.272ms | 3370 | 320 | 370822 | 2559.2 | 1.32634 | 5(Loss) | true |
