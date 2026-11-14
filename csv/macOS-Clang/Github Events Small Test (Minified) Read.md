
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1711.51 | 0.21317 | 97.6391ms | 1691 | 1280 | 5164.06 | 942.247 | 0.36481 | 1(Win) | true |
| Glaze | 1344.74 | 0.145441 | 124.118ms | 1691 | 320 | 973.484 | 1199.23 | 0.37114 | 2(Loss) | true |
| Jsonifier (two-stage) | 1256.65 | 0.326721 | 145.461ms | 1691 | 30 | 527.39 | 1283.3 | 0.00779302 | 3(Loss) | true |
| simdjson (ondemand) | 1066.59 | 0.209823 | 156.888ms | 1691 | 80 | 805.177 | 1511.99 | 0.0339073 | 4(Loss) | true |
