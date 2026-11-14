
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 705.745 | 0.390363 | 8618.14ms | 500299 | 640 | 4.45738e+09 | 676054 | 5.57351 | -(Win) | false |
| simdjson (ondemand) | 686.822 | 0.999834 | 8863.81ms | 500299 | 30 | 1.44727e+09 | 694682 | 2.07852 | 2(Loss) | true |
