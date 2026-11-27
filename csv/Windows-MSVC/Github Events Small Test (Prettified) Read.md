
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1266.48 | 0.528364 | 173.697ms | 2158 | 40 | 2948.72 | 1625 | 0.510204 | 2.38844 | 1(Win) | true |
| Jsonifier | 1210.61 | 0.421244 | 161.42ms | 2158 | 40 | 2051.28 | 1700 | 0.195695 | 2.48561 | 2(Loss) | true |
| Glaze | 1100.55 | 0.436629 | 164.073ms | 2158 | 40 | 2666.67 | 1870 | 0.35524 | 2.74164 | 3(Loss) | true |
| simdjson (ondemand) | 985.698 | 0.159777 | 212.093ms | 2158 | 2560 | 28489.5 | 2087.89 | 0.112381 | 3.05377 | 4(Loss) | true |
