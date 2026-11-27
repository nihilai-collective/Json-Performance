
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1364.62 | 0.295941 | 7892.6ms | 7351818 | 40 | 9.24773e+09 | 5.13787e+06 | 0.515548 | 3.73905 | 15.7134 | 3.38497 | 0.0115037 | 0.186228 | 0.00474981 | 1(Win) | true |
| simdjson (ondemand) | 922.236 | 0.22202 | 5382.55ms | 7351818 | 30 | 8.54697e+09 | 7.60243e+06 | 0.367149 | 5.51373 | 26.28 | 5.27001 | 0.0104686 | 0.435943 | 0.00671931 | 2(Loss) | true |
