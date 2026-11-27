
----
### Github Events Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1095.07 | 0.0365556 | 6443.41ms | 65103 | 2560 | 1.09968e+06 | 56696.9 | 0.0169782 | 4.66928 | 16.4921 | 3.32691 | 0.0145982 | 0.0001166 | 7.68974e-05 | 1(Win) | true |
| simdjson (ondemand) | 560.038 | 0.0598282 | 6055.43ms | 65103 | 2560 | 1.12621e+07 | 110862 | 0.0249249 | 9.1168 | 33.2181 | 5.95838 | 0.0481615 | 8.72236e-05 | 5.3419e-05 | 2(Loss) | true |
