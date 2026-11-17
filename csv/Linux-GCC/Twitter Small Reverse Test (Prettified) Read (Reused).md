
----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1043.87 | 0.0442804 | 1071.23ms | 3770 | 2560 | 5954.55 | 3444.24 | 0.131756 | 5.01372 | 20.3553 | 3.82044 | 0.00153359 | 5.61588e-05 | 1.55421e-05 | 1(Win) | true |
| simdjson (ondemand) | 545.27 | 0.0314066 | 1383.92ms | 3770 | 2560 | 10978.5 | 6593.71 | 0.0420796 | 9.50002 | 43.4836 | 8.68886 | 0.00927802 | 5.98889e-05 | 2.35204e-05 | 2(Loss) | true |
