
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2697.46 | 0.264239 | 283.125ms | 7932 | 4890 | 268509 | 2804.33 | 0.0347356 | 1(Win) | true |
| Jsonifier (two-stage) | 2356.83 | 0.207275 | 324.445ms | 7932 | 4890 | 216428 | 3209.63 | 1.40892 | 2(Loss) | true |
| simdjson (reflection) | 1917.16 | 0.150462 | 399.644ms | 7932 | 4890 | 172351 | 3945.7 | 0.0051152 | 3(Loss) | true |
| Glaze | 1864.8 | 0.184942 | 409.177ms | 7932 | 2560 | 144083 | 4056.5 | 0.101175 | 4(Loss) | true |
| simdjson (ondemand) | 1525.77 | 0.237958 | 523.665ms | 7932 | 4890 | 680609 | 4957.87 | 0.564247 | 5(Loss) | true |
