
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1571.46 | 0.0930296 | 1105.55ms | 18245 | 1280 | 135810 | 11072.3 | 0.110193 | 1.92969 | 1(Win) | true |
| Jsonifier | 1416.77 | 0.0798346 | 1230.83ms | 18245 | 4890 | 470088 | 12281.3 | 0.0327656 | 2.14078 | 2(Loss) | true |
| simdjson (ondemand) | 986.426 | 0.100587 | 1772.96ms | 18245 | 1280 | 402949 | 17639.2 | 0.00265736 | 3.07576 | 3(Loss) | true |
| Glaze | 866.409 | 0.0983736 | 2016.06ms | 18245 | 640 | 249793 | 20082.7 | 0.0147848 | 3.50396 | 4(Loss) | true |
