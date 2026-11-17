
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1864.34 | 0.051782 | 1142.15ms | 8150 | 1280 | 5965.28 | 4169 | 0.0440185 | 2.78877 | 10.975 | 2.04258 | 0.0027963 | 3.24962e-05 | 8.14801e-06 | 1(Win) | true |
| simdjson (ondemand) | 1706.76 | 0.0354426 | 1184.85ms | 8150 | 2560 | 6669.04 | 4553.92 | 0.0623649 | 3.03668 | 12.3243 | 2.0919 | 0.00212898 | 3.11541e-05 | 1.06883e-05 | 2(Loss) | true |
