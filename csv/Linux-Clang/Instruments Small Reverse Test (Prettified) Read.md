
----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 903.572 | 0.0534408 | 1559.23ms | 7932 | 80 | 1601.31 | 8371.83 | 0.00358332 | 5.73012 | 24.4981 | 4.84279 | 0.00500662 | 3.30938e-05 | 1.5759e-06 | 1(Win) | true |
| simdjson (ondemand) | 415.722 | 0.0644349 | 2558.15ms | 7932 | 640 | 87979.9 | 18196.2 | 0.0685796 | 12.3972 | 61.3158 | 11.0202 | 0.0223917 | 3.95944e-05 | 1.69409e-05 | 2(Loss) | true |
