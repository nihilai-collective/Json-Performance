
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 432.35 | 0.102472 | 6167.24ms | 1834197 | 30 | 5.15651e+08 | 4.04586e+06 | 0.329917 | 5.72636 | 1(Win) | true |
| simdjson (ondemand) | 228.548 | 0.0930966 | 5386.97ms | 1834197 | 40 | 2.03079e+09 | 7.65366e+06 | 0.80227 | 10.8323 | 2(Loss) | true |
