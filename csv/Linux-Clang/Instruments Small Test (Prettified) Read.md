
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2810.18 | 0.181308 | 1006.89ms | 7932 | 4890 | 116477 | 2691.83 | 0.0913169 | 1.82509 | 7.31493 | 1.18079 | 0.000892737 | 2.58331e-05 | 7.14148e-06 | 1(Win) | true |
| Glaze | 2333.33 | 0.102422 | 1060.72ms | 7932 | 40 | 441.023 | 3241.95 | 0.304953 | 2.19434 | 8.94995 | 1.66831 | 0.00233863 | 3.46697e-05 | 0 | 2(Loss) | true |
| Jsonifier | 2081.94 | 0.189275 | 1100.08ms | 7932 | 4890 | 231273 | 3633.41 | 0.122724 | 2.45567 | 7.95386 | 1.78366 | 0.00141922 | 3.10925e-05 | 1.11118e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1096.61 | 0.0829434 | 1428.94ms | 7932 | 4890 | 160079 | 6898.12 | 0.0523998 | 4.63714 | 17.5501 | 2.72227 | 0.00211465 | 4.45505e-05 | 1.68869e-05 | 4(Loss) | true |
