
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2070.45 | 0.0708563 | 136.509ms | 2889 | 160 | 142.247 | 1330.71 | 0.0305196 | 1.16995 | 1(Win) | true |
| Glaze | 2044.85 | 0.343375 | 137.615ms | 2889 | 2560 | 54795.8 | 1347.37 | 0.012207 | 1.18518 | 2(Loss) | true |
| Jsonifier (two-stage) | 2023.55 | 0.212621 | 141.51ms | 2889 | 40 | 335.228 | 1361.55 | 0.357485 | 1.19808 | 3(Loss) | true |
| simdjson (ondemand) | 968.977 | 0.273048 | 290.957ms | 2889 | 1280 | 77153.8 | 2843.38 | 0.437912 | 2.53006 | 4(Loss) | true |
