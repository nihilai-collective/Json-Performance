
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2075.81 | 0.124514 | 125.708ms | 2632 | 80 | 181.352 | 1209.2 | 0.0103363 | 1.16613 | 1(Win) | true |
| simdjson (reflection) | 2069.92 | 0.0296196 | 125.468ms | 2632 | 640 | 82.5659 | 1212.64 | 0.0766077 | 1.17122 | 2(Loss) | true |
| Jsonifier | 2048.02 | 0.0343709 | 126.975ms | 2632 | 320 | 56.7849 | 1225.61 | 0.0270347 | 1.18258 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1700.17 | 0.192028 | 152.15ms | 2632 | 80 | 642.994 | 1476.36 | 0.141195 | 1.42948 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1696.42 | 0.0988823 | 155.004ms | 2632 | 40 | 85.625 | 1479.62 | 0.173728 | 1.43284 | 4(Tie) | true |
