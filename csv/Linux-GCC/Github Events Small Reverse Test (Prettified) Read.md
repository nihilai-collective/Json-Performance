
----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1045.83 | 0.138112 | 902.782ms | 2158 | 40 | 295.464 | 1967.85 | 0.00762311 | 5.02298 | 17.2159 | 3.46803 | 0.00282669 | 9.26784e-05 | 3.47544e-05 | 1(Win) | true |
| simdjson (ondemand) | 930.039 | 0.0492091 | 936.528ms | 2158 | 2560 | 3035.51 | 2212.84 | 0.315669 | 5.65797 | 21.962 | 4.25533 | 0.000972218 | 9.34025e-05 | 2.08164e-05 | 2(Loss) | true |
