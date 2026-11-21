
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2529.42 | 0.0439468 | 312.352ms | 8051 | 160 | 284.73 | 3035.49 | 0.21604 | 0.970562 | 1(Win) | true |
| Jsonifier | 2030.89 | 0.0380834 | 385.212ms | 8051 | 160 | 331.681 | 3780.63 | 0.103216 | 1.21061 | 2(Loss) | true |
| Glaze | 1707.03 | 0.040785 | 457.165ms | 8051 | 160 | 538.44 | 4497.89 | 0.192962 | 1.44232 | 3(Loss) | true |
| simdjson (ondemand) | 1392.83 | 0.18959 | 554.679ms | 8051 | 2560 | 279623 | 5512.52 | 0.0017007 | 1.76759 | 4(Loss) | true |
