
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11418.7 | 0.108195 | 1631.38ms | 108313 | 160 | 15327.1 | 9046.14 | 0.0611131 | 0.452618 | 2.40346 | 0.118518 | 5.86841e-05 | 2.48123e-06 | 9.80953e-07 | 1(Win) | true |
| simdjson (stage-1) | 10068.3 | 0.0282564 | 1745.21ms | 108313 | 30 | 252.116 | 10259.4 | 0.00844822 | 0.51395 | 2.45259 | 0.108879 | 9.29405e-05 | 1.53875e-06 | 0 | 2(Loss) | true |
