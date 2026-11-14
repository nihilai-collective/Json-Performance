
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1199.82 | 0.199911 | 752.598ms | 9378 | 2560 | 568463 | 7454.1 | 0.124044 | 2.5256 | 1(Win) | true |
| simdjson (ondemand) | 1098.17 | 0.177388 | 826.535ms | 9378 | 2560 | 534275 | 8144.02 | 0.256908 | 2.76066 | 2(Loss) | true |
