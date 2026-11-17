
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5280.46 | 0.377651 | 6645.76ms | 631514 | 30 | 5.56578e+06 | 114054 | 0.336104 | 1(Win) | true |
| Jsonifier | 5208.1 | 0.447726 | 6510.54ms | 631514 | 30 | 8.04182e+06 | 115639 | 0.912793 | 2(Loss) | true |
| simdjson (ondemand) | 4073.61 | 0.647278 | 7532.8ms | 631514 | 640 | 5.86096e+08 | 147844 | 1.46717 | 3(Loss) | true |
| Glaze | 2671.31 | 0.38909 | 5863.16ms | 631514 | 30 | 2.30854e+07 | 225454 | 0.017331 | 4(Loss) | true |
