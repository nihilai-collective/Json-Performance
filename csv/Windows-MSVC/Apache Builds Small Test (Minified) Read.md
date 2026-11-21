
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1055.14 | 0.254868 | 242.002ms | 2632 | 4890 | 179759 | 2378.9 | 0.36528 | 2.31795 | 1(Win) | true |
| Jsonifier (two-stage) | 1001.03 | 0.232876 | 255.783ms | 2632 | 80 | 2727.85 | 2507.5 | 0 | 2.44934 | 2(Loss) | true |
| Glaze | 817.446 | 0.201295 | 315.588ms | 2632 | 160 | 6112.81 | 3070.62 | 0.347222 | 3.00148 | 3(Loss) | true |
| simdjson (ondemand) | 740.707 | 0.277746 | 350.22ms | 2632 | 80 | 7087.03 | 3388.75 | 0.184094 | 3.31507 | 4(Loss) | true |
