
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1373.77 | 0.121926 | 7703.04ms | 7351818 | 80 | 3.09776e+09 | 5.10367e+06 | 0.309632 | 3.68324 | 17.0514 | 3.3956 | 0.0103912 | 0.186412 | 0.00172323 | 1(Win) | true |
| simdjson (ondemand) | 896.034 | 0.213482 | 5538.2ms | 7351818 | 40 | 1.11616e+10 | 7.82475e+06 | 1.39708 | 5.69212 | 27.194 | 5.33205 | 0.0120835 | 0.43583 | 0.00708829 | 2(Loss) | true |
