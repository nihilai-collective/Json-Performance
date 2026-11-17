
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2556.87 | 0.242979 | 221.374ms | 5839 | 4890 | 136932 | 2177.86 | 0.030331 | 0.955504 | 1(Win) | true |
| Jsonifier | 1886.78 | 0.210672 | 300.522ms | 5839 | 2560 | 98967 | 2951.33 | 0.386816 | 1.29936 | 2(Loss) | true |
| simdjson (ondemand) | 1771.06 | 0.271395 | 323.78ms | 5839 | 1280 | 93201.4 | 3144.16 | 0.00777671 | 1.3854 | 3(Loss) | true |
| Glaze | 1745.72 | 0.0972667 | 331.44ms | 5839 | 30 | 288.786 | 3189.8 | 0.314596 | 1.40634 | 4(Loss) | true |
