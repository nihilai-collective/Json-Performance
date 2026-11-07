
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 927.329 | 0.0924189 | 480.836ms | 4604 | 30 | 574.441 | 4734.8 | 0.16166 | 2.65474 | 1(Win) | true |
| Jsonifier (two-stage) | 833.293 | 0.208428 | 529.18ms | 4604 | 2560 | 308766 | 5269.12 | 0.387703 | 2.9554 | 2(Loss) | true |
| Glaze | 666.635 | 0.213335 | 660.732ms | 4604 | 1280 | 252713 | 6586.39 | 0.137106 | 3.69642 | 3(Loss) | true |
| simdjson (ondemand) | 544.86 | 0.0853615 | 804.26ms | 4604 | 40 | 1892.71 | 8058.43 | 0.0657094 | 4.53044 | 4(Loss) | true |
