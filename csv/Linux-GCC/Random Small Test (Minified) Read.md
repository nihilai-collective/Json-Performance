
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1962.04 | 0.0613857 | 257.053ms | 5094 | 80 | 184.81 | 2476 | 0.502311 | 1.24843 | 1(Win) | true |
| Jsonifier (two-stage) | 1603.01 | 0.0535192 | 306.223ms | 5094 | 160 | 420.903 | 3030.55 | 0.317823 | 1.53071 | 2(Loss) | true |
| simdjson (reflection) | 1354.94 | 0.110823 | 366.951ms | 5094 | 40 | 631.528 | 3585.4 | 0.11886 | 1.81345 | 3(Loss) | true |
| simdjson (ondemand) | 1265.17 | 0.161149 | 390.866ms | 5094 | 40 | 1531.55 | 3839.8 | 0.234703 | 1.94361 | 4(Loss) | true |
| Glaze | 1107.06 | 0.429455 | 443.567ms | 5094 | 640 | 227296 | 4388.22 | 0.255004 | 2.22249 | 5(Loss) | true |
