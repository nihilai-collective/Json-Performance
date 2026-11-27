
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2281.61 | 0.169161 | 2731.67ms | 65103 | 640 | 1.35613e+06 | 27212 | 0.207934 | 1.08402 | 1(Win) | true |
| Jsonifier (two-stage) | 1939.75 | 0.0932376 | 3089.63ms | 65103 | 2560 | 2.27999e+06 | 32007.8 | 0.251454 | 1.27525 | 2(Loss) | true |
| Glaze | 1626.45 | 0.127281 | 3833.47ms | 65103 | 1280 | 3.02176e+06 | 38173.5 | 0.143942 | 1.52118 | 3(Loss) | true |
| simdjson (ondemand) | 1249.43 | 0.140955 | 5038.73ms | 65103 | 640 | 3.13992e+06 | 49692.4 | 0.00139611 | 1.98053 | 4(Loss) | true |
