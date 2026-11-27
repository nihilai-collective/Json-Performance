
----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1667.14 | 0.145479 | 9273.54ms | 5212421 | 160 | 3.01063e+09 | 2.98173e+06 | 0.0650539 | 3.04195 | 14.1457 | 2.80467 | 0.0100816 | 0.101531 | 0.00250477 | 1(Win) | true |
| simdjson (ondemand) | 1616.85 | 0.1226 | 9606.99ms | 5212421 | 80 | 1.13661e+09 | 3.07446e+06 | 0.00482093 | 3.12887 | 14.7176 | 2.67159 | 0.0103475 | 0.121139 | 0.00146305 | 2(Loss) | true |
