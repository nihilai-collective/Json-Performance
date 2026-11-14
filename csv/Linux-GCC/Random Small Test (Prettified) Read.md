
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2198.95 | 0.0418148 | 1077.39ms | 8051 | 4890 | 10424.1 | 3491.68 | 0.0424555 | 2.35273 | 10.0946 | 1.62464 | 0.00130411 | 7.21881e-05 | 3.34778e-05 | 1(Win) | true |
| Jsonifier | 1920.37 | 0.0513771 | 1126.25ms | 8051 | 2560 | 10802.1 | 3998.2 | 0.127975 | 2.70778 | 11.0467 | 2.07987 | 0.00158511 | 4.70633e-05 | 2.00383e-05 | 2(Loss) | true |
| simdjson (reflection) | 1909.61 | 0.0603617 | 1136.75ms | 8051 | 2560 | 15079 | 4020.72 | 0.0905034 | 2.68794 | 10.5814 | 1.67557 | 0.00207588 | 4.18232e-05 | 1.88738e-05 | 3(Loss) | true |
| Glaze | 1622.67 | 0.0678669 | 1201.54ms | 8051 | 1280 | 13199.8 | 4731.73 | 0.0401705 | 3.19714 | 13.5512 | 2.60241 | 0.00377049 | 3.0858e-05 | 7.4719e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1610.54 | 0.113328 | 1203.61ms | 8051 | 30 | 875.689 | 4767.37 | 0.0139859 | 3.22654 | 11.5321 | 1.87281 | 0.00303482 | 3.72625e-05 | 4.14027e-06 | 5(Loss) | true |
