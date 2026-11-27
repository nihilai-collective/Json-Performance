
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1574.17 | 0.105979 | 854.094ms | 2158 | 80 | 153.579 | 1307.38 | 0.0477829 | 3.37456 | 11.7822 | 2.22614 | 0.000463392 | 1.73772e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1537.44 | 0.099977 | 857.003ms | 2158 | 4890 | 8758.27 | 1338.61 | 0.174917 | 3.48697 | 12.0806 | 2.24467 | 0.000642494 | 0.000240604 | 0.00012196 | 2(Loss) | true |
