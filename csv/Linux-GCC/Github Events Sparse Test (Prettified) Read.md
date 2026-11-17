
----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8516.47 | 0.0320947 | 1455ms | 65103 | 2560 | 14014.9 | 7290.23 | 0.030436 | 0.605921 | 2.85564 | 0.339938 | 0.000617555 | 3.28806e-06 | 4.98009e-07 | 1(Win) | true |
| simdjson (ondemand) | 7714.7 | 0.0389267 | 1526.59ms | 65103 | 2560 | 25124.6 | 8047.89 | 0.00345114 | 0.670274 | 3.05786 | 0.356604 | 0.000705229 | 2.92805e-06 | 3.54006e-07 | 2(Loss) | true |
