
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1058.63 | 0.365725 | 502.535ms | 4604 | 1280 | 294512 | 4147.55 | 0.100537 | 2.32329 | 1(Win) | true |
| Jsonifier (two-stage) | 950.309 | 0.847438 | 564.345ms | 4604 | 320 | 490576 | 4620.3 | 0.114097 | 2.5893 | 2(Loss) | true |
| Glaze | 652.391 | 0.143367 | 746.785ms | 4604 | 4890 | 455264 | 6730.19 | 0.107746 | 3.77909 | 3(Loss) | true |
| simdjson (ondemand) | 548.715 | 0.317603 | 884.657ms | 4604 | 4890 | 3.1583e+06 | 8001.81 | 0.191518 | 4.49506 | 4(Loss) | true |
