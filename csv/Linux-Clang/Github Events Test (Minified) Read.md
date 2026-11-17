
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1300.56 | 0.0516495 | 4681.91ms | 53331 | 640 | 261102 | 39106.5 | 0.0532644 | 3.96197 | 13.9699 | 2.74989 | 0.0130499 | 4.38007e-05 | 2.33799e-05 | 1(Win) | true |
| simdjson (ondemand) | 998.82 | 0.139633 | 5821.19ms | 53331 | 2560 | 1.2942e+07 | 50920.5 | 0.0626936 | 5.15083 | 18.8427 | 3.49552 | 0.0206926 | 5.62818e-05 | 2.31162e-05 | 2(Loss) | true |
