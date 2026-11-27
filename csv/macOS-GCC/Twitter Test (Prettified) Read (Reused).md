
----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3064.33 | 0.112656 | 5975.73ms | 631514 | 640 | 3.13749e+07 | 196538 | 0.0854065 | 1(Win) | true |
| Jsonifier (two-stage) | 2586.81 | 0.267951 | 7048.09ms | 631514 | 40 | 1.55672e+07 | 232819 | 0.111914 | 2(Loss) | true |
| Glaze | 2377.69 | 0.0655463 | 7380.45ms | 631514 | 1280 | 3.52828e+07 | 253296 | 0.220465 | 3(Loss) | true |
| simdjson (reflection) | 1905.26 | 0.164427 | 9086.12ms | 631514 | 80 | 2.16119e+07 | 316102 | 0.137867 | 4(Loss) | true |
| simdjson (ondemand) | 1396.77 | 0.157215 | 6018.45ms | 631514 | 40 | 1.8381e+07 | 431181 | 0.0296771 | 5(Loss) | true |
