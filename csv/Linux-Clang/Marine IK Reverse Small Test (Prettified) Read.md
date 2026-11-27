
----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2764.86 | 0.118846 | 635.795ms | 18245 | 4890 | 273539 | 6293.19 | 0.209277 | 0.891408 | 1(Win) | true |
| Jsonifier | 2333.76 | 0.180871 | 749.919ms | 18245 | 2560 | 465539 | 7455.7 | 0.0874613 | 1.05705 | 2(Loss) | true |
| simdjson (ondemand) | 1912.15 | 0.0495233 | 915.753ms | 18245 | 80 | 1624.63 | 9099.59 | 0.120053 | 1.29107 | 3(Loss) | true |
| Glaze | 1774.57 | 0.0966473 | 982.823ms | 18245 | 4890 | 439128 | 9805.09 | 0.0621737 | 1.39141 | 4(Loss) | true |
