
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13574.6 | 0.167191 | 8746.86ms | 2251027 | 40 | 2.79636e+06 | 158145 | 0.0678717 | 0.378089 | 1.74254 | 0.110614 | 0.00222758 | 0.0248748 | 8.66271e-07 | 1(Win) | true |
| simdjson (stage-1) | 11823.2 | 0.612982 | 9737.36ms | 2251027 | 2560 | 3.17122e+09 | 181570 | 0.066391 | 0.432842 | 1.89627 | 0.0806455 | 0.000911878 | 0.0246696 | 5.68664e-07 | 2(Loss) | true |
