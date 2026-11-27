
----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16049.3 | 0.1197 | 924.071ms | 31235 | 2560 | 12635.8 | 1856.04 | 0.0390254 | 0.32269 | 1.44117 | 0.244694 | 0.000126786 | 1.81587e-05 | 9.3795e-06 | 1(Win) | true |
| Glaze | 5193.37 | 0.0654419 | 1311.31ms | 31235 | 4890 | 68897.7 | 5735.78 | 0.36704 | 0.981679 | 3.70453 | 0.654298 | 0.0022327 | 2.83555e-05 | 1.7448e-05 | 2(Loss) | true |
