
----
### Stream Formats Small Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4006.12 | 0.0587317 | 5749.44ms | 16002592 | 40 | 2.00234e+08 | 3.80949e+06 | 0.1174 | 1.26455 | 7.26695 | 1.14523 | 0.000764386 | 0.0328342 | 0.00172639 | 1(Win) | true |
| simdjson (ondemand) | 3387.45 | 0.0658496 | 6764.2ms | 16002592 | 80 | 7.04094e+08 | 4.50524e+06 | 0.161763 | 1.49677 | 7.97793 | 1.16694 | 0.00105343 | 0.0351108 | 0.00335036 | 2(Loss) | true |
