
----
### Google Maps Response Test (Minified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10312.6 | 0.0592471 | 820.69ms | 11812 | 2560 | 1072.21 | 1092.33 | 0.0430732 | 0.517449 | 2.54004 | 0.128175 | 8.51888e-05 | 8.00298e-06 | 1.32281e-07 | 1(Win) | true |
| simdjson (stage-1) | 9556.65 | 0.0801476 | 827.123ms | 11812 | 2560 | 2284.85 | 1178.74 | 0.0280942 | 0.556614 | 2.58872 | 0.116577 | 8.53541e-05 | 1.05163e-05 | 2.14956e-06 | 2(Loss) | true |
