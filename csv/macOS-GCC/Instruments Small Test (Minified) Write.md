
----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13308.3 | 2.02541 | 36.416ms | 4669 | 4890 | 224561 | 334.58 | 0.203642 | 1(Win) | true |
| simdjson (reflection) | 9141.62 | 1.47501 | 50.9261ms | 4669 | 4890 | 252408 | 487.081 | 0.636482 | 2(Loss) | true |
| Glaze | 1679.63 | 0.620497 | 251.468ms | 4669 | 1280 | 346345 | 2651 | 1.24504 | 3(Loss) | true |
