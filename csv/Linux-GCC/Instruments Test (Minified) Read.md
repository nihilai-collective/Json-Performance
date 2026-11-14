
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1663.39 | 0.040514 | 6957.46ms | 108313 | 1280 | 810204 | 62099.4 | 0.0142005 | 3.09119 | 13.8842 | 2.79489 | 0.00364478 | 3.73339e-05 | 2.84188e-05 | 1(Win) | true |
| simdjson (ondemand) | 1491.63 | 0.057927 | 7626.3ms | 108313 | 640 | 1.02987e+06 | 69250 | 0.182929 | 3.3919 | 15.3163 | 2.5203 | 0.00700986 | 7.78992e-06 | 4.16905e-06 | 2(Loss) | true |
