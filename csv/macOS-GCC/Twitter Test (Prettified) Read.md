
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1932.13 | 0.616645 | 7997.11ms | 631514 | 320 | 1.18226e+09 | 311706 | 0.229201 | 1(Win) | true |
| Jsonifier (two-stage) | 1904.42 | 0.394222 | 7899.77ms | 631514 | 320 | 4.9736e+08 | 316242 | 0.758808 | 2(Loss) | true |
| Glaze | 1842.1 | 0.192254 | 8319.7ms | 631514 | 320 | 1.26427e+08 | 326942 | 0.128787 | 3(Loss) | true |
| simdjson (reflection) | 1608.44 | 0.423674 | 9636.98ms | 631514 | 160 | 4.02662e+08 | 374437 | 0.787703 | 4(Loss) | true |
| simdjson (ondemand) | 1262.61 | 0.152888 | 6182.95ms | 631514 | 640 | 3.4037e+08 | 476993 | 1.08965 | 5(Loss) | true |
