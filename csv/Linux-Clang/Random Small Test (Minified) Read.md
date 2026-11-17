
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1678.58 | 0.0842437 | 298.256ms | 5094 | 80 | 475.554 | 2894.12 | 0.00259152 | 1.46145 | 1(Win) | true |
| Jsonifier (two-stage) | 1510.67 | 0.0797824 | 327.964ms | 5094 | 30 | 197.476 | 3215.8 | 0.156274 | 1.62528 | 2(Loss) | true |
| Glaze | 1185.5 | 0.0904846 | 412.525ms | 5094 | 30 | 412.464 | 4097.87 | 0.000813438 | 2.07461 | 3(Loss) | true |
| simdjson (ondemand) | 864.427 | 0.649135 | 579.563ms | 5094 | 160 | 212937 | 5619.93 | 0.157724 | 2.84892 | 4(Loss) | true |
