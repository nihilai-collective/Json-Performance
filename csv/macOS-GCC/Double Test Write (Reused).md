
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1003.63 | 1.0077 | 208.028ms | 1997 | 320 | 117009 | 1897.6 | 0.508475 | 1(Win) | true |
| Jsonifier | 849.459 | 0.416442 | 238.527ms | 1997 | 2560 | 223162 | 2242 | 1.25958 | 2(Loss) | true |
| Glaze | 582.182 | 0.300702 | 316.53ms | 1798 | 4890 | 383570 | 2945.31 | 0.182709 | 3(Loss) | true |
