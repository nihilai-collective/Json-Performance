
----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 13330.9 | 1.09802 | 66.9169ms | 9255 | 4890 | 258445 | 662.092 | 5.49593 | -(Win) | false |
| Glaze | 2581.46 | 0.312048 | 348.774ms | 9255 | 2560 | 291411 | 3419.1 | 0.049696 | 2(Loss) | true |
| simdjson (reflection) | 318.78 | 0.241644 | 2710.5ms | 9255 | 1280 | 5.72973e+06 | 27687.6 | 0.788316 | 3(Loss) | true |
