
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 17111.4 | 0.0987056 | 1070.44ms | 65103 | 30 | 384.8 | 3628.4 | 0.0211251 | 0.304772 | 1.54139 | 0.0770779 | 0.00021402 | 1.02402e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 16396.4 | 0.050725 | 1095.64ms | 65103 | 40 | 147.574 | 3786.62 | 0.0037411 | 0.317578 | 1.68504 | 0.0622398 | 3.07206e-05 | 2.30404e-06 | 0 | 2(Loss) | true |
