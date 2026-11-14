
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9731.36 | 0.154398 | 1069.48ms | 108313 | 1280 | 343803 | 10614.7 | 0.0559054 | 0.311187 | 1(Win) | true |
| simdjson (stage-1) | 9108.94 | 0.191686 | 1158.24ms | 108313 | 640 | 302404 | 11340 | 0.063422 | 0.332493 | 2(Loss) | true |
