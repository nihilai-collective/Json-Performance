
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2530.01 | 0.449693 | 66.7346ms | 1691 | 2560 | 21033.6 | 637.413 | 0.0974734 | 0.939072 | 1(Win) | true |
| Glaze | 2041.33 | 0.0979498 | 82.1428ms | 1691 | 160 | 95.805 | 790.006 | 0.0071207 | 1.17355 | 2(Loss) | true |
| Jsonifier (two-stage) | 1906.73 | 0.203449 | 87.3035ms | 1691 | 40 | 118.435 | 845.775 | 0.375947 | 1.25955 | 3(Loss) | true |
| simdjson (ondemand) | 1450.93 | 0.0540053 | 113.788ms | 1691 | 320 | 115.297 | 1111.47 | 0.0489457 | 1.66533 | 4(Loss) | true |
