
----
### Github Events Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1109.03 | 0.0862698 | 6354.06ms | 65103 | 640 | 1.49284e+06 | 55983.2 | 0.0858638 | 4.61694 | 16.5847 | 3.26492 | 0.0144975 | 0.000364567 | 0.000282437 | 1(Win) | true |
| simdjson (ondemand) | 599.732 | 0.104675 | 5701.37ms | 65103 | 320 | 3.75774e+06 | 103525 | 0.122743 | 8.53434 | 30.2036 | 6.06528 | 0.0529291 | 6.24491e-05 | 3.68647e-05 | 2(Loss) | true |
