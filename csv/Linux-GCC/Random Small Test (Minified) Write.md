
----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17440.8 | 0.0926282 | 30.3237ms | 5094 | 320 | 21.3022 | 278.544 | 0.176948 | 0.129193 | 1(Win) | true |
| simdjson (reflection) | 11466.6 | 0.283678 | 44.5803ms | 5094 | 30 | 43.3333 | 423.667 | 0.0786164 | 0.202277 | 2(Loss) | true |
| Glaze | 3757.06 | 0.0454382 | 133.065ms | 5094 | 160 | 55.2313 | 1293.04 | 0.0415515 | 0.645485 | 3(Loss) | true |
