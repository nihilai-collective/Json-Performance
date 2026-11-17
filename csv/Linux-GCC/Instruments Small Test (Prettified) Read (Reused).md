
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3485.89 | 0.0522725 | 951.195ms | 7932 | 4890 | 6292.06 | 2170.04 | 0.127348 | 1.47969 | 6.14183 | 0.980585 | 0.000785898 | 2.10635e-05 | 7.50242e-06 | 1(Win) | true |
| Jsonifier | 3006.88 | 0.0577638 | 986.184ms | 7932 | 4890 | 10326.5 | 2515.75 | 0.0301916 | 1.72393 | 6.29501 | 1.38944 | 0.00109128 | 4.05801e-05 | 2.03932e-05 | 2(Loss) | true |
| simdjson (reflection) | 2749.33 | 0.113488 | 1020.92ms | 7932 | 80 | 780.018 | 2751.41 | 0.175217 | 1.90119 | 7.87582 | 1.15431 | 0.000630358 | 3.46697e-05 | 2.20625e-05 | 3(Loss) | true |
| Glaze | 2528.81 | 0.0682555 | 1034.23ms | 7932 | 320 | 1334.01 | 2991.35 | 0.520543 | 2.0368 | 8.07526 | 1.55648 | 0.0019872 | 1.33951e-05 | 5.12166e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2295.66 | 0.0959033 | 1068.42ms | 7932 | 40 | 399.464 | 3295.15 | 0.0490861 | 2.23115 | 8.89788 | 1.5029 | 0.000690242 | 3.15179e-05 | 0 | 5(Loss) | true |
