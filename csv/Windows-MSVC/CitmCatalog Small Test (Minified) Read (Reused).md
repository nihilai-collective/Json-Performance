
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 841.045 | 0.344591 | 427.421ms | 3223 | 2560 | 406005 | 3654.61 | 0.206929 | 2.9192 | 1(Win) | true |
| Jsonifier | 593.091 | 0.16764 | 375.618ms | 3223 | 40 | 3019.23 | 5182.5 | 0.208601 | 4.1563 | 2(Loss) | true |
| Glaze | 560.552 | 0.215666 | 625.835ms | 3223 | 30 | 4195.4 | 5483.33 | 0.182039 | 4.39006 | 3(Loss) | true |
| simdjson (ondemand) | 461.515 | 0.154405 | 772.488ms | 3223 | 30 | 3172.41 | 6660 | 0.1998 | 5.34383 | 4(Loss) | true |
