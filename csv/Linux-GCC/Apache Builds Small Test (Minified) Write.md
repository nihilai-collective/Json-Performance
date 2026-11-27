
----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10955.6 | 0.326012 | 25.7168ms | 2632 | 80 | 44.6328 | 229.113 | 0.554093 | 0.198741 | 1(Win) | true |
| simdjson (reflection) | 8874.73 | 0.376323 | 31.4023ms | 2632 | 4890 | 5539.77 | 282.833 | 0.183102 | 0.252464 | 2(Loss) | true |
| Glaze | 4250.28 | 0.15376 | 63.2961ms | 2632 | 30 | 24.7368 | 590.567 | 0.113014 | 0.556117 | 3(Loss) | true |
