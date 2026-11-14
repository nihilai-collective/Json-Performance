
----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1079.03 | 0.0559074 | 6502.11ms | 65103 | 640 | 662301 | 57539.8 | 0.0845836 | 4.77021 | 16.9316 | 3.39064 | 0.014793 | 2.97605e-05 | 1.02242e-05 | 1(Win) | true |
| simdjson (ondemand) | 562.85 | 0.0655918 | 6003.5ms | 65103 | 1280 | 6.70077e+06 | 110308 | 0.00641213 | 9.08616 | 33.2686 | 5.9672 | 0.046913 | 6.04091e-05 | 3.13086e-05 | 2(Loss) | true |
