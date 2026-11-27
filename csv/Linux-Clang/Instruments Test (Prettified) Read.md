
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2341.63 | 0.0676252 | 8233.92ms | 183677 | 160 | 409460 | 74806.1 | 0.0656544 | 2.15804 | 9.4263 | 1.71097 | 0.00229006 | 1.01401e-05 | 6.22696e-06 | 1(Win) | true |
| simdjson (ondemand) | 2316.49 | 0.0468165 | 8300.31ms | 183677 | 1280 | 1.6042e+06 | 75618 | 0.332857 | 2.19393 | 10.2182 | 1.46798 | 0.00403149 | 1.37937e-05 | 9.65945e-06 | 2(Loss) | true |
