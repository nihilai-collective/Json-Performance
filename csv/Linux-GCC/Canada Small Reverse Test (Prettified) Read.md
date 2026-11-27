
----
### Canada Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1677.91 | 0.0235174 | 1386.32ms | 11579 | 4890 | 11713.6 | 6581.14 | 0.198797 | 3.07486 | 15.1309 | 2.72459 | 0.00181951 | 2.49199e-05 | 8.54802e-06 | 1(Win) | true |
| Jsonifier (generic) | 1622.25 | 0.0481761 | 1410.2ms | 11579 | 1280 | 13765.1 | 6806.96 | 0.102769 | 3.15804 | 14.5622 | 2.85992 | 0.00208554 | 2.56391e-05 | 1.09303e-05 | 2(Loss) | true |
