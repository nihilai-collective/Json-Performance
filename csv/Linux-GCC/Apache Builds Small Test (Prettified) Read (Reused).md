
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2782.81 | 0.087153 | 127.12ms | 3370 | 160 | 162.098 | 1154.91 | 0.156154 | 0.869266 | 1(Win) | true |
| simdjson (reflection) | 2720.98 | 0.0469094 | 129.02ms | 3370 | 80 | 24.5595 | 1181.15 | 0.116548 | 0.889703 | 2(Loss) | true |
| Glaze | 2504.15 | 0.10206 | 129.831ms | 3370 | 80 | 137.26 | 1283.42 | 0.115059 | 0.968884 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2422.37 | 0.350825 | 144.162ms | 3370 | 40 | 866.603 | 1326.75 | 0.134595 | 1.00139 | 4(Tie) | true |
| Jsonifier STATISTICAL TIE | 2418.65 | 0.0620919 | 142.525ms | 3370 | 160 | 108.919 | 1328.79 | 0.0897565 | 1.00398 | 4(Tie) | true |
