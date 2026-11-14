
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22024.1 | 0.0820931 | 7941.7ms | 1834197 | 2560 | 1.0883e+07 | 79423.4 | 0.24935 | 0.112372 | 1(Win) | true |
| simdjson (stage-1) | 17659 | 0.100705 | 5095.08ms | 1834197 | 640 | 6.36855e+06 | 99055.8 | 0.0908589 | 0.140153 | 2(Loss) | true |
