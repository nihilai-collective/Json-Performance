
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2213.77 | 0.153132 | 351.02ms | 8051 | 4890 | 137936 | 3468.3 | 0.637355 | 1.10919 | 1(Win) | true |
| Jsonifier | 1759.35 | 0.270401 | 441.357ms | 8051 | 2560 | 356492 | 4364.12 | 0.265288 | 1.39814 | 2(Loss) | true |
| Glaze | 1530.53 | 0.458214 | 511.558ms | 8051 | 640 | 338167 | 5016.58 | 0.349208 | 1.60883 | 3(Loss) | true |
| simdjson (ondemand) | 1318.26 | 0.117828 | 586.471ms | 8051 | 80 | 3767.75 | 5824.35 | 0.112761 | 1.86846 | 4(Loss) | true |
