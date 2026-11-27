
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5162.19 | 0.243494 | 6230.86ms | 631514 | 2560 | 2.06593e+08 | 116667 | 0.136351 | 1(Win) | true |
| Jsonifier | 4320.45 | 0.682605 | 5946.8ms | 631514 | 160 | 1.44866e+08 | 139397 | 0.149869 | 2(Loss) | true |
| simdjson (ondemand) | 3961.36 | 0.449513 | 7146.41ms | 631514 | 320 | 1.49456e+08 | 152033 | 2.65005 | 3(Loss) | true |
| Glaze | 2794.97 | 0.126973 | 5568.17ms | 631514 | 160 | 1.19773e+07 | 215479 | 0.00257282 | 4(Loss) | true |
