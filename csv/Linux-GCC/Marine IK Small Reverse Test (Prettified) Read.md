
----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1190.73 | 0.0443125 | 2194.16ms | 18245 | 1280 | 53669.4 | 14612.8 | 0.0216908 | 4.33506 | 17.8653 | 3.75588 | 0.00543792 | 4.86435e-05 | 2.40648e-05 | 1(Win) | true |
| simdjson (ondemand) | 912.506 | 0.0771962 | 2631.53ms | 18245 | 640 | 138672 | 19068.1 | 0.155499 | 5.61953 | 27.5252 | 5.58772 | 0.00642034 | 2.45787e-05 | 9.50603e-06 | 2(Loss) | true |
