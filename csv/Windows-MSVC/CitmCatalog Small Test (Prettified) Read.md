
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1224.74 | 0.293255 | 475.526ms | 5839 | 30 | 5333.33 | 4546.67 | 1.18694 | 2.46675 | 1(Win) | true |
| Jsonifier (two-stage) | 1201.14 | 0.107193 | 489.674ms | 5839 | 1280 | 31610.4 | 4636.02 | 0.455376 | 2.51807 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 945.417 | 0.205129 | 620.345ms | 5839 | 30 | 4379.31 | 5890 | 0.169492 | 3.20986 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 942.178 | 1.39752 | 604.508ms | 5839 | 4890 | 3.33609e+07 | 5910.25 | 0.362362 | 3.21357 | 3(Tie) | true |
