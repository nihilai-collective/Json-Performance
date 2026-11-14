
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2042.76 | 0.0682468 | 1312.64ms | 9578 | 2560 | 23840.8 | 4471.55 | 0.02902 | 2.51521 | 13.3639 | 2.0283 | 0.00157449 | 4.49843e-05 | 2.22678e-05 | 1(Win) | true |
| Jsonifier (generic) | 1733.45 | 0.0584618 | 1383.46ms | 9578 | 2560 | 24294.6 | 5269.42 | 0.208734 | 2.95614 | 14.9192 | 2.39079 | 0.00307374 | 4.44541e-05 | 2.21047e-05 | 2(Loss) | true |
