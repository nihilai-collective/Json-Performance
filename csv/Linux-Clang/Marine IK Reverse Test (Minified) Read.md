
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 384.474 | 0.218971 | 6777.57ms | 1834197 | 80 | 7.93999e+09 | 4.54966e+06 | 0.251996 | 13.1227 | 64.1942 | 13.4199 | 0.0385662 | 0.343896 | 0.020975 | 1(Win) | true |
| simdjson (ondemand) | 266.716 | 0.0994834 | 9884.98ms | 1834197 | 40 | 1.70277e+09 | 6.55839e+06 | 0.22056 | 18.975 | 105.333 | 21.2119 | 0.0494483 | 0.788908 | 0.00124125 | 2(Loss) | true |
