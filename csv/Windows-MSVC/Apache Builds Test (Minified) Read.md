
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 816.41 | 0.258653 | 5658.98ms | 94653 | 2560 | 2.09377e+08 | 110567 | 0.381842 | 3.72183 | 1(Win) | true |
| Jsonifier (two-stage) | 770.174 | 0.200734 | 6013.4ms | 94653 | 2560 | 1.41701e+08 | 117205 | 0.703938 | 3.94537 | 2(Loss) | true |
| Glaze | 758.357 | 0.5598 | 6057.68ms | 94653 | 1280 | 5.68325e+08 | 119031 | 0.126317 | 4.00692 | 3(Loss) | true |
| simdjson (ondemand) | 641.181 | 0.17615 | 7198.61ms | 94653 | 2560 | 1.57439e+08 | 140784 | 0.204792 | 4.73935 | 4(Loss) | true |
