
----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 27698.6 | 0.115882 | 34.5746ms | 9249 | 320 | 43.5771 | 318.447 | 0.09118 | 0.0818001 | 1(Win) | true |
| Glaze | 3563.24 | 0.104664 | 249.403ms | 9249 | 40 | 268.507 | 2475.43 | 0.0380261 | 0.687374 | 2(Loss) | true |
| simdjson (reflection) | 521.63 | 0.176775 | 1706.17ms | 9249 | 40 | 35741.1 | 16909.5 | 0.32027 | 4.73917 | 3(Loss) | true |
