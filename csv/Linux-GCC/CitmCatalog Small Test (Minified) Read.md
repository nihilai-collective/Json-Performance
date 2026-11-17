
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1645.32 | 0.0710921 | 190.027ms | 3223 | 80 | 141.107 | 1868.14 | 0.244825 | 1.48231 | 1(Win) | true |
| Jsonifier (two-stage) | 1542.17 | 0.0744112 | 205.51ms | 3223 | 80 | 175.965 | 1993.1 | 0.182797 | 1.58402 | 2(Loss) | true |
| Glaze | 1438.04 | 0.228743 | 217.998ms | 3223 | 4890 | 116892 | 2137.42 | 0.114588 | 1.70088 | 3(Loss) | true |
| simdjson (ondemand) | 1250.11 | 0.0826858 | 242.362ms | 3223 | 30 | 123.995 | 2458.73 | 0.252877 | 1.95731 | 4(Loss) | true |
| simdjson (reflection) | 1198.57 | 0.299084 | 259.276ms | 3223 | 1280 | 75299.1 | 2564.47 | 0.293071 | 2.04208 | 5(Loss) | true |
