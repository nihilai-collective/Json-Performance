
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3535.33 | 0.0613336 | 218.64ms | 7932 | 80 | 137.782 | 2139.7 | 0.149778 | 0.691011 | 1(Win) | true |
| Jsonifier | 2150.36 | 0.0712433 | 349.535ms | 7932 | 40 | 251.241 | 3517.8 | 0.0331757 | 1.14224 | 2(Loss) | true |
| Glaze | 2047.25 | 0.0901752 | 376.835ms | 7932 | 40 | 444.076 | 3694.97 | 0.0259294 | 1.20034 | 3(Loss) | true |
| simdjson (ondemand) | 1034.46 | 0.436791 | 746.657ms | 7932 | 160 | 163233 | 7312.57 | 0.335449 | 2.38475 | 4(Loss) | true |
