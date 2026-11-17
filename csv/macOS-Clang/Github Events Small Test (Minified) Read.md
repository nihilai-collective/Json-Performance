
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1655.09 | 0.0890036 | 100.175ms | 1691 | 640 | 481.324 | 974.364 | 0.321915 | 1(Win) | true |
| Glaze | 1378.04 | 0.184933 | 120.295ms | 1691 | 160 | 749.402 | 1170.26 | 0.0427437 | 2(Loss) | true |
| Jsonifier (two-stage) | 1209.88 | 0.146564 | 142.267ms | 1691 | 160 | 610.626 | 1332.91 | 0.923104 | 3(Loss) | true |
| simdjson (ondemand) | 889.915 | 0.342674 | 176.793ms | 1691 | 2560 | 98717.1 | 1812.15 | 0.931861 | 4(Loss) | true |
