
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 557.195 | 0.0338123 | 1507.44ms | 4604 | 1280 | 9086.89 | 7880.03 | 0.156703 | 9.28967 | 36.7168 | 7.45026 | 0.0103314 | 6.07488e-05 | 1.9684e-05 | 1(Win) | true |
| simdjson (ondemand) | 552.465 | 0.0240932 | 1534.51ms | 4604 | 2560 | 9386.17 | 7947.5 | 0.0933357 | 9.36797 | 38.0517 | 6.88003 | 0.012852 | 9.33292e-05 | 4.10648e-05 | 2(Loss) | true |
