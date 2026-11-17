
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11478.6 | 0.026321 | 1623.85ms | 108313 | 2560 | 14362.5 | 8998.96 | 0.128582 | 0.450512 | 2.40346 | 0.118518 | 1.89591e-05 | 1.51831e-06 | 4.25561e-07 | 1(Win) | true |
| simdjson (stage-1) | 10073.6 | 0.0181241 | 1744.03ms | 108313 | 4890 | 16889.3 | 10254.1 | 0.0634332 | 0.5125 | 2.45259 | 0.108879 | 3.43623e-05 | 3.5193e-06 | 2.20334e-06 | 2(Loss) | true |
