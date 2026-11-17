
----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10541.6 | 0.557545 | 109.093ms | 11812 | 2560 | 90871.9 | 1068.6 | 0.447177 | 1(Win) | true |
| simdjson (reflection) | 8111.86 | 1.12601 | 138.305ms | 11812 | 4890 | 1.19564e+06 | 1388.68 | 0.186293 | 2(Loss) | true |
| Glaze | 1820.43 | 0.569214 | 635.16ms | 11812 | 1280 | 1.58804e+06 | 6188 | 1.93966 | 3(Loss) | true |
