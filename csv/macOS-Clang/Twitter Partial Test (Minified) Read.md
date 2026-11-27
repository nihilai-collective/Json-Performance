
----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4880.52 | 0.330639 | 9668.7ms | 466906 | 1280 | 1.16478e+08 | 91235.4 | 0.167802 | 1(Win) | true |
| Jsonifier | 4751.19 | 0.466096 | 9844.51ms | 466906 | 640 | 1.22119e+08 | 93718.9 | 0.268301 | 2(Loss) | true |
| simdjson (ondemand) | 4098.26 | 0.0568142 | 5983.39ms | 466906 | 2560 | 9.7547e+06 | 108650 | 0.0833355 | 3(Loss) | true |
| Glaze | 2131.25 | 0.31888 | 5503.54ms | 466906 | 640 | 2.8407e+08 | 208927 | 1.61029 | 4(Loss) | true |
