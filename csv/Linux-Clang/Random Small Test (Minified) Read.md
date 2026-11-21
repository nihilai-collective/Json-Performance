
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1853.07 | 0.0926187 | 266.267ms | 5094 | 30 | 176.869 | 2621.6 | 0.215344 | 1.32578 | 1(Win) | true |
| Jsonifier (two-stage) | 1685.8 | 0.0657863 | 291.811ms | 5094 | 80 | 287.518 | 2881.72 | 0.0399226 | 1.45528 | 2(Loss) | true |
| Glaze | 1295.02 | 0.122221 | 389.488ms | 5094 | 30 | 630.631 | 3751.3 | 0.062162 | 1.89934 | 3(Loss) | true |
| simdjson (ondemand) | 923.318 | 0.234568 | 528.893ms | 5094 | 1280 | 194968 | 5261.48 | 0.0360688 | 2.66738 | 4(Loss) | true |
