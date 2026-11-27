
----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2699.01 | 0.0895383 | 648.55ms | 18245 | 30 | 999.582 | 6446.73 | 0.186825 | 0.913874 | 1(Win) | true |
| Jsonifier | 2555.69 | 0.0878715 | 699.645ms | 18245 | 30 | 1073.72 | 6808.27 | 0.230559 | 0.965127 | 2(Loss) | true |
| simdjson (reflection) | 2342.77 | 0.180183 | 760.466ms | 18245 | 40 | 7163.33 | 7427 | 0.0479999 | 1.05317 | 3(Loss) | true |
| simdjson (ondemand) | 1823.55 | 0.11657 | 939.065ms | 18245 | 30 | 3711.46 | 9541.7 | 0.695218 | 1.35393 | 4(Loss) | true |
| Glaze | 1791.94 | 0.0824252 | 972.465ms | 18245 | 30 | 1921.69 | 9710.03 | 0.0628611 | 1.37791 | 5(Loss) | true |
