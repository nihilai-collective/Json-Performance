
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2171.81 | 0.0956268 | 1022.69ms | 6701 | 1280 | 10134.5 | 2942.5 | 0.0267701 | 2.39806 | 9.24101 | 1.44844 | 0.00058655 | 4.94329e-05 | 2.4833e-05 | 1(Win) | true |
| Glaze | 2070.7 | 0.0565067 | 1032.43ms | 6701 | 2560 | 7785.5 | 3086.19 | 0.0423689 | 2.51646 | 10.4195 | 2.10775 | 0.000245649 | 6.54053e-05 | 3.44515e-05 | 2(Loss) | true |
| simdjson (reflection) | 2044.27 | 0.0754918 | 1042.66ms | 6701 | 2560 | 14257.5 | 3126.09 | 0.0201639 | 2.55047 | 9.82182 | 1.61871 | 0.000968605 | 0.00011717 | 6.38897e-05 | 3(Loss) | true |
| Jsonifier | 1975.44 | 0.0536578 | 1048.38ms | 6701 | 320 | 964.2 | 3235.01 | 0.0716254 | 2.64131 | 9.25131 | 1.79719 | 0.00149744 | 1.67885e-05 | 1.86539e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1710.32 | 0.0432417 | 1100.74ms | 6701 | 4890 | 12765.5 | 3736.47 | 0.199403 | 3.03202 | 10.8505 | 1.99985 | 0.00128321 | 7.09841e-05 | 3.43629e-05 | 5(Loss) | true |
