
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1503.65 | 0.157682 | 449.949ms | 5839 | 30 | 1022.99 | 3703.33 | 0.2693 | 1.63002 | 1(Win) | true |
| Jsonifier | 1482.3 | 0.244948 | 448.251ms | 5839 | 30 | 2540.23 | 3756.67 | 0.0886525 | 1.6557 | 2(Loss) | true |
| Glaze | 928.277 | 0.112898 | 676.823ms | 5839 | 80 | 3669.3 | 5998.75 | 0.52367 | 2.65254 | 3(Loss) | true |
| simdjson (ondemand) | 889.099 | 0.164121 | 709.299ms | 5839 | 4890 | 516672 | 6263.09 | 0.500769 | 2.77205 | 4(Loss) | true |
