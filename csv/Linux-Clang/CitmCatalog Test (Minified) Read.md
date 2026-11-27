
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1245.76 | 0.121954 | 9747.12ms | 500299 | 320 | 6.9812e+07 | 382996 | 0.327568 | 1.98718 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1245.63 | 0.0920744 | 9782.13ms | 500299 | 160 | 1.99012e+07 | 383037 | 0.277335 | 1.98739 | 1(Tie) | true |
