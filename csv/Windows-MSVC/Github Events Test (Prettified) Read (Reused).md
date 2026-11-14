
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1710.24 | 0.140561 | 4350.59ms | 65103 | 1280 | 3.33291e+06 | 36303 | 0.231014 | 1.77594 | 1(Win) | true |
| Jsonifier | 1620.33 | 0.359961 | 4715.08ms | 65103 | 40 | 760968 | 38317.5 | 0.0195771 | 1.87424 | 2(Loss) | true |
| Glaze | 1560.57 | 0.795125 | 4712.89ms | 65103 | 2560 | 2.56182e+08 | 39785 | 0.647429 | 1.94623 | 3(Loss) | true |
| simdjson (ondemand) | 1145.49 | 0.104491 | 6112.39ms | 65103 | 640 | 2.05285e+06 | 54201.1 | 0.264801 | 2.65209 | 4(Loss) | true |
