
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2020.38 | 0.214812 | 466.741ms | 9378 | 30 | 2712.64 | 4426.67 | 0.449775 | 1.21717 | 1(Win) | true |
| Jsonifier (two-stage) | 2003.04 | 0.121117 | 449.151ms | 9378 | 160 | 4679.25 | 4465 | 0 | 1.22765 | 2(Loss) | true |
| Glaze | 1345.93 | 0.237292 | 682.863ms | 9378 | 2560 | 636472 | 6644.88 | 0.586166 | 1.83132 | 3(Loss) | true |
| simdjson (ondemand) | 1161.12 | 0.214146 | 754.57ms | 9378 | 80 | 21765.8 | 7702.5 | 0.983284 | 2.12431 | 4(Loss) | true |
