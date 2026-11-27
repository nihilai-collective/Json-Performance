
----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9569.12 | 0.217645 | 7108.14ms | 631514 | 80 | 1.5011e+06 | 62937.7 | 0.0705758 | 0.536856 | 2.69828 | 0.311943 | 0.000727577 | 4.87519e-05 | 1.5637e-05 | 1(Win) | true |
| Jsonifier | 9432.96 | 0.0720895 | 7105.08ms | 631514 | 40 | 84737.2 | 63846.2 | 0.0289712 | 0.536057 | 2.69858 | 0.312015 | 0.00073304 | 2.79883e-05 | 7.24449e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8186.65 | 0.0490179 | 8081.96ms | 631514 | 1280 | 1.66446e+06 | 73565.9 | 0.0255626 | 0.617419 | 3.02916 | 0.290049 | 0.000633663 | 1.24354e-05 | 3.91544e-06 | 3(Loss) | true |
| simdjson (reflection) | 8140.16 | 0.09917 | 8174.57ms | 631514 | 160 | 861351 | 73986.1 | 0.18347 | 0.627458 | 3.00761 | 0.289292 | 0.000728082 | 2.39504e-06 | 1.08865e-07 | 4(Loss) | true |
| Glaze | 3852.03 | 0.0368537 | 8372.64ms | 631514 | 2560 | 8.49938e+06 | 156348 | 0.121196 | 1.32207 | 5.85935 | 0.963143 | 0.0014715 | 6.52759e-06 | 4.33977e-06 | 5(Loss) | true |
