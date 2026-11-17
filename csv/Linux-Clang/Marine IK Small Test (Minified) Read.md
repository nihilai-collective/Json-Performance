
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 862.63 | 0.162311 | 516.196ms | 4604 | 4890 | 333754 | 5089.92 | 0.0495685 | 2.85386 | 1(Win) | true |
| Jsonifier (two-stage) | 802.247 | 0.238099 | 552.985ms | 4604 | 1280 | 217361 | 5473.02 | 0.36582 | 3.06956 | 2(Loss) | true |
| Glaze | 583.756 | 0.173562 | 752.59ms | 4604 | 2560 | 436270 | 7521.49 | 0.116255 | 4.22507 | 3(Loss) | true |
| simdjson (ondemand) | 509.082 | 0.106963 | 867.441ms | 4604 | 4890 | 416175 | 8624.78 | 1.0437 | 4.84778 | 4(Loss) | true |
