
----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1921.3 | 0.155568 | 168.901ms | 3223 | 30 | 185.821 | 1599.8 | 0.233908 | 1.26678 | 1(Win) | true |
| Jsonifier (two-stage) | 1596.37 | 0.147883 | 197.241ms | 3223 | 40 | 324.302 | 1925.42 | 0.148673 | 1.52827 | 2(Loss) | true |
| simdjson (ondemand) | 1412.59 | 0.0618005 | 225.949ms | 3223 | 320 | 578.663 | 2175.93 | 0.297404 | 1.73165 | 3(Loss) | true |
| Glaze | 1317.32 | 0.103357 | 237.636ms | 3223 | 80 | 465.271 | 2333.29 | 0.682643 | 1.8578 | 4(Loss) | true |
| simdjson (reflection) | 1304.4 | 0.155429 | 239.467ms | 3223 | 80 | 1073.13 | 2356.4 | 0.752523 | 1.87647 | 5(Loss) | true |
