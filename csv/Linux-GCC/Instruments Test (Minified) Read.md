
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21710.4 | 0.0441763 | 470.384ms | 108313 | 30 | 132.533 | 4757.87 | 0.0210222 | 0.113357 | 1(Win) | true |
| simdjson (stage-1) | 16301.8 | 0.0321938 | 640.601ms | 108313 | 80 | 332.907 | 6336.44 | 0.16341 | 0.151218 | 2(Loss) | true |
