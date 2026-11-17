
----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 608.816 | 0.038705 | 9142.44ms | 108313 | 1280 | 5.51992e+06 | 169666 | 0.0873839 | 8.39852 | 37.7457 | 7.55556 | 0.0107603 | 1.30265e-05 | 6.20309e-06 | 1(Win) | true |
| simdjson (ondemand) | 256.787 | 0.111686 | 5253.28ms | 108313 | 80 | 1.61473e+07 | 402260 | 0.0744454 | 19.9526 | 90.0121 | 18.3458 | 0.0812558 | 2.76975e-05 | 1.95037e-05 | 2(Loss) | true |
