
----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1068.58 | 0.0262091 | 910.627ms | 2158 | 4890 | 1245.94 | 1925.94 | 0.000833323 | 4.92059 | 17.2706 | 3.49537 | 0.00289473 | 9.30575e-05 | 1.6394e-05 | 1(Win) | true |
| simdjson (ondemand) | 865.697 | 0.0534758 | 956.337ms | 2158 | 1280 | 2068.7 | 2377.31 | 0.0397153 | 6.0504 | 23.766 | 4.22475 | 0.00275392 | 7.2043e-05 | 1.4843e-05 | 2(Loss) | true |
