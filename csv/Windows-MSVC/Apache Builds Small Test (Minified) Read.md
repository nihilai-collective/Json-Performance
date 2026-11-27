
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1425.67 | 0.220075 | 185.422ms | 2632 | 160 | 2402.12 | 1760.62 | 0.0355114 | 2.11025 | 1(Win) | true |
| Jsonifier (two-stage) | 1238.3 | 0.228094 | 206.674ms | 2632 | 640 | 13681.3 | 2027.03 | 0.100309 | 2.43204 | 2(Loss) | true |
| Glaze | 1007.05 | 0.648634 | 276.245ms | 2632 | 40 | 10455.1 | 2492.5 | 0.100402 | 2.9929 | 3(Loss) | true |
| simdjson (ondemand) | 841.6 | 0.447388 | 304.149ms | 2632 | 40 | 7121.79 | 2982.5 | 0.0838926 | 3.59022 | 4(Loss) | true |
