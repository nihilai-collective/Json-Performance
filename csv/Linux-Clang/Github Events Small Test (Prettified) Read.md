
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2639.62 | 0.0487825 | 81.2982ms | 2158 | 320 | 46.2912 | 779.669 | 0.0328557 | 0.905383 | 1(Win) | true |
| Glaze | 2182.5 | 0.0529925 | 98.4885ms | 2158 | 320 | 79.905 | 942.969 | 0.0908862 | 1.10347 | 2(Loss) | true |
| Jsonifier | 1885.99 | 0.306609 | 111.813ms | 2158 | 2560 | 28657.4 | 1091.22 | 0.0482312 | 1.2818 | 3(Loss) | true |
| simdjson (ondemand) | 1806.87 | 0.162589 | 117.316ms | 2158 | 40 | 137.179 | 1139 | 0.0643425 | 1.33996 | 4(Loss) | true |
