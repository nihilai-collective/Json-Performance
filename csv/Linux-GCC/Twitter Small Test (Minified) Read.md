
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2747.68 | 0.204194 | 105.565ms | 2889 | 40 | 167.692 | 1002.73 | 0.146883 | 0.878133 | 1(Win) | true |
| Glaze | 2039.65 | 0.140317 | 141.732ms | 2889 | 40 | 143.703 | 1350.8 | 0.10375 | 1.19149 | 2(Loss) | true |
| Jsonifier (two-stage) | 1955.73 | 0.105621 | 145.642ms | 2889 | 80 | 177.12 | 1408.76 | 0.0115336 | 1.24059 | 3(Loss) | true |
| simdjson (reflection) | 1852.96 | 0.262429 | 149.602ms | 2889 | 30 | 456.783 | 1486.9 | 0.221447 | 1.31209 | 4(Loss) | true |
| simdjson (ondemand) | 1135.06 | 0.0709198 | 247.069ms | 2889 | 160 | 474.145 | 2427.32 | 0.0920948 | 2.15769 | 5(Loss) | true |
