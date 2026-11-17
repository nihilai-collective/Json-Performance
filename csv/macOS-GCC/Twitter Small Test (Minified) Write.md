
----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10679.9 | 2.52598 | 30.6051ms | 2963 | 4890 | 218424 | 264.586 | 1.56783 | 1(Win) | true |
| simdjson (reflection) | 8594.09 | 4.0256 | 35.202ms | 2963 | 1280 | 224251 | 328.8 | 0.611995 | 2(Loss) | true |
| Glaze | 3240.52 | 1.84681 | 97.8811ms | 2963 | 640 | 165981 | 872 | 1.35747 | 3(Loss) | true |
