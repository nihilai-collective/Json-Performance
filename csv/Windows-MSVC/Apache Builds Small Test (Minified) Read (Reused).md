
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1894.39 | 0.367681 | 165.201ms | 2632 | 80 | 1898.73 | 1325 | 0.56926 | 1.58318 | 1(Win) | true |
| Glaze | 1773.9 | 0.404079 | 176.908ms | 2632 | 40 | 1307.69 | 1415 | 0.117647 | 1.68812 | 2(Loss) | true |
| Jsonifier (two-stage) | 1602.53 | 0.0951511 | 186.237ms | 2632 | 4890 | 10861.7 | 1566.32 | 0.266977 | 1.8742 | 3(Loss) | true |
| simdjson (ondemand) | 1185.04 | 0.161431 | 249.69ms | 2632 | 160 | 1870.68 | 2118.12 | 0.674091 | 2.54547 | 4(Loss) | true |
