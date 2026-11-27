
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1492.63 | 0.107475 | 4180.41ms | 65103 | 4890 | 9.77298e+06 | 41595.9 | 0.0367089 | 1.6576 | 1(Win) | true |
| simdjson (ondemand) | 1164.1 | 0.0501431 | 5357.61ms | 65103 | 4890 | 3.49744e+06 | 53334.7 | 0.132212 | 2.12575 | 2(Loss) | true |
