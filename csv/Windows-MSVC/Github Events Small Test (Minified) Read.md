
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1054.46 | 0.178866 | 164.703ms | 1691 | 320 | 2394.59 | 1529.38 | 0 | 2.30363 | 1(Win) | true |
| Jsonifier | 910.145 | 0.200385 | 181.961ms | 1691 | 320 | 4034.09 | 1771.88 | 0.141293 | 2.67494 | 2(Loss) | true |
| Jsonifier (two-stage) | 827.719 | 0.350502 | 204.683ms | 1691 | 4890 | 228041 | 1948.32 | 0.157996 | 2.94351 | 3(Loss) | true |
| simdjson (ondemand) | 539.804 | 0.333534 | 310.998ms | 1691 | 80 | 7943.04 | 2987.5 | 0.335852 | 4.55727 | 4(Loss) | true |
