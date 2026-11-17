
----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1505.98 | 0.0769763 | 1319.09ms | 9378 | 80 | 1671.81 | 5938.7 | 0.000841928 | 3.44481 | 14.9292 | 2.91629 | 0.00597675 | 4.79846e-05 | 2.26594e-05 | 1(Win) | true |
| simdjson (ondemand) | 1372.3 | 0.0373762 | 1371.46ms | 9378 | 1280 | 7594.96 | 6517.21 | 0.037235 | 3.71207 | 16.0448 | 2.86778 | 0.00470166 | 2.51586e-05 | 9.91349e-06 | 2(Loss) | true |
