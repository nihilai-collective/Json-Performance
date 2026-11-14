
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 851.77 | 0.26037 | 576.885ms | 5092 | 1280 | 282049 | 5701.2 | 0.196065 | 1(Win) | true |
| simdjson (ondemand) | 771.868 | 0.127386 | 631.956ms | 5092 | 4890 | 314081 | 6291.37 | 0.0386072 | 2(Loss) | true |
