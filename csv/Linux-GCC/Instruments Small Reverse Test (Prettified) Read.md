
----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 845.779 | 0.0985697 | 1612.06ms | 7932 | 80 | 6217.68 | 8943.88 | 0.0539767 | 6.11956 | 24.3567 | 4.87595 | 0.00573626 | 2.04866e-05 | 4.72769e-06 | 1(Win) | true |
| simdjson (ondemand) | 424.373 | 0.0431565 | 2509.29ms | 7932 | 1280 | 75748.3 | 17825.2 | 0.0674545 | 12.1445 | 55.6912 | 11.2751 | 0.0294873 | 5.04286e-05 | 1.52665e-05 | 2(Loss) | true |
