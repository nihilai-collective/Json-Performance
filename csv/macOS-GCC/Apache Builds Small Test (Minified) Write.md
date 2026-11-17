
----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 9174.24 | 12.9358 | 31.4898ms | 2632 | 160 | 200418 | 273.6 | 0.581395 | -(Win) | false |
| simdjson (reflection) | 5152.03 | 5.77254 | 49.056ms | 2632 | 320 | 253104 | 487.2 | 1.45631 | 2(Loss) | true |
| Glaze | 2824.43 | 0.882601 | 93.322ms | 2632 | 2560 | 157499 | 888.7 | 1.72848 | 3(Loss) | true |
