
----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14341 | 0.103218 | 750.363ms | 4300 | 40 | 3.48462 | 285.95 | 0.0291341 | 0.410244 | 0.951395 | 0.134884 | 0.000232558 | 2.90698e-05 | 0 | 1(Win) | true |
| Glaze | 4249.08 | 0.274444 | 819.389ms | 4300 | 2560 | 17959.5 | 965.103 | 0.677184 | 1.26281 | 3.03163 | 0.477209 | 0.000233285 | 5.07812e-05 | 2.33467e-05 | 2(Loss) | true |
| simdjson (reflection) | 553.611 | 0.128988 | 1479.46ms | 4300 | 1280 | 116851 | 7407.37 | 0.036205 | 9.34268 | 34.0716 | 7.50791 | 0.0103156 | 0.000334302 | 0.000213481 | 3(Loss) | true |
