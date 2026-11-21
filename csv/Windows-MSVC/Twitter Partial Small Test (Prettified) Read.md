
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6329.57 | 0.429366 | 62.005ms | 3808 | 320 | 1942.01 | 573.75 | 0.325733 | 0.371702 | 1(Win) | true |
| Jsonifier (two-stage) | 6184.72 | 0.318693 | 62.02ms | 3808 | 320 | 1120.59 | 587.188 | 0.0531915 | 0.380914 | 2(Loss) | true |
| simdjson (ondemand) | 4832.06 | 0.372304 | 79.4904ms | 3808 | 320 | 2505.39 | 751.562 | 0.124585 | 0.495138 | 3(Loss) | true |
| Glaze | 3301.45 | 0 | 110.283ms | 3808 | 30 | 0 | 1100 | 0 | 0.727582 | 4(Loss) | true |
