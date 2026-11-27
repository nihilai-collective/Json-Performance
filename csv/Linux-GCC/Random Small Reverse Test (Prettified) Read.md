
----
### Random Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1311.06 | 0.0702746 | 1315.73ms | 8150 | 160 | 2777.08 | 5928.38 | 0.184889 | 3.95592 | 16.9772 | 3.33509 | 0.00628911 | 9.89264e-05 | 5.44479e-05 | 1(Win) | true |
| simdjson (ondemand) | 776.795 | 0.0629785 | 1733.41ms | 8150 | 320 | 12706.8 | 10005.8 | 0.00596494 | 6.6539 | 27.7747 | 5.45473 | 0.0142742 | 4.33282e-05 | 1.61043e-05 | 2(Loss) | true |
