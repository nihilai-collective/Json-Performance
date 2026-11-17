
----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15470.8 | 0.567817 | 773.708ms | 108313 | 160 | 229971 | 6676.8 | 0.409047 | 1(Win) | true |
| simdjson (reflection) | 8686.7 | 0.205282 | 1263.41ms | 108313 | 640 | 381360 | 11891.2 | 0.107759 | 2(Loss) | true |
| Glaze | 2014.36 | 0.350997 | 5215.94ms | 108313 | 640 | 2.07337e+07 | 51279.6 | 0.802408 | 3(Loss) | true |
