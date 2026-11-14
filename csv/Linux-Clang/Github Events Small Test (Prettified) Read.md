
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1536.8 | 0.0381747 | 852.61ms | 2158 | 2560 | 669.048 | 1339.16 | 0.0713408 | 3.45288 | 12.2275 | 2.3633 | 0.000467374 | 7.36721e-05 | 7.60253e-06 | 1(Win) | true |
| simdjson (ondemand) | 1490.65 | 0.0346303 | 856.315ms | 2158 | 4890 | 1117.82 | 1380.62 | 0.0443022 | 3.5577 | 13.4194 | 2.29611 | 0.000479597 | 9.31522e-05 | 1.89526e-05 | 2(Loss) | true |
