
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11278.4 | 0.151652 | 484.318ms | 56369 | 640 | 33439.3 | 4766.41 | 0.180624 | 0.268012 | 1(Win) | true |
| Glaze | 4172.06 | 0.125926 | 1293.47ms | 56369 | 640 | 168496 | 12885.2 | 0.0157667 | 0.727124 | 2(Loss) | true |
