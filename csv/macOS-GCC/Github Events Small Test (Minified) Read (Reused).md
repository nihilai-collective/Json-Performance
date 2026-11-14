
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1966.18 | 1.5029 | 118.755ms | 1691 | 1280 | 194496 | 820.2 | 2.26933 | 1(Win) | true |
| Glaze | 1894.35 | 0.903832 | 110.257ms | 1691 | 2560 | 151559 | 851.3 | 0.688287 | 2(Loss) | true |
| Jsonifier (two-stage) | 1615.25 | 1.23176 | 119.265ms | 1691 | 40 | 6049.48 | 998.4 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1454.16 | 0.80317 | 133.457ms | 1691 | 1280 | 101552 | 1109 | 0.341481 | 4(Loss) | true |
| simdjson (reflection) | 1325 | 0.694224 | 147.165ms | 1691 | 2560 | 182765 | 1217.1 | 0.449861 | 5(Loss) | true |
