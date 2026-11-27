
----
### Marine IK Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1214.86 | 0.0717336 | 2170.37ms | 18245 | 1280 | 135110 | 14322.4 | 0.083562 | 4.23077 | 17.7206 | 3.76142 | 0.00482992 | 6.94111e-05 | 4.25202e-05 | 1(Win) | true |
| simdjson (ondemand) | 907.137 | 0.0294846 | 2665.73ms | 18245 | 2560 | 81879.1 | 19181 | 0.0348897 | 5.67276 | 27.5733 | 5.59677 | 0.00619476 | 9.88499e-05 | 7.04388e-05 | 2(Loss) | true |
