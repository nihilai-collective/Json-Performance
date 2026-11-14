
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2056.29 | 0.107632 | 8741.32ms | 5212421 | 30 | 2.03103e+08 | 2.41744e+06 | 0.0601493 | 2.45347 | 11.3279 | 1.78366 | 0.00989242 | 0.0511361 | 0.00120588 | 1(Win) | true |
| Jsonifier (generic) | 2037.17 | 0.0673113 | 8792.06ms | 5212421 | 80 | 2.15819e+08 | 2.44012e+06 | 0.119872 | 2.47877 | 11.7381 | 2.07614 | 0.00974707 | 0.0512011 | 0.000861039 | 2(Loss) | true |
