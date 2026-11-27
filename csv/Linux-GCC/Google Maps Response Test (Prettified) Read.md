
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14656.7 | 0.109946 | 878.425ms | 25388 | 30 | 98.9609 | 1651.93 | 0.0282417 | 0.360153 | 1.85158 | 0.103277 | 4.46405e-05 | 2.62591e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 14003.2 | 0.0804574 | 882.937ms | 25388 | 40 | 77.4096 | 1729.03 | 0.101799 | 0.376562 | 1.97822 | 0.0768867 | 0.00012112 | 2.95415e-06 | 9.84717e-07 | 2(Loss) | true |
