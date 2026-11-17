
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1204.33 | 0.134623 | 481.538ms | 5839 | 80 | 3099.68 | 4623.75 | 0.027027 | 2.04334 | 1(Win) | true |
| Jsonifier | 1103.4 | 0.206697 | 523.183ms | 5839 | 30 | 3264.37 | 5046.67 | 0.0660066 | 2.23026 | 2(Loss) | true |
| simdjson (ondemand) | 744.639 | 0.131856 | 762.967ms | 5839 | 160 | 15556.2 | 7478.12 | 0.0250668 | 3.3113 | 3(Loss) | true |
| Glaze | 740.739 | 0.231317 | 762.807ms | 5839 | 2560 | 774106 | 7517.5 | 0.00207853 | 3.32961 | 4(Loss) | true |
