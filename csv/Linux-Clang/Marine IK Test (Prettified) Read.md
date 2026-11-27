
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22225.8 | 0.085575 | 8144.97ms | 7351818 | 160 | 1.16597e+07 | 315455 | 0.0116564 | 0.111385 | 1(Win) | true |
| simdjson (stage-1) | 20284.3 | 0.184235 | 8946.45ms | 7351818 | 40 | 1.62209e+07 | 345649 | 0.0816257 | 0.122047 | 2(Loss) | true |
