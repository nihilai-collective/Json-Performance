
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1497.89 | 0.146746 | 4900.22ms | 65103 | 4890 | 1.80918e+07 | 41449.7 | 0.130727 | 3.40927 | 11.7239 | 2.27886 | 0.0104494 | 0.000162668 | 0.000113402 | 1(Win) | true |
| simdjson (ondemand) | 1230.49 | 0.0679537 | 5815.88ms | 65103 | 640 | 752410 | 50457.4 | 0.108065 | 4.14549 | 15.5763 | 2.85593 | 0.015942 | 4.49288e-05 | 2.56565e-05 | 2(Loss) | true |
