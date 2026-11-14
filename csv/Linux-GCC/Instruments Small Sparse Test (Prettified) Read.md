
----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6445.18 | 0.0471269 | 851.833ms | 7932 | 320 | 97.9003 | 1173.67 | 0.0441793 | 0.829521 | 3.84102 | 0.433056 | 0.000758006 | 1.10313e-05 | 3.93974e-07 | 1(Win) | true |
| Jsonifier (generic) | 6321.52 | 0.126848 | 830.748ms | 7932 | 2560 | 5898.31 | 1196.63 | 0.0659945 | 0.842636 | 3.6852 | 0.463944 | 0.000884865 | 9.94784e-06 | 2.01912e-06 | 2(Loss) | true |
