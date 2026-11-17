
----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1301.02 | 0.0472029 | 2157.03ms | 18245 | 640 | 25505.8 | 13374 | 0.118839 | 3.96999 | 17.4935 | 3.60565 | 0.00487976 | 1.85839e-05 | 4.11072e-06 | 1(Win) | true |
| simdjson (ondemand) | 980.752 | 0.120367 | 2609.21ms | 18245 | 40 | 18240.7 | 17741.3 | 0.00624759 | 5.26244 | 27.6597 | 5.37846 | 0.00526994 | 3.28857e-05 | 1.09619e-05 | 2(Loss) | true |
