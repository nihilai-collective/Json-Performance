
----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4468.18 | 0.119938 | 927.331ms | 9378 | 160 | 922.126 | 2001.61 | 0.00874219 | 1.17622 | 5.4517 | 0.880145 | 0.00085506 | 1.26626e-05 | 6.66453e-06 | 1(Win) | true |
| simdjson (ondemand) | 3804.42 | 0.0723285 | 966.199ms | 9378 | 640 | 1850.31 | 2350.84 | 0.164365 | 1.37615 | 6.00768 | 0.920346 | 0.000937867 | 1.44954e-05 | 1.16629e-06 | 2(Loss) | true |
