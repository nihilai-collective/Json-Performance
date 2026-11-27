
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1131.3 | 0.528932 | 238.952ms | 2632 | 160 | 22036.2 | 2218.75 | 0.225861 | 2.16208 | 1(Win) | true |
| Jsonifier (two-stage) | 1038.29 | 0.251679 | 246.656ms | 2632 | 40 | 1480.77 | 2417.5 | 0.172652 | 2.3523 | 2(Loss) | true |
| Glaze | 872.689 | 0.632881 | 313.506ms | 2632 | 160 | 53017.3 | 2876.25 | 0.0434405 | 2.80831 | 3(Loss) | true |
| simdjson (ondemand) | 653.664 | 0.204288 | 403.775ms | 2632 | 40 | 2461.54 | 3840 | 0.0867303 | 3.76022 | 4(Loss) | true |
