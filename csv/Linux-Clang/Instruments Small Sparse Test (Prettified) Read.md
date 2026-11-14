
----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6073.73 | 0.0912125 | 854.175ms | 7932 | 1280 | 1651.86 | 1245.45 | 0.192018 | 0.861618 | 3.81531 | 0.432048 | 0.00100109 | 3.0533e-05 | 1.52665e-05 | 1(Win) | true |
| Jsonifier (generic) | 6028.81 | 0.101959 | 853.927ms | 7932 | 30 | 49.0989 | 1254.73 | 0.0824227 | 0.866293 | 3.65721 | 0.483737 | 0.000760632 | 1.68095e-05 | 1.68095e-05 | 2(Loss) | true |
