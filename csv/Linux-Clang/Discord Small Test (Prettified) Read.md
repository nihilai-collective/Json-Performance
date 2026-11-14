
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1856.99 | 0.225805 | 1064.47ms | 6701 | 30 | 1811.55 | 3441.37 | 0.017438 | 2.81681 | 11.1388 | 2.09327 | 0.00096503 | 6.96413e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1795.57 | 0.128849 | 1076.09ms | 6701 | 320 | 6729.61 | 3559.08 | 0.0793496 | 2.89893 | 11.5998 | 1.91076 | 0.000741494 | 4.10387e-05 | 1.95866e-05 | 2(Loss) | true |
