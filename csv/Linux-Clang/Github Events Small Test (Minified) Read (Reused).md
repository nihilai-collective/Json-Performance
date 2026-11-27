
----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3249.7 | 0.101151 | 59.1607ms | 1691 | 160 | 40.3145 | 496.25 | 0.0731013 | 0.723111 | 1(Win) | true |
| Jsonifier (two-stage) | 2522.96 | 0.647279 | 72.1003ms | 1691 | 1280 | 21910.8 | 639.194 | 0.0952441 | 0.942016 | 2(Loss) | true |
| Glaze | 2350.93 | 0.0890597 | 79.6028ms | 1691 | 160 | 59.716 | 685.969 | 0.084806 | 1.0127 | 3(Loss) | true |
| simdjson (ondemand) | 1734.52 | 0.080978 | 102.194ms | 1691 | 320 | 181.389 | 929.744 | 0.0718767 | 1.38572 | 4(Loss) | true |
