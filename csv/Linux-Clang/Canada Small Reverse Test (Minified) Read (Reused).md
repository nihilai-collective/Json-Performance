
----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 797.593 | 0.101343 | 1369.77ms | 4630 | 40 | 1259.07 | 5536.05 | 0.133191 | 6.38644 | 31.6432 | 5.98877 | 0.00230562 | 1.61987e-05 | 5.39957e-06 | 1(Win) | true |
| simdjson (ondemand) | 789.979 | 0.236095 | 1384.75ms | 4630 | 160 | 27862.8 | 5589.41 | 0.0432926 | 6.42984 | 32.1689 | 5.62916 | 0.00218143 | 3.64471e-05 | 1.34989e-06 | 2(Loss) | true |
