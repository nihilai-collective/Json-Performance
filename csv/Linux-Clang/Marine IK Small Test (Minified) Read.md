
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 976.252 | 0.0887559 | 456.964ms | 4604 | 40 | 637.384 | 4497.52 | 0.177006 | 2.52022 | 1(Win) | true |
| Jsonifier (two-stage) | 872.444 | 0.205371 | 521.543ms | 4604 | 1280 | 136737 | 5032.66 | 0.358716 | 2.82205 | 2(Loss) | true |
| Glaze | 684.228 | 0.123933 | 654.341ms | 4604 | 30 | 1897.41 | 6417.03 | 0.0899458 | 3.60406 | 3(Loss) | true |
| simdjson (ondemand) | 546.033 | 0.0499373 | 817.518ms | 4604 | 80 | 1289.95 | 8041.11 | 0.115322 | 4.51988 | 4(Loss) | true |
