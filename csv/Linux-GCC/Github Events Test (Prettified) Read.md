
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1493.8 | 0.0707019 | 4897.64ms | 65103 | 640 | 552660 | 41563.1 | 0.000203005 | 3.43261 | 11.8627 | 2.28831 | 0.0105017 | 3.27606e-05 | 1.53363e-05 | 1(Win) | true |
| simdjson (ondemand) | 1256.36 | 0.0273778 | 5672.09ms | 65103 | 4890 | 895112 | 49418.1 | 0.0760289 | 4.08733 | 14.77 | 2.85788 | 0.0169242 | 4.43595e-05 | 1.44493e-05 | 2(Loss) | true |
