
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 5032.3 | 0.402825 | 6307.26ms | 631514 | 320 | 7.43732e+07 | 119679 | 2.7884 | 1(Win) | true |
| Jsonifier | 4880.15 | 0.300788 | 6438.15ms | 631514 | 640 | 8.81863e+07 | 123410 | 3.13682 | 2(Loss) | true |
| simdjson (ondemand) | 4498.43 | 0.24281 | 7225.2ms | 631514 | 640 | 6.76326e+07 | 133882 | 0.0800554 | 3(Loss) | true |
| Glaze | 2507.22 | 0.766545 | 6140.04ms | 631514 | 40 | 1.35617e+08 | 240209 | 0.216501 | 4(Loss) | true |
