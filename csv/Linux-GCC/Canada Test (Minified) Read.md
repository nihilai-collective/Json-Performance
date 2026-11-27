
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 807.213 | 0.0751384 | 7703.72ms | 2090234 | 160 | 5.5088e+08 | 2.46949e+06 | 0.227759 | 6.28899 | 30.4159 | 5.62526 | 0.022817 | 0.103605 | 0.000552262 | 1(Win) | true |
| Jsonifier (generic) | 781.212 | 0.124224 | 8027.28ms | 2090234 | 40 | 4.01904e+08 | 2.55168e+06 | 1.26786 | 6.47651 | 30.3131 | 6.22188 | 0.0269788 | 0.103639 | 0.00080961 | 2(Loss) | true |
