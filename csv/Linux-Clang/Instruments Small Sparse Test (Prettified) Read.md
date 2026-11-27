
----
### Instruments Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6607.47 | 0.0527618 | 845.124ms | 7932 | 4890 | 1784.2 | 1144.85 | 0.0408758 | 0.805685 | 3.57426 | 0.48651 | 0.000513903 | 3.44699e-05 | 1.4747e-05 | 1(Win) | true |
| simdjson (ondemand) | 6211.48 | 0.0399075 | 844.088ms | 7932 | 1280 | 302.338 | 1217.83 | 0.100295 | 0.85788 | 3.81228 | 0.432426 | 0.000952333 | 1.60544e-05 | 4.82618e-06 | 2(Loss) | true |
